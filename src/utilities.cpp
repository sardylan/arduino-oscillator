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


#include "utilities.hpp"

char charBuffer[21];
static uint64_t pow10[20];

void utilitiesInit() {
    pow10[0] = 1;
    pow10[1] = 10;
    pow10[2] = 100;
    pow10[3] = 1000;
    pow10[4] = 10000;
    pow10[5] = 100000;
    pow10[6] = 1000000;
    pow10[7] = 10000000;
    pow10[8] = 100000000;
    pow10[9] = 1000000000;
    pow10[10] = 10000000000;
    pow10[11] = 100000000000;
    pow10[12] = 1000000000000;
    pow10[13] = 10000000000000;
    pow10[14] = 100000000000000;
    pow10[15] = 1000000000000000;
    pow10[16] = 10000000000000000;
    pow10[17] = 100000000000000000;
    pow10[18] = 1000000000000000000;
    pow10[19] = 10000000000000000000;
}

bool parseClock(si5351_clock *clock, const char &c) {
    switch (c) {
        case '0':
            *clock = SI5351_CLK0;
            return true;

        case '1':
            *clock = SI5351_CLK1;
            return true;

        case '2':
            *clock = SI5351_CLK2;
            return true;

        default:
            return false;
    }
}

const char *u64Serialize(const uint64_t value, char *dst) {
    if (dst == nullptr) {
        memset(charBuffer, '\0', sizeof(charBuffer));
        dst = &charBuffer[19];
    }

    *dst = static_cast<char>('0' + value % 10);
    if (value < 10)
        return dst;
    return u64Serialize(value / 10, dst - 1);
}

uint64_t u64Parse(const char *s, const uint64_t initial) {
    if (s == nullptr) return 0;

    const size_t len = strlen(s);
    if (*s < '0' || *s > '9' || len == 0)
        return initial;

    return u64Parse(s + 1, initial + (*s - '0') * pow10[len - 1]);
}
