#include <check.h>
#include <limits.h>
#include <math.h>

#include "s21_decimal.h"

// Функции сравнения:

START_TEST(s21_is_greater_1) {
  s21_decimal value_1 = {{123, 1, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{12, 1, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_3) {
  s21_decimal value_1 = {{12, 1, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 1, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_6) {
  s21_decimal value_1 = {{123456, 1, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456, 1, 0xFFFFFFFF, 0x10000}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_7) {
  s21_decimal value_1 = {{234, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_8) {
  s21_decimal value_1 = {{234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{2, 0, 0, 0x80000000}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_9) {
  s21_decimal value_1 = {{234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{20, 0, 0, 0x10000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
  s21_decimal value_1 = {{123457, 1, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456, 1, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0x200000}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_3) {
  s21_decimal value_1 = {{12345, 654, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{12, 654, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal value_1 = {{123456, 6, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123, 6, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 3454334633}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_7) {
  s21_decimal value_1 = {{123456, 6, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456, 6, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal value_1 = {{12346, 6, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{12345, 6, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {
  s21_decimal value_1 = {{0, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_9) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_not_equal_1) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_not_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_is_not_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

// Тесты на арифметические операции:

START_TEST(s21_add_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 10, y = 10, z = 20, result_int = 0;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, z);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result.bits[0], 4294967294);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 2;
  float result_float = 0, y = 1.2345678, z = x + y;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_float_to_decimal(y, &value_2);
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(fabs((result_float - z)) < 1e-6, 1);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{1, 1, 1, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_sub_111) {
  s21_decimal value_1 = {{0, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result), x = 0;
  s21_from_decimal_to_int(result, &x);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  for (int i = 0; i < 3; i++) ck_assert_int_eq(result.bits[i], 0xFFFFFFFF - 1);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 10, y = 2147483638, result_int = 0;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, -2147483628);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0] + result.bits[1] + result.bits[2], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 2;
  float result_float = 0, y = 1.2345678, z = x - 1.2345678;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_float_to_decimal(y, &value_2);
  int return_value = s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(fabs((result_float - z)) < 1e-6, 1);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_div_1) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_div(value_1, value_2, &result);
  float result_float = 0;
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(fabs((result_float - 1)) < 1e-7, 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_from_int_to_decimal(1, &value_1);
  int return_value = s21_div(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_div(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal value_2 = {0};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int x = 2, y = 3;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_div(value_1, value_2, &result);
  float result_float = 0;
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(fabs((result_float - 0.66666)) < 1e-4, 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int return_value = s21_div(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(0.1, &value_2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_mul_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result), result_int = 0;
  ck_assert_int_eq(return_value, 0);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_mod_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_mod(value_2, value_1, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(result_int, 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mod_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_mod(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_mod_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(0.1, &value_1);
  int return_value = s21_mod(value_2, value_1, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mod_4) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(-0.1, &value_1);
  int return_value = s21_mod(value_1, value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_negate_1) {
  s21_decimal value_2 = {{0, 0, 1, 0x80000000}};
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(value_1, result), 1);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal value_2 = {{0, 0, 1, 0x80000000}};
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
}
END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal value_2 = {{0, 0, 0, 0x80020000}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_truncate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(value_2, value_1), 1);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal value_2 = {0};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(0.1111000, &value_2);
  int return_value = s21_truncate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_1), 1);
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(1.7111000, &value_2);
  int return_value = s21_round(value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, 2);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80020000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(2.2, &value_2);
  int return_value = s21_round(value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, 2);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal value_2 = {{15, 0, 0, pow(2, 16)}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal value_2 = {{15, 0, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal value_2 = {{UINT_MAX, UINT_MAX, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_1) {
  float src = 0.0000000;
  s21_decimal value_1 = {{0xffffff, 0xffffff, 0xffffff, 0xffffff}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &value_1);
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  float src = 1.23456789999;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {0};
  return_value = s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 1e-06);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  float src = 7.92281625143e+27f;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  return_value = s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(7922816.0f, temp, 1e-06);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  float src = 7.92281625143e+30;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  return_value = s21_from_float_to_decimal(src, &value_1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  float src = 7.92281577919e+28;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(7922816.0f, temp, 1e-06);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  float src = 1e-29f;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  return_value = s21_from_float_to_decimal(src, &value_1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

// s21_from_int_to_decimal

START_TEST(s21_from_int_to_decimal_1) {
  int src = -2147483647;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  int src = -0;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  int src = 101;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_4) {
  int src = -31325;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

// s21_from_decimal_to_int_1

START_TEST(s21_from_decimal_to_int_1) {
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 1, 0}};
  return_value = s21_from_decimal_to_int(value_1, &temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  int src = 0;
  int temp = 100;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  int src = 0;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0x80000000, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  int src = 133;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0x85, 0, 0, 0}};
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

// s21_from_decimal_to_float

START_TEST(s21_from_decimal_to_float_1) {
  float src = 0.00000000000;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_decimal_to_float(value_1, &temp);
  if (fabs(src - temp) < pow(10, -7)) {
    return_value = 1;
  }
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  float src = 0.0001;
  float temp = 0;
  s21_decimal value_1 = {{1, 0, 0, 0b00000000000001000000000000000000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  float src = 0.0000000000000123;
  float temp = 0;
  s21_decimal value_1 = {{123, 0, 0, 0b00000000000100000000000000000000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  float src = -0.0001;
  float temp = 0;
  s21_decimal value_1 = {{1, 0, 0, 0b10000000000001000000000000000000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 10e-7);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");

  TCase *tc_is_greater_1;
  tc_is_greater_1 = tcase_create("s21_is_greater_1");
  suite_add_tcase(s, tc_is_greater_1);
  tcase_add_test(tc_is_greater_1, s21_is_greater_1);

  TCase *tc_is_greater_2;
  tc_is_greater_2 = tcase_create("s21_is_greater_2");
  suite_add_tcase(s, tc_is_greater_2);
  tcase_add_test(tc_is_greater_2, s21_is_greater_2);

  TCase *tc_is_greater_3;
  tc_is_greater_3 = tcase_create("s21_is_greater_3");
  suite_add_tcase(s, tc_is_greater_3);
  tcase_add_test(tc_is_greater_3, s21_is_greater_3);

  TCase *tc_is_greater_4;
  tc_is_greater_4 = tcase_create("s21_is_greater_4");
  suite_add_tcase(s, tc_is_greater_4);
  tcase_add_test(tc_is_greater_4, s21_is_greater_4);

  TCase *tc_is_greater_5;
  tc_is_greater_5 = tcase_create("s21_is_greater_5");
  suite_add_tcase(s, tc_is_greater_5);
  tcase_add_test(tc_is_greater_5, s21_is_greater_5);

  TCase *tc_is_greater_6;
  tc_is_greater_6 = tcase_create("s21_is_greater_6");
  suite_add_tcase(s, tc_is_greater_6);
  tcase_add_test(tc_is_greater_6, s21_is_greater_6);

  TCase *tc_is_greater_7;
  tc_is_greater_7 = tcase_create("s21_is_greater_7");
  suite_add_tcase(s, tc_is_greater_7);
  tcase_add_test(tc_is_greater_7, s21_is_greater_7);

  TCase *tc_is_greater_8;
  tc_is_greater_8 = tcase_create("s21_is_greater_8");
  suite_add_tcase(s, tc_is_greater_8);
  tcase_add_test(tc_is_greater_8, s21_is_greater_8);

  TCase *tc_is_greater_9;
  tc_is_greater_9 = tcase_create("s21_is_greater_9");
  suite_add_tcase(s, tc_is_greater_9);
  tcase_add_test(tc_is_greater_9, s21_is_greater_9);

  TCase *tc_is_equal_1;
  tc_is_equal_1 = tcase_create("s21_is_equal_1");
  suite_add_tcase(s, tc_is_equal_1);
  tcase_add_test(tc_is_equal_1, s21_is_equal_1);

  TCase *tc_is_equal_2;
  tc_is_equal_2 = tcase_create("s21_is_equal_2");
  suite_add_tcase(s, tc_is_equal_2);
  tcase_add_test(tc_is_equal_2, s21_is_equal_2);

  TCase *tc_is_equal_3;
  tc_is_equal_3 = tcase_create("s21_is_equal_3");
  suite_add_tcase(s, tc_is_equal_3);
  tcase_add_test(tc_is_equal_3, s21_is_equal_3);

  TCase *tc_is_equal_4;
  tc_is_equal_4 = tcase_create("s21_is_equal_4");
  suite_add_tcase(s, tc_is_equal_4);
  tcase_add_test(tc_is_equal_4, s21_is_equal_4);

  TCase *tc_is_equal_5;
  tc_is_equal_5 = tcase_create("s21_is_equal_5");
  suite_add_tcase(s, tc_is_equal_5);
  tcase_add_test(tc_is_equal_5, s21_is_equal_5);

  TCase *tc_is_greater_or_equal_1;
  tc_is_greater_or_equal_1 = tcase_create("s21_is_greater_or_equal_1");
  suite_add_tcase(s, tc_is_greater_or_equal_1);
  tcase_add_test(tc_is_greater_or_equal_1, s21_is_greater_or_equal_1);

  TCase *tc_is_greater_or_equal_2;
  tc_is_greater_or_equal_2 = tcase_create("s21_is_greater_or_equal_2");
  suite_add_tcase(s, tc_is_greater_or_equal_2);
  tcase_add_test(tc_is_greater_or_equal_2, s21_is_greater_or_equal_2);

  TCase *tc_is_greater_or_equal_3;
  tc_is_greater_or_equal_3 = tcase_create("s21_is_greater_or_equal_3");
  suite_add_tcase(s, tc_is_greater_or_equal_3);
  tcase_add_test(tc_is_greater_or_equal_3, s21_is_greater_or_equal_3);

  TCase *tc_is_greater_or_equal_4;
  tc_is_greater_or_equal_4 = tcase_create("s21_is_greater_or_equal_4");
  suite_add_tcase(s, tc_is_greater_or_equal_4);
  tcase_add_test(tc_is_greater_or_equal_4, s21_is_greater_or_equal_4);

  TCase *tc_is_greater_or_equal_5;
  tc_is_greater_or_equal_5 = tcase_create("s21_is_greater_or_equal_5");
  suite_add_tcase(s, tc_is_greater_or_equal_5);
  tcase_add_test(tc_is_greater_or_equal_5, s21_is_greater_or_equal_5);

  TCase *tc_is_greater_or_equal_6;
  tc_is_greater_or_equal_6 = tcase_create("s21_is_greater_or_equal_6");
  suite_add_tcase(s, tc_is_greater_or_equal_6);
  tcase_add_test(tc_is_greater_or_equal_6, s21_is_greater_or_equal_6);

  TCase *tc_is_greater_or_equal_7;
  tc_is_greater_or_equal_7 = tcase_create("s21_is_greater_or_equal_7");
  suite_add_tcase(s, tc_is_greater_or_equal_7);
  tcase_add_test(tc_is_greater_or_equal_7, s21_is_greater_or_equal_7);

  TCase *tc_is_less_1;
  tc_is_less_1 = tcase_create("s21_is_less_1");
  suite_add_tcase(s, tc_is_less_1);
  tcase_add_test(tc_is_less_1, s21_is_less_1);

  TCase *tc_is_less_2;
  tc_is_less_2 = tcase_create("s21_is_less_2");
  suite_add_tcase(s, tc_is_less_2);
  tcase_add_test(tc_is_less_2, s21_is_less_2);

  TCase *tc_is_less_3;
  tc_is_less_3 = tcase_create("s21_is_less_3");
  suite_add_tcase(s, tc_is_less_3);
  tcase_add_test(tc_is_less_3, s21_is_less_3);

  TCase *tc_is_less_4;
  tc_is_less_4 = tcase_create("s21_is_less_4");
  suite_add_tcase(s, tc_is_less_4);
  tcase_add_test(tc_is_less_4, s21_is_less_4);

  TCase *tc_is_less_5;
  tc_is_less_5 = tcase_create("s21_is_less_5");
  suite_add_tcase(s, tc_is_less_5);
  tcase_add_test(tc_is_less_5, s21_is_less_5);

  TCase *tc_is_less_6;
  tc_is_less_6 = tcase_create("s21_is_less_6");
  suite_add_tcase(s, tc_is_less_6);
  tcase_add_test(tc_is_less_6, s21_is_less_6);

  TCase *tc_is_less_7;
  tc_is_less_7 = tcase_create("s21_is_less_7");
  suite_add_tcase(s, tc_is_less_7);
  tcase_add_test(tc_is_less_7, s21_is_less_7);

  TCase *tc_is_less_or_equal_1;
  tc_is_less_or_equal_1 = tcase_create("s21_is_less_or_equal_1");
  suite_add_tcase(s, tc_is_less_or_equal_1);
  tcase_add_test(tc_is_less_or_equal_1, s21_is_less_or_equal_1);

  TCase *tc_is_less_or_equal_2;
  tc_is_less_or_equal_2 = tcase_create("s21_is_less_or_equal_2");
  suite_add_tcase(s, tc_is_less_or_equal_2);
  tcase_add_test(tc_is_less_or_equal_2, s21_is_less_or_equal_2);

  TCase *tc_is_less_or_equal_3;
  tc_is_less_or_equal_3 = tcase_create("s21_is_less_or_equal_3");
  suite_add_tcase(s, tc_is_less_or_equal_3);
  tcase_add_test(tc_is_less_or_equal_3, s21_is_less_or_equal_3);

  TCase *tc_is_less_or_equal_4;
  tc_is_less_or_equal_4 = tcase_create("s21_is_less_or_equal_4");
  suite_add_tcase(s, tc_is_less_or_equal_4);
  tcase_add_test(tc_is_less_or_equal_4, s21_is_less_or_equal_4);

  TCase *tc_is_less_or_equal_5;
  tc_is_less_or_equal_5 = tcase_create("s21_is_less_or_equal_5");
  suite_add_tcase(s, tc_is_less_or_equal_5);
  tcase_add_test(tc_is_less_or_equal_5, s21_is_less_or_equal_5);

  TCase *tc_is_less_or_equal_6;
  tc_is_less_or_equal_6 = tcase_create("s21_is_less_or_equal_6");
  suite_add_tcase(s, tc_is_less_or_equal_6);
  tcase_add_test(tc_is_less_or_equal_6, s21_is_less_or_equal_6);

  TCase *tc_is_less_or_equal_7;
  tc_is_less_or_equal_7 = tcase_create("s21_is_less_or_equal_7");
  suite_add_tcase(s, tc_is_less_or_equal_7);
  tcase_add_test(tc_is_less_or_equal_7, s21_is_less_or_equal_7);

  TCase *tc_is_less_or_equal_8;
  tc_is_less_or_equal_8 = tcase_create("s21_is_less_or_equal_8");
  suite_add_tcase(s, tc_is_less_or_equal_8);
  tcase_add_test(tc_is_less_or_equal_8, s21_is_less_or_equal_8);

  TCase *tc_is_less_or_equal_9;
  tc_is_less_or_equal_9 = tcase_create("s21_is_less_or_equal_9");
  suite_add_tcase(s, tc_is_less_or_equal_9);
  tcase_add_test(tc_is_less_or_equal_9, s21_is_less_or_equal_9);

  TCase *tc_is_not_equal_1;
  tc_is_not_equal_1 = tcase_create("s21_is_not_equal_1");
  suite_add_tcase(s, tc_is_not_equal_1);
  tcase_add_test(tc_is_not_equal_1, s21_is_not_equal_1);

  TCase *tc_is_not_equal_2;
  tc_is_not_equal_2 = tcase_create("s21_is_not_equal_2");
  suite_add_tcase(s, tc_is_not_equal_2);
  tcase_add_test(tc_is_not_equal_2, s21_is_not_equal_2);

  TCase *tc_is_not_equal_3;
  tc_is_not_equal_3 = tcase_create("s21_is_not_equal_3");
  suite_add_tcase(s, tc_is_not_equal_3);
  tcase_add_test(tc_is_not_equal_3, s21_is_not_equal_3);

  TCase *tc_is_not_equal_4;
  tc_is_not_equal_4 = tcase_create("s21_is_not_equal_4");
  suite_add_tcase(s, tc_is_not_equal_4);
  tcase_add_test(tc_is_not_equal_4, s21_is_not_equal_4);

  TCase *tc_is_not_equal_5;
  tc_is_not_equal_5 = tcase_create("s21_is_not_equal_5");
  suite_add_tcase(s, tc_is_not_equal_5);
  tcase_add_test(tc_is_not_equal_5, s21_is_not_equal_5);

  TCase *tc_add_1;
  tc_add_1 = tcase_create("s21_add_1");
  suite_add_tcase(s, tc_add_1);
  tcase_add_test(tc_add_1, s21_add_1);

  TCase *tc_add_2;
  tc_add_2 = tcase_create("s21_add_2");
  suite_add_tcase(s, tc_add_2);
  tcase_add_test(tc_add_2, s21_add_2);

  TCase *tc_add_3;
  tc_add_3 = tcase_create("s21_add_3");
  suite_add_tcase(s, tc_add_3);
  tcase_add_test(tc_add_3, s21_add_3);

  TCase *tc_add_4;
  tc_add_4 = tcase_create("s21_add_4");
  suite_add_tcase(s, tc_add_4);
  tcase_add_test(tc_add_4, s21_add_4);

  TCase *tc_add_5;
  tc_add_5 = tcase_create("s21_add_5");
  suite_add_tcase(s, tc_add_5);
  tcase_add_test(tc_add_5, s21_add_5);

  TCase *tc_add_6;
  tc_add_6 = tcase_create("s21_add_6");
  suite_add_tcase(s, tc_add_6);
  tcase_add_test(tc_add_6, s21_add_6);

  TCase *tc_add_7;
  tc_add_7 = tcase_create("s21_add_7");
  suite_add_tcase(s, tc_add_7);
  tcase_add_test(tc_add_7, s21_add_7);

  TCase *tc_sub_111;
  tc_sub_111 = tcase_create("s21_sub_111");
  suite_add_tcase(s, tc_sub_111);
  tcase_add_test(tc_sub_111, s21_sub_111);

  TCase *tc_sub_2;
  tc_sub_2 = tcase_create("s21_sub_2");
  suite_add_tcase(s, tc_sub_2);
  tcase_add_test(tc_sub_2, s21_sub_2);

  TCase *tc_sub_3;
  tc_sub_3 = tcase_create("s21_sub_3");
  suite_add_tcase(s, tc_sub_3);
  tcase_add_test(tc_sub_3, s21_sub_3);

  TCase *tc_sub_4;
  tc_sub_4 = tcase_create("s21_sub_4");
  suite_add_tcase(s, tc_sub_4);
  tcase_add_test(tc_sub_4, s21_sub_4);

  TCase *tc_sub_5;
  tc_sub_5 = tcase_create("s21_sub_5");
  suite_add_tcase(s, tc_sub_5);
  tcase_add_test(tc_sub_5, s21_sub_5);

  TCase *tc_sub_6;
  tc_sub_6 = tcase_create("s21_sub_6");
  suite_add_tcase(s, tc_sub_6);
  tcase_add_test(tc_sub_6, s21_sub_6);

  TCase *tc_sub_7;
  tc_sub_7 = tcase_create("s21_sub_7");
  suite_add_tcase(s, tc_sub_7);
  tcase_add_test(tc_sub_7, s21_sub_7);

  TCase *tc_div_1;
  tc_div_1 = tcase_create("s21_div_1");
  suite_add_tcase(s, tc_div_1);
  tcase_add_test(tc_div_1, s21_div_1);

  TCase *tc_div_2;
  tc_div_2 = tcase_create("s21_div_2");
  suite_add_tcase(s, tc_div_2);
  tcase_add_test(tc_div_2, s21_div_2);

  TCase *tc_div_3;
  tc_div_3 = tcase_create("s21_div_3");
  suite_add_tcase(s, tc_div_3);
  tcase_add_test(tc_div_3, s21_div_3);

  TCase *tc_div_4;
  tc_div_4 = tcase_create("s21_div_4");
  suite_add_tcase(s, tc_div_4);
  tcase_add_test(tc_div_4, s21_div_4);

  TCase *tc_div_5;
  tc_div_5 = tcase_create("s21_div_5");
  suite_add_tcase(s, tc_div_5);
  tcase_add_test(tc_div_5, s21_div_5);

  TCase *tc_div_6;
  tc_div_6 = tcase_create("s21_div_6");
  suite_add_tcase(s, tc_div_6);
  tcase_add_test(tc_div_6, s21_div_6);

  TCase *tc_mul_1;
  tc_mul_1 = tcase_create("s21_mul_1");
  suite_add_tcase(s, tc_mul_1);
  tcase_add_test(tc_mul_1, s21_mul_1);

  TCase *tc_mul_2;
  tc_mul_2 = tcase_create("s21_mul_2");
  suite_add_tcase(s, tc_mul_2);
  tcase_add_test(tc_mul_2, s21_mul_2);

  TCase *tc_mul_3;
  tc_mul_3 = tcase_create("s21_mul_3");
  suite_add_tcase(s, tc_mul_3);
  tcase_add_test(tc_mul_3, s21_mul_3);

  TCase *tc_mod_1;
  tc_mod_1 = tcase_create("s21_mod_1");
  suite_add_tcase(s, tc_mod_1);
  tcase_add_test(tc_mod_1, s21_mod_1);

  TCase *tc_mod_2;
  tc_mod_2 = tcase_create("s21_mod_2");
  suite_add_tcase(s, tc_mod_2);
  tcase_add_test(tc_mod_2, s21_mod_2);

  TCase *tc_mod_3;
  tc_mod_3 = tcase_create("s21_mod_3");
  suite_add_tcase(s, tc_mod_3);
  tcase_add_test(tc_mod_3, s21_mod_3);

  TCase *tc_mod_4;
  tc_mod_4 = tcase_create("s21_mod_4");
  suite_add_tcase(s, tc_mod_4);
  tcase_add_test(tc_mod_4, s21_mod_4);

  TCase *tc_negate_1;
  tc_negate_1 = tcase_create("s21_negate_1");
  suite_add_tcase(s, tc_negate_1);
  tcase_add_test(tc_negate_1, s21_negate_1);

  TCase *tc_negate_2;
  tc_negate_2 = tcase_create("s21_negate_2");
  suite_add_tcase(s, tc_negate_2);
  tcase_add_test(tc_negate_2, s21_negate_2);

  TCase *tc_truncate_1;
  tc_truncate_1 = tcase_create("s21_truncate_1");
  suite_add_tcase(s, tc_truncate_1);
  tcase_add_test(tc_truncate_1, s21_truncate_1);

  TCase *tc_truncate_2;
  tc_truncate_2 = tcase_create("s21_truncate_2");
  suite_add_tcase(s, tc_truncate_2);
  tcase_add_test(tc_truncate_2, s21_truncate_2);

  TCase *tc_round_1;
  tc_round_1 = tcase_create("s21_round_1");
  suite_add_tcase(s, tc_round_1);
  tcase_add_test(tc_round_1, s21_round_1);

  TCase *tc_round_2;
  tc_round_2 = tcase_create("s21_round_2");
  suite_add_tcase(s, tc_round_2);
  tcase_add_test(tc_round_2, s21_round_2);

  TCase *tc_round_3;
  tc_round_3 = tcase_create("s21_round_3");
  suite_add_tcase(s, tc_round_3);
  tcase_add_test(tc_round_3, s21_round_3);

  TCase *tc_round_4;
  tc_round_4 = tcase_create("s21_round_4");
  suite_add_tcase(s, tc_round_4);
  tcase_add_test(tc_round_4, s21_round_4);

  TCase *tc_round_5;
  tc_round_5 = tcase_create("s21_round_5");
  suite_add_tcase(s, tc_round_5);
  tcase_add_test(tc_round_5, s21_round_5);

  TCase *tc_round_6;
  tc_round_6 = tcase_create("s21_round_6");
  suite_add_tcase(s, tc_round_6);
  tcase_add_test(tc_round_6, s21_round_6);

  TCase *tc_floor_1;
  tc_floor_1 = tcase_create("s21_floor_1");
  suite_add_tcase(s, tc_floor_1);
  tcase_add_test(tc_floor_1, s21_floor_1);

  TCase *tc_floor_2;
  tc_floor_2 = tcase_create("s21_floor_2");
  suite_add_tcase(s, tc_floor_2);
  tcase_add_test(tc_floor_2, s21_floor_2);

  TCase *tc_floor_3;
  tc_floor_3 = tcase_create("s21_floor_3");
  suite_add_tcase(s, tc_floor_3);
  tcase_add_test(tc_floor_3, s21_floor_3);

  TCase *tc_floor_4;
  tc_floor_4 = tcase_create("s21_floor_4");
  suite_add_tcase(s, tc_floor_4);
  tcase_add_test(tc_floor_4, s21_floor_4);

  TCase *tc_from_float_to_decimal_1;
  tc_from_float_to_decimal_1 = tcase_create("s21_from_float_to_decimal_1");
  suite_add_tcase(s, tc_from_float_to_decimal_1);
  tcase_add_test(tc_from_float_to_decimal_1, s21_from_float_to_decimal_1);

  TCase *tc_from_float_to_decimal_2;
  tc_from_float_to_decimal_2 = tcase_create("s21_from_float_to_decimal_2");
  suite_add_tcase(s, tc_from_float_to_decimal_2);
  tcase_add_test(tc_from_float_to_decimal_2, s21_from_float_to_decimal_2);

  TCase *tc_from_float_to_decimal_3;
  tc_from_float_to_decimal_3 = tcase_create("s21_from_float_to_decimal_3");
  suite_add_tcase(s, tc_from_float_to_decimal_3);
  tcase_add_test(tc_from_float_to_decimal_3, s21_from_float_to_decimal_3);

  TCase *tc_from_float_to_decimal_4;
  tc_from_float_to_decimal_4 = tcase_create("s21_from_float_to_decimal_4");
  suite_add_tcase(s, tc_from_float_to_decimal_4);
  tcase_add_test(tc_from_float_to_decimal_4, s21_from_float_to_decimal_4);

  TCase *tc_from_float_to_decimal_5;
  tc_from_float_to_decimal_5 = tcase_create("s21_from_float_to_decimal_5");
  suite_add_tcase(s, tc_from_float_to_decimal_5);
  tcase_add_test(tc_from_float_to_decimal_5, s21_from_float_to_decimal_5);

  TCase *tc_from_float_to_decimal_6;
  tc_from_float_to_decimal_6 = tcase_create("s21_from_float_to_decimal_6");
  suite_add_tcase(s, tc_from_float_to_decimal_6);
  tcase_add_test(tc_from_float_to_decimal_6, s21_from_float_to_decimal_6);

  // s21_from_int_to_decimal_1

  TCase *tc_from_int_to_decimal_1;
  tc_from_int_to_decimal_1 = tcase_create("s21_from_int_to_decimal_1");
  suite_add_tcase(s, tc_from_int_to_decimal_1);
  tcase_add_test(tc_from_int_to_decimal_1, s21_from_int_to_decimal_1);

  TCase *tc_from_int_to_decimal_2;
  tc_from_int_to_decimal_2 = tcase_create("s21_from_int_to_decimal_2");
  suite_add_tcase(s, tc_from_int_to_decimal_2);
  tcase_add_test(tc_from_int_to_decimal_2, s21_from_int_to_decimal_2);

  TCase *tc_from_int_to_decimal_3;
  tc_from_int_to_decimal_3 = tcase_create("s21_from_int_to_decimal_3");
  suite_add_tcase(s, tc_from_int_to_decimal_3);
  tcase_add_test(tc_from_int_to_decimal_3, s21_from_int_to_decimal_3);

  TCase *tc_from_int_to_decimal_4;
  tc_from_int_to_decimal_4 = tcase_create("s21_from_int_to_decimal_4");
  suite_add_tcase(s, tc_from_int_to_decimal_4);
  tcase_add_test(tc_from_int_to_decimal_4, s21_from_int_to_decimal_4);

  // s21_from_decimal_to_int_1

  TCase *tc_from_decimal_to_int_1;
  tc_from_decimal_to_int_1 = tcase_create("s21_from_decimal_to_int_1");
  suite_add_tcase(s, tc_from_decimal_to_int_1);
  tcase_add_test(tc_from_decimal_to_int_1, s21_from_decimal_to_int_1);

  TCase *tc_from_decimal_to_int_2;
  tc_from_decimal_to_int_2 = tcase_create("s21_from_decimal_to_int_2");
  suite_add_tcase(s, tc_from_decimal_to_int_2);
  tcase_add_test(tc_from_decimal_to_int_2, s21_from_decimal_to_int_2);

  TCase *tc_from_decimal_to_int_3;
  tc_from_decimal_to_int_3 = tcase_create("s21_from_decimal_to_int_3");
  suite_add_tcase(s, tc_from_decimal_to_int_3);
  tcase_add_test(tc_from_decimal_to_int_3, s21_from_decimal_to_int_3);

  TCase *tc_from_decimal_to_int_4;
  tc_from_decimal_to_int_4 = tcase_create("s21_from_decimal_to_int_4");
  suite_add_tcase(s, tc_from_decimal_to_int_4);
  tcase_add_test(tc_from_decimal_to_int_4, s21_from_decimal_to_int_4);

  // s21_from_decimal_to_float

  TCase *tc_from_decimal_to_float_1;
  tc_from_decimal_to_float_1 = tcase_create("s21_from_decimal_to_float_1");
  suite_add_tcase(s, tc_from_decimal_to_float_1);
  tcase_add_test(tc_from_decimal_to_float_1, s21_from_decimal_to_float_1);

  TCase *tc_from_decimal_to_float_2;
  tc_from_decimal_to_float_2 = tcase_create("s21_from_decimal_to_float_2");
  suite_add_tcase(s, tc_from_decimal_to_float_2);
  tcase_add_test(tc_from_decimal_to_float_2, s21_from_decimal_to_float_2);

  TCase *tc_from_decimal_to_float_3;
  tc_from_decimal_to_float_3 = tcase_create("s21_from_decimal_to_float_3");
  suite_add_tcase(s, tc_from_decimal_to_float_3);
  tcase_add_test(tc_from_decimal_to_float_3, s21_from_decimal_to_float_3);

  TCase *tc_from_decimal_to_float_4;
  tc_from_decimal_to_float_4 = tcase_create("s21_from_decimal_to_float_4");
  suite_add_tcase(s, tc_from_decimal_to_float_4);
  tcase_add_test(tc_from_decimal_to_float_4, s21_from_decimal_to_float_4);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;
  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, 2);
  srunner_free(sr);
  return 0;
}
