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


#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
#include <si5351.h>

void utilitiesInit();

bool parseClock(si5351_clock *clock, const char &c);

const char *u64Serialize(uint64_t value, char *dst = nullptr);

uint64_t u64Parse(const char *s, uint64_t initial = 0);

#endif
