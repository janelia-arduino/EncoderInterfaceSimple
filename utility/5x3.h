// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef ENCODER_INTERFACE_SIMPLE_5X3_CONSTANTS_H
#define ENCODER_INTERFACE_SIMPLE_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace encoder_interface_simple
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{INTERRUPT_COUNT_MAX=1};

enum {CHANNEL_COUNT=8};

enum{EVENT_COUNT_MAX=36};
enum{INDEXED_PWM_COUNT_MAX=16};

enum{PWM_LEVEL_COUNT_MAX=4};

extern const size_t signal_pins[CHANNEL_COUNT];
extern const size_t fault_pins[CHANNEL_COUNT];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long power_max_default[CHANNEL_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
