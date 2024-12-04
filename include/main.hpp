/*
 * Copyright (C) 2024 Luca Cireddu <sardylan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */


#ifndef MAIN_H
#define MAIN_H

#include <si5351.h>

#define OUTPUT_BUFFER_SIZE 256

#define ledInit() pinMode(LED_BUILTIN, OUTPUT)
#define ledOff() digitalWrite(LED_BUILTIN, LOW)
#define ledOn() digitalWrite(LED_BUILTIN, HIGH)

void parseCommand();

void updateOscillatorFrequency(si5351_clock clock);

void output(const char *format, ...);

#endif
