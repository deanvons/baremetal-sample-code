# Bare‑Metal STM32F4 Samples (STM32F411/Nucleo)

A curated set of **bare‑metal** examples for the STM32F4 (tested on **STM32F411RE Nucleo**), progressing from GPIO to UART, ADC, SysTick, timers, and capture/compare.

Each example is intentionally small, register‑level, and self‑contained so you can read it end‑to‑end and step through in a debugger.

> If you're new to this style: the idea is to *learn the peripherals*, not a framework. We use CMSIS headers only; no HAL/LL.

---

## How this repo is organized

Each topic below lives on its **own branch**, checked out independently and self-contained (its own CMSIS headers, its own `.cproject`/`.project`, ready to import in STM32CubeIDE without anything else on disk). `main` is just this overview — check out a branch to get the code for that topic:

```
git checkout <branch-name>
```

| # | Branch | Topic |
|---|--------|-------|
| 00 | [`00-led-toggle-addr`](../../tree/00-led-toggle-addr) | Blink by writing to memory‑mapped registers (no structs) |
| 01 | [`01-led-toggle-addr-struct`](../../tree/01-led-toggle-addr-struct) | Blink using register structs |
| 02 | [`02-gpio-output`](../../tree/02-gpio-output) | Configure PA5 as output, drive LED |
| 03 | [`03-gpio-bsrr`](../../tree/03-gpio-bsrr) | Atomic pin set/reset using BSRR |
| 04 | [`04-gpio-input`](../../tree/04-gpio-input) | Read a button, simple polling |
| 05 | [`05-uart-tx`](../../tree/05-uart-tx) | Minimal UART TX (write DR when TXE) |
| 06 | [`06-uart-printf`](../../tree/06-uart-printf) | Retarget printf over USART2 |
| 07 | [`07-uart-modular`](../../tree/07-uart-modular) | Split UART into uart.c/.h module |
| 08 | [`08-uart-rx`](../../tree/08-uart-rx) | RX with polling or interrupt skeleton |
| 09 | [`09-adc-single-conversion`](../../tree/09-adc-single-conversion) | ADC single‑shot on PA1 |
| 10 | [`10-adc-continuous-conversion`](../../tree/10-adc-continuous-conversion) | ADC continuous mode + EOC handling |
| 11 | [`11-systick-delay`](../../tree/11-systick-delay) | Millisecond delay with SysTick (24‑bit down counter) |
| 12 | [`12-timers`](../../tree/12-timers) | TIM2 basic timebase (PSC+ARR) for 1 Hz |
| 13 | [`13-output-compare`](../../tree/13-output-compare) | Toggle PA5 via TIM2 OC (no CPU in the loop) |
| 14 | [`14-input-capture`](../../tree/14-input-capture) | Measure external frequency/duty with input capture |

`F4_chip_headers/CMSIS` (kept here on `main`) is a reference copy of the vendor/CMSIS headers used across the series; each topic branch also carries its own self-contained copy so it builds standalone.

---

## Target & Prerequisites

- **Board:** NUCLEO‑F411RE (STM32F411RET6)
- **IDE:** STM32CubeIDE (latest version recommended)
- **Headers:** CMSIS + device headers, vendored per branch (and referenced here under `F4_chip_headers/`)

Optional:
- You can still build with `arm-none-eabi-gcc` manually, but STM32CubeIDE provides a ready toolchain + debugger integration.

---

## Build & Flash (STM32CubeIDE)

1. Check out the branch for the topic you want (see table above).
2. Open **STM32CubeIDE**.
3. **Import Project** → *Existing Projects into Workspace*.
   - Point to the repo root (branches are flattened, one project per branch).
   - Make sure "Copy projects into workspace" is **unchecked** (so it stays linked to the repo).
4. Build (`Ctrl+B` or hammer icon).
5. Connect your Nucleo board via USB (ST‑Link).
6. Run → Debug/Run (green bug/play icons).
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

- **Wrong clock tree:** If `SYSCLK` / `APB` prescalers are off, timer math won't match reality. Use CubeMX clock config view to confirm.
- **ADC sampling time:** Too short for a high‑impedance sensor → noisy readings.
- **Forgetting to clear flags:** e.g., EXTI PR, ADC EOC, TIM UIF → repeated/blocked events.
- **ISRs doing too much:** Keep interrupt handlers short; push work to main/task context.

---

## Credits

These examples were built while following **Israel Gbati**'s bare-metal STM32 course. All original curriculum, structure, and example design credit goes to him — this repo is a personal working copy used for learning, later split per-topic into branches and lightly cleaned up.
