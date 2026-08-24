# gpio_input — 04-gpio-input

Read the user button (PC13) with simple polling and mirror its state on the LED.

Part of the [Bare-Metal STM32F4 Samples](https://github.com/deanvons/baremetal-sample-code) series — see the `main` branch for the full course overview and the list of all topics/branches.

## Target

- **Board:** NUCLEO-F411RE (STM32F411RET6)
- **Style:** bare-metal, register-level, no HAL/LL

## C and C++ versions

This branch has both a **C** and a **C++** version of the same example — pick one, they cannot both be built (both define `main()`):

- C: `Src/main.c`
- C++: `Src/main.cpp`

Delete the file set you don't want before importing into STM32CubeIDE (or building manually). The C++ version is a near 1:1 translation: `constexpr` instead of `#define`, `static_cast`/`reinterpret_cast` instead of C-style casts, `pragma once` instead of include guards — no classes or abstractions, so it stays easy to diff against the C version line by line.

## Build & Flash (STM32CubeIDE)

1. Check out this branch (`04-gpio-input`).
2. Open **STM32CubeIDE** → **Import Project** → *Existing Projects into Workspace*.
   - Point to the repo root (this branch's checkout).
   - Leave "Copy projects into workspace" **unchecked** so it stays linked to the repo.
3. Build (`Ctrl+B`).
4. Connect the Nucleo board via USB (ST-Link).
5. Run → Debug/Run — the IDE will compile, flash, and start the debugger.

## Typical gotchas

- **Wrong clock tree:** if `SYSCLK`/APB prescalers are off, timing math won't match reality.
- **Forgetting to clear flags:** e.g. EXTI PR, ADC EOC, TIM UIF → repeated/blocked events.
- **ISRs doing too much:** keep interrupt handlers short; push work to main/task context.

---

Credits: Israel Gbati (original course author)
