# Bare‑Metal STM32F4 Samples (STM32F411/Nucleo)

A curated set of **bare‑metal** examples for the STM32F4 (tested on **STM32F411RE Nucleo**), progressing from GPIO to UART, ADC, SysTick, timers, and capture/compare.

Each example is intentionally small, register‑level, and self‑contained so you can read it end‑to‑end and step through in a debugger.

> If you're new to this style: the idea is to *learn the peripherals*, not a framework. We use CMSIS headers only; no HAL/LL.

---

## What’s inside

```
0_led_toggle_addr/             # Blink by writing to memory‑mapped registers (no structs)
1_led_toggle_addr_struct/      # Blink using register structs
2_gpio_output/                 # Configure PA5 as output, drive LED
3_gpio_bsrr/                   # Atomic pin set/reset using BSRR
4_gpio_input/                  # Read a button, simple polling
5_uart_tx/                     # Minimal UART TX (write DR when TXE)
6_uart_printf/                 # Retarget printf over USART2
7_uart_modular/                # Split UART into uart.c/.h module
8_uart_rx/                     # RX with polling or interrupt skeleton
9_adc_single_conversion/       # ADC single‑shot on PA1
10_adc_continuous_conversion/  # ADC continuous mode + EOC handling
11_Systick_delay/              # Millisecond delay with SysTick (24‑bit down counter)
12_Timers/                     # TIM2 basic timebase (PSC+ARR) for 1 Hz
13_OutputCompare/              # Toggle PA5 via TIM2 OC (no CPU in the loop)
14_InputCapture/               # Measure external frequency/duty with input capture
F4_chip_headers/ CMSIS/        # Vendor headers & core CMSIS (used by all examples)
```

> Folder names map to the learning path you’ve been following in class.

---

## Target & Prerequisites

- **Board:** NUCLEO‑F411RE (STM32F411RET6)  
- **IDE:** STM32CubeIDE (latest version recommended)  
- **Headers:** CMSIS + device headers are supplied under `F4_chip_headers/`

Optional:
- You can still build with `arm-none-eabi-gcc` manually, but STM32CubeIDE provides a ready toolchain + debugger integration.

---

## Build & Flash (STM32CubeIDE)

1. Open **STM32CubeIDE**.  
2. **Import Project** → *Existing Projects into Workspace*.  
   - Point to the example folder (e.g., `12_Timers/`).  
   - Make sure “Copy projects into workspace” is **unchecked** (so it stays linked to the repo).  
3. Build (`Ctrl+B` or hammer icon).  
4. Connect your Nucleo board via USB (ST‑Link).  
5. Run → Debug/Run (green bug/play icons).  
   - The IDE will compile, flash, and start the debugger.  

---

## Debugging Notes (CubeIDE)

- **Peripherals view**: lets you inspect registers live (GPIO, RCC, ADC, TIM, etc.).  
- **SFRs/Registers**: CubeIDE reads the SVD so you can step through and watch bits change.  
- **Breakpoints**: pause inside your ISR or main loop to see program flow.  

---

## UART, ADC, Timer quick notes

- **USART2 (Nucleo‑F411RE)**  
  - TX: **PA2**, RX: **PA3**, AF7, 115200‑8‑N‑1 in the examples
- **ADC**  
  - Default examples use **PA1 (ADC1_IN1)**; set sample time (`SMPR2`) and sequence length (`SQR1.L=0`)
- **TIM2**  
  - 32‑bit general‑purpose timer on **APB1**  
  - 1 Hz example: choose `PSC` and `ARR` such that  
    \( f_{update} = \dfrac{f_{TIM}}{(PSC+1)(ARR+1)} = 1\text{ Hz} \)

---

## Typical Gotchas

- **Wrong clock tree:** If `SYSCLK` / `APB` prescalers are off, timer math won’t match reality. Use CubeMX clock config view to confirm.  
- **ADC sampling time:** Too short for a high‑impedance sensor → noisy readings.  
- **Forgetting to clear flags:** e.g., EXTI PR, ADC EOC, TIM UIF → repeated/blocked events.  
- **ISRs doing too much:** Keep interrupt handlers short; push work to main/task context.  

---


