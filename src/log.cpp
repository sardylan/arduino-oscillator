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


#include "log.hpp"

#include <Arduino.h>

void logMessage(const LogLevel level, const char *filename, const int line, const char *format, ...) {
    char bufLevel[6];
    switch (level) {
        case OFF:
            sprintf(bufLevel, " OFF ");
            break;
        case ERROR:
            sprintf(bufLevel, " ERR ");
            break;
        case WARNING:
            sprintf(bufLevel, "WARN ");
            break;
        case INFO:
            sprintf(bufLevel, "INFO ");
            break;
        case DEBUG:
            sprintf(bufLevel, "DEBUG");
            break;
        case TRACE:
            sprintf(bufLevel, "TRACE");
            break;
    }

    va_list args;
    va_start(args, format);
    char bufFormat[LOG_BUFFER_FORMAT_SIZE];
    vsnprintf(bufFormat, LOG_BUFFER_FORMAT_SIZE, format, args);
    va_end(args);

    char buf[LOG_BUFFER_SIZE];
    snprintf(buf, LOG_BUFFER_SIZE, "%010lu [%s] %s:%d: %s", millis(), bufLevel, filename, line, bufFormat);
    Serial.println(buf);
}
