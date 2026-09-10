# Zephyr Course

## Prerequisites

- Some basic knowledge of C

- A development board containing a [zephyr-supported
board/SOC](https://docs.zephyrproject.org/latest/boards/index.html#) (this course
will assume use of the `nucleo_h753zi` by ST-Microelectronics)

- Devicetree compiler (most systems have this preinstalled)
- Git
- Python
- CMake
- Ninja

Additionally, if using an ST SOC:

- [stm32cubeprogrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)

Or (experimental):

- [OpenOCD](https://openocd.org/pages/getting-openocd.html)

## Plan

### 1. Brief Introduction

- The end goal of embedded programming
- What's an RTOS?
- Our (programming) language of choice
- Complicating a simple task
- Why Zephyr?

### 2. The Zephyr Project Structure

- Zephyr Workspace
- Build system
- Boards
- Project configuration

### 3. Compiling Your OS

- The zephyr kernel
- Kernel config
- Conditional compilation

### 4. Drivers

- What is a driver?
- Rationale behind separation of API and implementation

### 5. The Application

### 6. The Implementation

### 7. Finished Blinky

- Devicetree & the overlay file
- Flashing our application!

## Next Steps

- [Zephyr Docs](https://docs.zephyrproject.org/latest/index.html)
- [Digikey Zephyr series](https://www.youtube.com/watch?v=mTJ_vKlMS_4&list=PLEBQazB0HUyTmK2zdwhaf8bLwuEaDH-52)

## Next step: [introduction](./1_introduction.md)
