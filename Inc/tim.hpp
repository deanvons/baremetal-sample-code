#pragma once

#include <cstdint>

constexpr uint32_t SR_UIF   = (1U << 0);
constexpr uint32_t SR_CC1IF = (1U << 1);

void tim2_1hz_init();
void tim2_pa5_output_compare();
void tim3_pa6_input_capture();
