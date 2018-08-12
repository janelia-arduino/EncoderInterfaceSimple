// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef ENCODER_INTERFACE_SIMPLE_CONSTANTS_H
#define ENCODER_INTERFACE_SIMPLE_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularServer.h>

#include <EventController.h>


namespace encoder_interface_simple
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=2};
enum{PARAMETER_COUNT_MAX=2};
enum{FUNCTION_COUNT_MAX=7};
enum{CALLBACK_COUNT_MAX=5};

enum{EVENT_COUNT_MAX=16};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const size_t enable_pin;

// Pins

// Units
extern ConstantString ms_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString invert_encoder_direction_property_name;
extern const bool invert_encoder_direction_element_default;

extern ConstantString sample_period_property_name;
extern const long sample_period_min;
extern const long sample_period_max;
extern const long sample_period_default;

// Parameters
extern ConstantString encoder_index_parameter_name;

extern ConstantString position_parameter_name;

// Functions
extern ConstantString get_positions_function_name;
extern ConstantString set_position_function_name;
extern ConstantString outputs_enabled_function_name;
extern ConstantString sampling_function_name;
extern ConstantString get_samples_function_name;
extern ConstantString get_sample_count_function_name;
extern ConstantString get_sample_count_max_function_name;

// Callbacks
extern ConstantString enable_outputs_callback_name;
extern ConstantString disable_outputs_callback_name;
extern ConstantString start_sampling_callback_name;
extern ConstantString stop_sampling_callback_name;
extern ConstantString clear_samples_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
