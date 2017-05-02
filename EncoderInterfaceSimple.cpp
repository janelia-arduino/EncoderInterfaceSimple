// ----------------------------------------------------------------------------
// EncoderInterfaceSimple.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "EncoderInterfaceSimple.h"


using namespace encoder_interface_simple;

void EncoderInterfaceSimple::setup()
{
  // Parent Setup
  ModularDeviceBase::setup();

  // Encoders Setup
  for (size_t encoder_index=0; encoder_index<constants::ENCODER_COUNT; ++encoder_index)
  {
    encoders_[encoder_index].setup(constants::encoder_a_pins[encoder_index],
                                   constants::encoder_b_pins[encoder_index]);
  }

  // Pin Setup
  pinMode(constants::enable_pin,OUTPUT);
  enableAllOutputs();

  for (size_t output_index=0; output_index<constants::OUTPUT_COUNT; ++output_index)
  {
    pinMode(constants::output_pins[output_index],OUTPUT);
    digitalWrite(constants::output_pins[output_index],LOW);
  }

  // Interrupts

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.addHardware(constants::hardware_info,
                              interrupts_);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);
  // Properties

  // Parameters

  // Functions
  modular_server::Function & enable_all_outputs_function = modular_server_.createFunction(constants::enable_all_outputs_function_name);
  enable_all_outputs_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::enableAllOutputsHandler));

  modular_server::Function & disable_all_outputs_function = modular_server_.createFunction(constants::disable_all_outputs_function_name);
  disable_all_outputs_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::disableAllOutputsHandler));

  modular_server::Function & outputs_enabled_function = modular_server_.createFunction(constants::outputs_enabled_function_name);
  outputs_enabled_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::outputsEnabledHandler));
  outputs_enabled_function.setReturnTypeBool();

  modular_server::Function & get_positions_function = modular_server_.createFunction(constants::get_positions_function_name);
  get_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&EncoderInterfaceSimple::getPositionsHandler));
  get_positions_function.setReturnTypeArray();

  // Callbacks

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

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(value) value type must match the property array element default type

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

