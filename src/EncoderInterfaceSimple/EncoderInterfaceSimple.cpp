// ----------------------------------------------------------------------------
// EncoderInterfaceSimple.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "../EncoderInterfaceSimple.h"


using namespace encoder_interface_simple;

void EncoderInterfaceSimple::setup()
{
  // Parent Setup
  ModularDeviceBase::setup();

  // Reset Watchdog
  resetWatchdog();

  // Event Controller Setup
  event_controller_.setup();

  // Pin Setup
  pinMode(constants::enable_pin,OUTPUT);
  enableAllOutputs();

  for (size_t output_index=0; output_index<constants::OUTPUT_COUNT; ++output_index)
  {
    pinMode(constants::output_pins[output_index],OUTPUT);
    digitalWrite(constants::output_pins[output_index],LOW);
  }

  // Pins

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.addHardware(constants::hardware_info,
                              pins_);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);
  // Properties
  modular_server::Property & invert_encoder_direction_property = modular_server_.createProperty(constants::invert_encoder_direction_property_name,constants::invert_encoder_direction_default);
  invert_encoder_direction_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&EncoderInterfaceSimple::invertEncoderDirectionHandler));

  modular_server::Property & sample_period_property = modular_server_.createProperty(constants::sample_period_property_name,constants::sample_period_default);
  sample_period_property.setRange(constants::sample_period_min,constants::sample_period_max);

  // Parameters
  modular_server::Parameter & encoder_index_parameter = modular_server_.createParameter(constants::encoder_index_parameter_name);
  encoder_index_parameter.setRange(0,constants::ENCODER_COUNT-1);

  modular_server::Parameter & position_parameter = modular_server_.createParameter(constants::position_parameter_name);
  position_parameter.setTypeLong();

  // Functions
  modular_server::Function & get_positions_function = modular_server_.createFunction(constants::get_positions_function_name);
  get_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::getPositionsHandler));
  get_positions_function.setResultTypeArray();
  get_positions_function.setResultTypeLong();

  modular_server::Function & set_position_function = modular_server_.createFunction(constants::set_position_function_name);
  set_position_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::setPositionHandler));
  set_position_function.addParameter(encoder_index_parameter);
  set_position_function.addParameter(position_parameter);

  modular_server::Function & enable_all_outputs_function = modular_server_.createFunction(constants::enable_all_outputs_function_name);
  enable_all_outputs_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::enableAllOutputsHandler));

  modular_server::Function & disable_all_outputs_function = modular_server_.createFunction(constants::disable_all_outputs_function_name);
  disable_all_outputs_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::disableAllOutputsHandler));

  modular_server::Function & outputs_enabled_function = modular_server_.createFunction(constants::outputs_enabled_function_name);
  outputs_enabled_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::outputsEnabledHandler));
  outputs_enabled_function.setResultTypeBool();

  // Callbacks

  // Encoders Setup
  for (size_t encoder_index=0; encoder_index<constants::ENCODER_COUNT; ++encoder_index)
  {
    invertEncoderDirectionHandler(encoder_index);
  }
  encoders_[0].attachPositiveFunctor(makeFunctor((Functor1<int32_t> *)0,*this,&EncoderInterfaceSimple::positiveEncoder0Handler));
  encoders_[0].attachNegativeFunctor(makeFunctor((Functor1<int32_t> *)0,*this,&EncoderInterfaceSimple::negativeEncoder0Handler));

}

void EncoderInterfaceSimple::enableAllOutputs()
{
  digitalWrite(constants::enable_pin,LOW);
  enabled_ = true;
}

void EncoderInterfaceSimple::disableAllOutputs()
{
  digitalWrite(constants::enable_pin,HIGH);
  enabled_ = false;
}

bool EncoderInterfaceSimple::outputsEnabled()
{
  return enabled_;
}

long EncoderInterfaceSimple::getPosition(const size_t encoder_index)
{
  noInterrupts();
  long position = encoders_[encoder_index].read();
  interrupts();
  return position;
}

void EncoderInterfaceSimple::setPosition(const size_t encoder_index,
                                         const long position)
{
  encoders_[encoder_index].write(position);
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void EncoderInterfaceSimple::positiveEncoder0Handler(const int32_t position)
{
  digitalWrite(constants::output_pins[0],
               !digitalRead(constants::output_pins[0]));
  digitalWrite(constants::output_pins[1],
               HIGH);
}

void EncoderInterfaceSimple::negativeEncoder0Handler(const int32_t position)
{
  digitalWrite(constants::output_pins[0],
               !digitalRead(constants::output_pins[0]));
  digitalWrite(constants::output_pins[1],
               LOW);
}

void EncoderInterfaceSimple::getPositionsHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  long position;
  for (size_t encoder_index=0; encoder_index<constants::ENCODER_COUNT; ++encoder_index)
  {
    position = getPosition(encoder_index);
    modular_server_.response().write(position);
  }

  modular_server_.response().endArray();

}

void EncoderInterfaceSimple::setPositionHandler()
{
  long encoder_index;
  modular_server_.parameter(constants::encoder_index_parameter_name).getValue(encoder_index);

  long position;
  modular_server_.parameter(constants::position_parameter_name).getValue(position);

  setPosition(encoder_index,position);
}

void EncoderInterfaceSimple::enableAllOutputsHandler()
{
  enableAllOutputs();
}

void EncoderInterfaceSimple::disableAllOutputsHandler()
{
  disableAllOutputs();
}

void EncoderInterfaceSimple::outputsEnabledHandler()
{
  bool all_enabled = outputsEnabled();
  modular_server_.response().returnResult(all_enabled);
}

void EncoderInterfaceSimple::invertEncoderDirectionHandler(const size_t encoder_index)
{
  modular_server::Property & invert_encoder_direction_property = modular_server_.property(constants::invert_encoder_direction_property_name);
  bool invert_encoder_direction;
  invert_encoder_direction_property.getElementValue(encoder_index,invert_encoder_direction);

  if (!invert_encoder_direction)
  {
    encoders_[encoder_index].setup(constants::encoder_a_pins[encoder_index],
                                   constants::encoder_b_pins[encoder_index]);
  }
  else
  {
    encoders_[encoder_index].setup(constants::encoder_b_pins[encoder_index],
                                   constants::encoder_a_pins[encoder_index]);
  }
}
