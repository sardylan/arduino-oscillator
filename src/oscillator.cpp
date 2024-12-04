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


#include "oscillator.hpp"

Si5351 si5351;

void oscillatorInit() {
    si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
}

void oscillatorSetFrequency(const si5351_clock clock, const uint64_t frequency) {
    switch (clock) {
        case SI5351_CLK0:
            si5351.set_freq(frequency, SI5351_CLK0);
            break;

        case SI5351_CLK1:
            si5351.set_freq(frequency, SI5351_CLK1);
            break;

        case SI5351_CLK2:
            si5351.set_freq(frequency, SI5351_CLK2);
            break;

        default:
            break;
    }
}
