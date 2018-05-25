// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace encoder_interface_simple
{
namespace constants
{
CONSTANT_STRING(device_name,"encoder_interface_simple");

CONSTANT_STRING(firmware_name,"EncoderInterfaceSimple");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=1,
  .version_patch=0,
};

CONSTANT_STRING(hardware_name,"encoder_interface_simple");

// Pins

// Units

// Properties
CONSTANT_STRING(invert_encoder_direction_property_name,"invertEncoderDirection");
const bool invert_encoder_direction_element_default = false;

CONSTANT_STRING(sample_period_property_name,"samplePeriod");
const long sample_period_min = 1;
const long sample_period_max = 10000;
const long sample_period_default = 100;

// Parameters
CONSTANT_STRING(encoder_index_parameter_name,"encoder_index");

CONSTANT_STRING(position_parameter_name,"position");

// Functions
CONSTANT_STRING(enable_all_outputs_function_name,"enableAllOutputs");
CONSTANT_STRING(disable_all_outputs_function_name,"disableAllOutputs");
CONSTANT_STRING(outputs_enabled_function_name,"outputsEnabled");
CONSTANT_STRING(get_positions_function_name,"getPositions");
CONSTANT_STRING(set_position_function_name,"setPosition");

// Callbacks

// Errors
}
}
