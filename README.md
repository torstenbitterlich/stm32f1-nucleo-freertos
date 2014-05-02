STM32F1-Nucleo Demo Application using FreeRTOSv8.0.0
=======================================================

# Description

This is a fork of https://github.com/rgrover/stm32f0-discovery. I just modified the project to be able to compile it on the console using a makefile.
I'm currently working on making the demo usable on the stm32f1-nucleo board.

# Usage

You will need the arm toolchain to build the project. I used this one: [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded).
Beside that, you need to add the FreeRTOS Source to the project. The current version 8.0.0 works.

If you setup a path to the locally installed toolchain, you will be able to build the project using "make". This will generate the binary, which can be loaded
to the target hardware using openocd/gdb.

# Acknowledgements

The Makefile for the peripheral library for the STM32F0 was taken from https://github.com/szczys/stm32f0-discovery-basic-template.

