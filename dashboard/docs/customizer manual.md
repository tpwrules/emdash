## Introduction

Welcome to the customizer's manual for the Einstein Motorsport Dashboard. This document contains the specific steps required to perform customizations to the firmware.

The following tasks are covered:
* Adding a Canvar
* Adding a Picture
* Writing a Canvar Callback
* Writing a Mode Function

## Adding a Canvar

Canvar definitions are stored in the `file` as Python objects. Adding a canvar is done by instantiating a Python `Variable` object and adding it to the list of `variables` in the file. Once this is completed, the variable can be used. If `<name>` is the variable's name, `cv_<name>` is the data structure which holds its value (a `canvar_state_t`) and `CV_ID_<name in uppercase>` is defined as its ID in the data structure array.

The `Variable` constructor has the following arguments:
* `name` is the name of the variable.
* `msg_id` is the 11-bit CAN message ID which contains the variable. If `None`, the variable has no associated ID and can only set with `app_canvar_interrupt`. The message is processed as little endian.
* `size` is the size, 1-32 bits, of the variable.
* `start` is the start, 0-63 bits, of the variable within the message. Bit 0 is LSB of byte 0 in the message, and bit 63 is MSB of byte 7 in the message.
* `signed=False`: if True, the variable is sign-extended to 32 bits.
* `multiplex=None` is the Multiplexer Value for this variable. If None, the message is not multiplexed.
* `callback=None` is the C function to call when this variable is updated with a new value. If None, nothing is called.

## Adding a Picture

Picture definitions are stored in the `file` as Python objects. Adding a picture is done by instantiating a Python `Picture` object and adding it to the `piclist` in the file. Once this is completed, the picture can be used. If `<name>` is the picture's name, its ID is defined as `PIC_ID_<name in uppercase>`. 

The `Picture` constructor has the following arguments:
* `path` is the file system path to the PNG file with the image data, relative to the `directory`.
* `name` is the name of the picture.
* `area=None` is the area of the original image to use, or None to use the whole image. It is a tuple with the following numbers, in pixels: `(<upper left corner of picture, x coordinate>, <upper left corner of picture, y coordinate>, <picture width>, <picture height>)`.

## Writing a Canvar Callback

When a canvar is changed, its callback is called to act on that change.

Callback functions have the following prototype: `void callback(uint32_t val)`, where `val` is the value of the canvar at the time the callback is called. It is sign or zero extended to 32 bits according to the `signed` parameter of the `Variable`.

The callback likely wants to change the screen based on the value of the canvar. Standard C functions like `sprintf` can be used to build the value, and the screen functions covered elsewhere can be used to update the screen. If the callback updates the screen in the mode area, it shuold check that `app_mode_change_func` equals the correct function, so that it only draws if the mode is actively being displayed.

The callback function is called with interrupts enabled. Interrupts can be disabled when necessary, but they should be enabled while screen functions are called.

If you want the canvar function to be called the next time the canvar is refreshed, even if the new value is the same as the old one, call `CV_CALL_NEXT_UPDATE(cv_<name>)` at the end of the function with interrupts disabled. Operations on other canvars are also possible.

## Writing a Mode Function

A mode function handles displaying and updating a dash mode. It has two jobs: to prepare the mode area of the screen for the current mode, and to update `app_mode_change_func` with the pointer to the next mode function.

Mode functions have the following prototype: `void mode_func(bool next)`. If `next` is `true`, the function should set `app_mode_change_func` to the next mode function and return. If `false`, the function can prepare the screen.

Preparing the screen usually involves drawing placeholder values and labels. The mode function should also call `CV_RENEW(cv_<name>)` with all of the canvars which are displayed in that mode, so that they will be immediately redrawn.