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


#include "main.hpp"

#include <Arduino.h>
#include <si5351.h>

#include "log.hpp"
#include "version.hpp"
#include "config.hpp"
#include "oscillator.hpp"
#include "persistence.hpp"
#include "utilities.hpp"

char serialBuffer[SERIAL_BUFFER_SIZE];
size_t serialBufferPos = 0;

void setup() {
    Serial.begin(SERIAL_SPEED);

    logInfo("QO-100 Arduino version %s (build %s %s)", VERSION, __DATE__, __TIME__);
    logInfo("Initializing");

    logDebug("Initializing utilities...");
    utilitiesInit();

    logDebug("Initializing oscillator...");
    oscillatorInit();

    logDebug("Creating persistence...");
    persistenceInit();

    ledInit();
    ledOff();

    logDebug("Setting oscillator frequencies...");
    updateOscillatorFrequency(SI5351_CLK0);
    updateOscillatorFrequency(SI5351_CLK1);
    updateOscillatorFrequency(SI5351_CLK2);

    ledOn();

    logDebug("Completed!!!!");
}

void loop() {
    while (Serial.available()) {
        ledOff();

        const int c = Serial.read();
#ifdef SERIAL_ENABLE_ECHO
        Serial.print(static_cast<char>(c));
#endif

        switch (c) {
            case -1:
                continue;

            case '\n':
            case '\r':
                parseCommand();
                memset(serialBuffer, '\0', SERIAL_BUFFER_SIZE);
                serialBufferPos = 0;
                break;

            default:
                serialBuffer[serialBufferPos++] = static_cast<char>(c);
        }

        ledOn();
    }
}

void parseCommand() {
    if (serialBufferPos == 0)
        return;

    const size_t size = strlen(serialBuffer);
    if (size == 0)
        return;

    switch (serialBuffer[0]) {
        case 'F': {
            si5351_clock clock;
            if (!parseClock(&clock, serialBuffer[1])) {
                Serial.println("Invalid clock");
                return;
            }

            const uint64_t frequency = u64Parse(&serialBuffer[2]);
            persistenceSetFrequency(clock, frequency);

            updateOscillatorFrequency(clock);

            output("Frequency set: %s", u64Serialize(persistenceGetFrequency(clock)));
        }
        break;

        case 'f': {
            si5351_clock clock;
            if (!parseClock(&clock, serialBuffer[1])) {
                Serial.println("Invalid clock");
                return;
            }

            output("Frequency: %s", u64Serialize(persistenceGetFrequency(clock)));
        }
        break;

        default:
            return;
    }
}

void updateOscillatorFrequency(const si5351_clock clock) {
    oscillatorSetFrequency(clock, persistenceGetFrequency(clock));
}

void output(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char outputBuffer[OUTPUT_BUFFER_SIZE];
    vsnprintf(outputBuffer, OUTPUT_BUFFER_SIZE, format, args);
    va_end(args);
    Serial.println(outputBuffer);
}
