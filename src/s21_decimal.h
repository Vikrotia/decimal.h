#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DECIMAL_MAX(value)                                         \
  ((value.bits[0] == 0xFFFFFFFF && value.bits[1] == 0xFFFFFFFF) && \
   value.bits[2] == 0xFFFFFFFF)
#define DECIMAL_ZERO_SOLO(value) \
  ((!value.bits[0] && !value.bits[1]) && !value.bits[2])
#define DECIMAL_ZERO_MULTI(value1, value2)                      \
  (((!value1.bits[0] && !value1.bits[1]) && !value1.bits[2]) && \
   ((!value2.bits[0] && !value2.bits[1]) && !value2.bits[2]))
#define DECIMAL_ONE(value)                                               \
  (((value.bits[0] == 1 && value.bits[1] == 0) && value.bits[2] == 0) && \
   (value.bits[3] == 0x80000000 || value.bits[3] == 0))

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// Арифметические операторы

/**
 * @brief Сложение двух decimal.
 * @param value_1 Первый decimal сложения.
 * @param value_2 Второй decimal сложения.
 * @param result Decimal результата сложения.
 * @return 0 - OK; 1 - Число слишком большое или равно бесконечности;
 * 2 - Число слишком маленькое или равно отрицательной бесконечности;
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вспомогательная функция для add.
int s21_add_sup(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Вычитание двух decimal
 * @param value_1 Уменьшаемый decimal
 * @param value_2 Вычитаемый decimal
 * @param result Decimal результата вычитания.
 * @return 0 - ОК; 1 - Число слишком большое или равно бесконечности;
 * 2 - Число слишком маленькое или равно отрицательной бесконечности;
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вспомогательная функция для sub.
void s21_sub_1(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Умножение двух decimal.
 * @param value_1 Первый decimal множитель.
 * @param value_2 Второй decimal множитель.
 * @param result Decimal результата умножения.
 * @return 0 - OK; 1 - Число слишком большое или равно бесконечности;
 * 2 - Число слишком маленькое или равно отрицательной бесконечности.
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Деление двух decimal.
 * @param value_1 Частное decimal.
 * @param value_2 Делитель decimal.
 * @param result Decimal результата деления.
 * @return 0 - OK; 1 - Число слишком большое или равно бесконечности;
 * 2 - Число слишком маленькое или равно отрицательной бесконечности;
 * 3 - Деление на 0.
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//Вспомогательные функции для div.
void s21_div_sup(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                 s21_decimal *temp_result1);

/**
 * @brief Находит остаток от деления двух decimal.
 * @param value_1 Частное decimal.
 * @param value_2 Делитель decimal.
 * @param result Decimal в который запишется остаток от деления.
 * @return 0 - OK.
 */
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Операторы сравнения

/**
 * @brief Является ли value_1 меньше value_2
 * @param value_1 Первый decimal.
 * @param value_2 Второй decimal.
 * @return 0 - False; 1 - True.
 */
int s21_is_less(s21_decimal, s21_decimal);  // Меньше "<"

/**
 * @brief Является ли value_1 меньше или равно value_2
 * @param value_1 Первый decimal.
 * @param value_2 Второй decimal.
 * @return 0 - False; 1 - True.
 */
int s21_is_less_or_equal(s21_decimal, s21_decimal);  // Меньше или равно "<="

/**
 * @brief Является ли value_1 больше value_2
 * @param value_1 Первый decimal.
 * @param value_2 Второй decimal.
 * @return 0 - False; 1 - True.
 */
int s21_is_greater(s21_decimal, s21_decimal);  // Больше ">"

/**
 * @brief Является ли value_1 больше или равно value_2
 * @param value_1 Первый decimal.
 * @param value_2 Второй decimal.
 * @return 0 - False; 1 - True.
 */
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  // Больше или равно ">="

/**
 * @brief Является ли value_1 равным value_2
 * @param value_1 Первый decimal.
 * @param value_2 Второй decimal.
 * @return 0 - False; 1 - True.
 */
int s21_is_equal(s21_decimal, s21_decimal);  // Равно "=="

/**
 * @brief Является ли value_1 не равным value_2
 * @param value_1 Первый decimal.
 * @param value_2 Второй decimal.
 * @return 0 - False; 1 - True.
 */
int s21_is_not_equal(s21_decimal, s21_decimal);  // Не равно "!="

// Преобразователи

/**
 * @brief Преобразование из int в decimal
 * @param src Int который нужно перевести в decimal
 * @param dst Decimal который запишет подаваемый int
 * @return 0 - OK; 1 - Ошибка конвертации.
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst);

/**
 * @brief Преобразование из float в decimal
 * @param src Float который нужно перевести в decimal
 * @param dst Decimal который запишет подаваемый float
 * @return 0 - OK; 1 - Ошибка конвертации.
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst);

/**
 * @brief Преобразование из decimal в int
 * @param src Decimal который нужно перевести в int
 * @param dst Int который запишет подаваемый decimal
 * @return 0 - OK; 1 - Ошибка конвертации.
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst);

/**
 * @brief Преобразование из decimal в float
 * @param src Decimal который нужно перевести в float
 * @param dst Float который запишет подаваемый decimal
 * @return 0 - OK; 1 - Ошибка конвертации.
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Другие функции

/**
 * @brief Округляет указанное Decimal число до ближайшего целого числа в сторону
 * отрицательной бесконечности.
 * @param value Decimal который мы округляем.
 * @param result Decimal в который записываем результат округления.
 * @return 0 - OK; 1 - Ошибка.
 */
int s21_floor(s21_decimal value, s21_decimal *result);

/**
 * @brief Округляет Decimal до ближайшего целого числа.
 * @param value Decimal который мы округляем.
 * @param result Decimal в который записываем результат округления.
 * @return 0 - OK; 1 - Ошибка.
 */
int s21_round(s21_decimal value, s21_decimal *result);

/**
 * @brief Возвращает только целую часть decimal.
 * @param value Исходный decimal
 * @param result Decimal в который запишется результат функции
 * @return 0 - OK; 1 - Ошибка вычисления.
 */
int s21_truncate(s21_decimal value, s21_decimal *result);

/**
 * @brief Возвращает результат умножения decimal на -1.
 * @param value Исходный decimal
 * @param result Decimal в который запишется результат функции
 * @return 0 - OK; 1 - Ошибка вычисления.
 */
int s21_negate(s21_decimal value, s21_decimal *result);

// Вспомогательные функции

/**
 * @brief Возвращает значение определенного бита.
 * @param number Decimal в котором ищем нужный бит.
 * @param bit Индекс бита для поиска
 * @return Возвращает значение бита 0 или 1.
 */
int get_bit(s21_decimal number, int bit);

/**
 * @brief Устанавливает значение определенного бита.
 * @param number Decimal в котором ищем нужный бит для замены.
 * @param bit Индекс бита для поиска
 * @param value 0 или 1, значение для нужного бита.
 */
void set_bit(s21_decimal *number, int bit, int value);

/**
 * @brief Возвращает знак в decimal.
 * @param number Decimal в котором нужно узнать знак.
 * @return 0 - '+'; 1 - '-'
 */
int get_sign(s21_decimal number);

/**
 * @brief Устанавливает знак в decimal.
 * @param number Decimal в котором нужно изменить знак.
 * @param int Подается либо 0 для положительного знака, либо 1 для
 * отрицательного знака.
 */
void set_sign(s21_decimal *number, int sign);

/**
 * @brief Иницилизация decimal, заполнение всех битов нулями.
 * @param number Decimal для иницилизации.
 */
void init(s21_decimal *number);

/**
 * @brief Приравнивает степени двух decimal, повышает наименьший к наибольшему.
 * @param value_1 Первый decimal.
 * @param value_2 Второй decimal.
 */
int up_scale(s21_decimal *value_1, s21_decimal *value_2);
int mul_ten(s21_decimal value, s21_decimal *result);
/**
 * @brief Инвертирует вычитаемое число. Используется в s21_sub.
 * @param value_2 Вычитаемое число decimal.
 * @param value_1 Уменьшаемое число decimal.
 */
void invert(s21_decimal *value_2, s21_decimal *value_1);

/**
 * @brief Смещает биты влево в decimal.
 * @param number Decimal в котором нужно сместить биты.
 * @param i Радиус смещения влево.
 */
void shift_left(s21_decimal *number, int i);

/**
 * @brief Выводит в консоль все биты определенного decimal начиная с bits[3]
 * @param temp_res Decimal который нужно напечатать.
 */
void print_bits(s21_decimal temp_res);

/**
 * @brief Возвращает степень в decimal.
 * @param number Decimal в котором нужно узнать степень.
 * @return Число степени.
 */
int get_scale(s21_decimal value);

/**
 * @brief Устанавливает значение степени в decimal.
 * @param number Decimal в котором нужно изменить значение степени.
 * @param scale Значение степени от 0 до 28.
 */
void set_scale(s21_decimal *value, int scale);

/**
 * @brief Умещается ли decimal в int. Используется в s21_from_decimal_to_int
 * @param src Decimal для проверки.
 * @return 0 - Умещается; 1 - Не умещается.
 */
int s21_goes_in_int(s21_decimal src);

/**
 * @brief Функция возвращает индекс бита, с которого начинается число decimal.
 * @param value Изучаемый decimal.
 * @return Индекс бита, с которого начинается число decimal.
 */
int bit_count(s21_decimal value);

#endif  // S21_DECIMAL_H_
