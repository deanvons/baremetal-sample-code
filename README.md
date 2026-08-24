# uart_printf — 06-uart-printf

Retarget printf over USART2 by implementing the syscalls write hook, so standard C output goes out the serial port.

Part of the [Bare-Metal STM32F4 Samples](https://github.com/deanvons/baremetal-sample-code) series — see the `main` branch for the full course overview and the list of all topics/branches.

## Target

- **Board:** NUCLEO-F411RE (STM32F411RET6)
- **Style:** bare-metal, register-level, no HAL/LL

## Peripheral notes

- **USART2 (Nucleo-F411RE):** TX `PA2`, RX `PA3`, alternate function `AF7`, 115200-8-N-1.
## Build & Flash (STM32CubeIDE)

1. Check out this branch (`06-uart-printf`).
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
