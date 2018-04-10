// ----------------------------------------------------------------------------
// EncoderInterfaceSimple.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef ENCODER_INTERFACE_SIMPLE_H
#define ENCODER_INTERFACE_SIMPLE_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <EncoderFunctors.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "EncoderInterfaceSimple/Constants.h"


class EncoderInterfaceSimple : public ModularDeviceBase
{
public:
  virtual void setup();

  void enableAllOutputs();
  void disableAllOutputs();
  bool outputsEnabled();

  long getPosition(const size_t encoder_index);
  void setPosition(const size_t encoder_index,
                   const long position);

private:
  modular_server::Pin pins_[encoder_interface_simple::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[encoder_interface_simple::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[encoder_interface_simple::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[encoder_interface_simple::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[encoder_interface_simple::constants::CALLBACK_COUNT_MAX];

  bool enabled_;
  EncoderFunctors encoders_[encoder_interface_simple::constants::ENCODER_COUNT];

  // Handlers
  void positiveEncoder0Handler(const int32_t position);
  void negativeEncoder0Handler(const int32_t position);
  void enableAllOutputsHandler();
  void disableAllOutputsHandler();
  void outputsEnabledHandler();
  void getPositionsHandler();
  void setPositionHandler();
  void invertEncoderDirectionHandler(const size_t encoder_index);

};

#endif
