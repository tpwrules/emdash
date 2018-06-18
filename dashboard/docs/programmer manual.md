## Introduction

Welcome to the programmer's manual for the Einstein Motorsport Dashboard. This document explains how the firmware works and the functions available to customizers.

The firmware is divided into four distinct sections:
* Application and Main Loop
* Canvar System and Variable Handlers
* Screen
* Platform

## Application and Main Loop

The application handles dash mode changes. It also has a timer interrupt to blink things.

The main loop runs the show. It calls the variable handlers when there are new values.

### Application Operations

The following operations change the state of the application:
* `void app_show_next_mode(void)` shows the next dash mode by calling the function pointed to by `app_mode_change_func` with a `false` value.

## Canvar System and Variable Handlers

The canvar (CAN Variable) system is responsible for parsing incoming CAN messages and storing new variable values in memory. The main loop then calls a function for each variable that acts on its new value.

Canvars are defined in the canvar database. This procedure is covered elsewhere.

### Canvar Operations

NOTE: All canvar operations must be done with interrupts disabled!

The canvar operations are defined in `the place`. Consult that for more detail.

If a canvar has a specific `<name>`, then `cv_<name>` is the data structure which holds its value (a `canvar_state_t`) and `CV_ID_<name in uppercase>` is defined as its ID in the data structure array.

The following operations on canvars are supported:
* `CV_RENEW(cv_<name>)` re-sets a variable to new as long as as it is a valid value.

## Screen

The dashboard is displayed on a 240x64 graphic LCD using the RA6963 controller. The LCD is set up with a 240x64 pixel graphic layer on bottom and a 40x8 text layer on top. The two layers each have several pages which can be displayed. 

Consult the `screen file` for more information.

## Platform

The platform interfaces between the application and hardware.

The plaform calls the following interrupt functions in the application to perform work:
* `void app_can_interrupt(uint32_t msg_id, uint8_t dlc, const uint8_t *data)` is called to process a new CAN message.
* `void app_canvar_interrupt(uint8_t cv_id, uint32_t val)` is called to set a specific canvar
* `void app_timer_interrupt(void)` is called every 10 milliseconds to advince time

### Platform Operations

The following operations affect the platform:
* `void interrupt_disable(void)` disables interrupts.
* `void interrupt_enable(void)` enables interrupts.
* `void interrupt_wait(void)` waits for an interrupt to occur, then returns with interrupts enabled. It must be called with interrupts disabled.