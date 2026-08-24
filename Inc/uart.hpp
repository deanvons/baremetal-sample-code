#pragma once

#include <cstdint>
#include "stm32f4xx.h"

void uart2_tx_init();
char uart2_read();
void uart2_rxtx_init();
