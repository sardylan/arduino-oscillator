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


#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

#include "config.hpp"

#define LOG_BUFFER_FORMAT_SIZE 192
#define LOG_BUFFER_SIZE 256

enum LogLevel {
    OFF = 0,
    ERROR = 1,
    WARNING = 2,
    INFO = 3,
    DEBUG = 4,
    TRACE = 5
};

void logMessage(LogLevel level, const char *filename, int line, const char *format, ...);

#ifdef LOG_ENABLE_ERROR
#define  logError(x, ...) logMessage(ERROR, __FILE__, __LINE__, x, ##__VA_ARGS__);
#else
#define  logError(x, ...)
#endif

#ifdef LOG_ENABLE_WARNING
#define  logWarning(x, ...) logMessage(WARNING, __FILE__, __LINE__, x, ##__VA_ARGS__);
#else
#define  logWarning(x, ...)
#endif

#ifdef LOG_ENABLE_INFO
#define  logInfo(x, ...) logMessage(INFO, __FILE__, __LINE__, x, ##__VA_ARGS__);
#else
#define  logInfo(x, ...)
#endif

#ifdef LOG_ENABLE_DEBUG
#define  logDebug(x, ...) logMessage(DEBUG, __FILE__, __LINE__, x, ##__VA_ARGS__);
#else
#define  logDebug(x, ...)
#endif

#ifdef LOG_ENABLE_TRACE
#define  logTrace(x, ...) logMessage(TRACE, __FILE__, __LINE__, x, ##__VA_ARGS__);
#else
#define  logTrace(x, ...)
#endif


#endif
