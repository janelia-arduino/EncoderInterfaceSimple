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

enum {ENCODER_COUNT=1};
enum {OUTPUT_COUNT=4};

extern const size_t encoder_a_pins[ENCODER_COUNT];
extern const size_t encoder_b_pins[ENCODER_COUNT];

extern const size_t output_pins[OUTPUT_COUNT];

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
