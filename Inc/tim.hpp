#pragma once

#include <cstdint>

constexpr uint32_t SR_UIF = (1U << 0);

void tim2_1hz_init();
