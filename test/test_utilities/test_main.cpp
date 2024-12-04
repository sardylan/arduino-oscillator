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


#include <Arduino.h>
#include <unity.h>
#include <si5351.h>

#include "utilities.hpp"
#include "utilities.cpp"

uint64_t testExpected;
uint64_t testActual;

#define testAssertEqualU64(expected, actual) \
    testExpected = expected; \
    testActual = actual; \
    TEST_ASSERT_EQUAL_STRING_LEN(&testExpected, &testActual, sizeof(uint64_t))

void testParseClock0() {
    si5351_clock *actual = nullptr;
    const bool result = parseClock(actual, '0');
    TEST_ASSERT_EQUAL(true, result);
    TEST_ASSERT_EQUAL(SI5351_CLK0, *actual);
}

void testParseClock1() {
    si5351_clock *actual = nullptr;
    const bool result = parseClock(actual, '1');
    TEST_ASSERT_EQUAL(true, result);
    TEST_ASSERT_EQUAL(SI5351_CLK1, *actual);
}

void testParseClock2() {
    si5351_clock *actual = nullptr;
    const bool result = parseClock(actual, '2');
    TEST_ASSERT_EQUAL(true, result);
    TEST_ASSERT_EQUAL(SI5351_CLK2, *actual);
}

void testU64Serialize() {
    TEST_ASSERT_EQUAL_STRING("0", u64Serialize(0LLU));
    TEST_ASSERT_EQUAL_STRING("1", u64Serialize(1LLU));
    TEST_ASSERT_EQUAL_STRING("10", u64Serialize(10LLU));
    TEST_ASSERT_EQUAL_STRING("100", u64Serialize(100LLU));
    TEST_ASSERT_EQUAL_STRING("18446744073709551615", u64Serialize(18446744073709551615LLU));
}

void testU64Parse() {
    testAssertEqualU64(0LLU, u64Parse("0"));
    testAssertEqualU64(0LLU, u64Parse("00"));
    testAssertEqualU64(0LLU, u64Parse("0000"));
    testAssertEqualU64(0LLU, u64Parse("000000000000"));
    testAssertEqualU64(1LLU, u64Parse("1"));
    testAssertEqualU64(1LLU, u64Parse("01"));
    testAssertEqualU64(1LLU, u64Parse("000000000001"));
    testAssertEqualU64(10LLU, u64Parse("10"));
    testAssertEqualU64(10LLU, u64Parse("010"));
    testAssertEqualU64(18446744073709551615LLU, u64Parse("18446744073709551615"));
}

void setup() {
    utilitiesInit();

    UNITY_BEGIN();

    RUN_TEST(testParseClock0);
    RUN_TEST(testParseClock1);
    RUN_TEST(testParseClock2);

    RUN_TEST(testU64Serialize);
    RUN_TEST(testU64Parse);

    UNITY_END();
}

void loop() {
}
