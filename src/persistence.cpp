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


#include "persistence.hpp"

#include <Arduino.h>
#include <EEPROM.h>

uint64_t clockFrequency0;
uint64_t clockFrequency1;
uint64_t clockFrequency2;

void persistenceInit() {
    clockFrequency0 = persistenceReadUInt64(persistenceGetAddress(SI5351_CLK0));
    clockFrequency1 = persistenceReadUInt64(persistenceGetAddress(SI5351_CLK1));
    clockFrequency2 = persistenceReadUInt64(persistenceGetAddress(SI5351_CLK2));
}

uint64_t persistenceGetFrequency(const si5351_clock clock) {
    switch (clock) {
        case SI5351_CLK0:
            return clockFrequency0;

        case SI5351_CLK1:
            return clockFrequency1;

        case SI5351_CLK2:
            return clockFrequency2;

        default:
            return 0;
    }
}

void persistenceSetFrequency(const si5351_clock clock, const uint64_t frequency) {
    switch (clock) {
        case SI5351_CLK0:
            clockFrequency0 = frequency;
            break;

        case SI5351_CLK1:
            clockFrequency1 = frequency;
            break;

        case SI5351_CLK2:
            clockFrequency2 = frequency;
            break;

        default:
            return;
    }

    persistenceWriteUInt64(persistenceGetAddress(clock), frequency);
}

int persistenceGetAddress(const si5351_clock clock) {
    switch (clock) {
        case SI5351_CLK0:
            return 0x00;
        case SI5351_CLK1:
            return 0x08;
        case SI5351_CLK2:
            return 0x10;
        default:
            return -1;
    }
}

uint64_t persistenceReadUInt64(const int address) {
    uint64_t value = 0;
    auto *ptr = reinterpret_cast<uint8_t *>(&value);

    *ptr = EEPROM.read(address);
    *(ptr + 1) = EEPROM.read(address + 1);
    *(ptr + 2) = EEPROM.read(address + 2);
    *(ptr + 3) = EEPROM.read(address + 3);
    *(ptr + 4) = EEPROM.read(address + 4);
    *(ptr + 5) = EEPROM.read(address + 5);
    *(ptr + 6) = EEPROM.read(address + 6);
    *(ptr + 7) = EEPROM.read(address + 7);

    return value;
}

void persistenceWriteUInt64(const int address, const uint64_t value) {
    const auto *ptr = reinterpret_cast<const uint8_t *>(&value);

    EEPROM.write(address, *ptr);
    EEPROM.write(address + 1, *(ptr + 1));
    EEPROM.write(address + 2, *(ptr + 2));
    EEPROM.write(address + 3, *(ptr + 3));
    EEPROM.write(address + 4, *(ptr + 4));
    EEPROM.write(address + 5, *(ptr + 5));
    EEPROM.write(address + 6, *(ptr + 6));
    EEPROM.write(address + 7, *(ptr + 7));
}
