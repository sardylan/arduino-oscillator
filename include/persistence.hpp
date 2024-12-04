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


#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <si5351.h>

void persistenceInit();

uint64_t persistenceGetFrequency(si5351_clock clock);

void persistenceSetFrequency(si5351_clock clock, uint64_t frequency);

int persistenceGetAddress(si5351_clock clock);

uint64_t persistenceReadUInt64(int address);

void persistenceWriteUInt64(int address, uint64_t value);

#endif
