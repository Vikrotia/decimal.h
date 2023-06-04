#include "s21_decimal.h"

// Арифметические операции.

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0, tmp = 0, left_bit = 0, right_bit = 0, sign1 = get_sign(value_1),
      sign2 = get_sign(value_2);
  s21_decimal bleach = {0};
  *result = bleach;
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  if (!up_scale(&value_1, &value_2)) {
    if ((!sign1 && !sign2) || (sign1 && sign2)) {
      for (int i = 0; i < 96; i++) {
        left_bit = get_bit(value_1, i);
        right_bit = get_bit(value_2, i);
        if (((left_bit || right_bit) && i == 95) && tmp) {
          if (!sign1 && !sign2)
            flag = 1;
          else
            flag = 2;
        } else {
          if (left_bit && right_bit) {
            if (tmp) {
              set_bit(result, i, 1);
            } else {
              set_bit(result, i, 0);
            }
            tmp = 1;
          }
          if (left_bit ^ right_bit) {  // 1
            if (tmp) {
              set_bit(result, i, 0);
              tmp = 1;
            } else {
              set_bit(result, i, 1);
            }
          }
          if (!left_bit && !right_bit) {
            if (tmp) {
              set_bit(result, i, 1);
              tmp = 0;
            } else {
              set_bit(result, i, 0);
            }
          }
        }
      }
      if (sign1 && sign2)
        set_sign(result, 1);
      else
        set_sign(result, 0);
    } else if (sign1 && !sign2) {
      if (s21_is_less(value_1, value_2)) {
        s21_sub(value_2, value_1, result);
        set_sign(result, 0);
      } else {
        s21_sub(value_1, value_2, result);
        set_sign(result, 1);
      }
    } else if (!sign1 && sign2) {
      if (s21_is_less(value_1, value_2)) {
        s21_sub(value_2, value_1, result);
        set_sign(result, 1);
      } else {
        s21_sub(value_1, value_2, result);
        set_sign(result, 0);
      }
    }
    set_scale(result, get_scale(value_1));
  } else {
    flag = 1;
  }
  if DECIMAL_ZERO_SOLO ((*result)) set_sign(result, 0);
  if (flag) init(result);
  return flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign1 = get_sign(value_1), sign2 = get_sign(value_2), flag = 0;
  s21_decimal bleach = {0};
  *result = bleach;
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  if (!up_scale(&value_1, &value_2)) {
    int less = s21_is_less(value_1, value_2);
    if (sign1 && sign2) {
      if (less) {
        s21_sub_1(value_2, value_1, result);
        set_sign(result, 0);
      } else {
        s21_sub_1(value_1, value_2, result);
        set_sign(result, 1);
      }
    } else if (!sign1 && !sign2) {
      if (less) {
        s21_sub_1(value_2, value_1, result);
        set_sign(result, 1);
      } else {
        s21_sub_1(value_1, value_2, result);
        set_sign(result, 0);
      }
    } else if (!sign1 && sign2) {
      if (s21_add(value_1, value_2, result)) flag = 1;
      set_sign(result, 0);
    } else if (sign1 && !sign2) {
      if (((DECIMAL_MAX(value_1) || DECIMAL_MAX(value_2))) &&
          (!DECIMAL_ZERO_SOLO(value_1) || !DECIMAL_ZERO_SOLO(value_2))) {
        flag = 2;
      } else {
        s21_add(value_1, value_2, result);
        set_sign(result, 1);
      }
    }
    set_scale(result, get_scale(value_1));
  } else {
    init(result);
    flag = 1;
  }
  return flag;
}

// Операция вычитания. Вызывается из s21_sub.
void s21_sub_1(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_decimal bleach = {0};
  *result = bleach;
  s21_decimal plus_one = {{1, 0, 0, 0}};
  set_scale(&plus_one, get_scale(value_1));  // ???
  s21_decimal invert_decimal = {0};
  if DECIMAL_MAX (value_1) flag = 1;
  invert(&value_2, &value_1);
  if (!flag) {
    s21_add(value_2, plus_one, &invert_decimal);
    s21_add(value_1, invert_decimal, result);
    int count = bit_count(value_1);
    set_bit(result, count + 1, 0);
  } else {
    *result = value_2;
  }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0, bit2 = 0, bit1 = 0, count = 0, mul_on_one = 0;
  int sign1 = get_sign(value_1), sign2 = get_sign(value_2);
  s21_decimal temp_result = {0}, one = {{1, 0, 0, 0}};
  *result = temp_result;
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  if ((DECIMAL_MAX(value_1) || DECIMAL_MAX(value_2))) {
    if (DECIMAL_ZERO_SOLO(value_1) || DECIMAL_ZERO_SOLO(value_2)) {
      mul_on_one = 1;
    } else if (s21_is_equal(value_1, one)) {
      *result = value_2;
      mul_on_one = 1;
    } else if (s21_is_equal(value_2, one)) {
      *result = value_1;
      mul_on_one = 1;
    } else if (s21_is_greater(value_1, one) || s21_is_greater(value_2, one)) {
      if ((sign1 && sign2) || (!sign1 && !sign2))
        flag = 1;
      else if ((sign1 && !sign2) || (!sign1 && sign2))
        flag = 2;
    }
  }
  if (!flag && !mul_on_one) {
    for (int i = 0; i < 96 && !flag; i++) {
      bit2 = get_bit(value_2, i);
      for (int j = 0; j < 96 && !flag; j++) {
        bit1 = get_bit(value_1, j);
        if (bit2) {
          set_bit(&temp_result, j, bit1);
        } else {
          set_bit(&temp_result, j, 0);
        }
      }
      if (count) shift_left(&temp_result, count);
      if (s21_add(*result, temp_result, result)) {
        if ((sign1 && sign2) || (!sign1 && !sign2))
          flag = 1;
        else
          flag = 2;
      }
      count++;
    }
    if ((sign1 && !sign2) || (!sign1 && sign2)) set_sign(result, 1);
    if ((sign1 && sign2) || (!sign1 && !sign2)) set_sign(result, 0);
    if (get_scale(value_1) + get_scale(value_2) > 28) {
      flag = 1;
      init(result);
    } else {
      set_scale(result, get_scale(value_1) + get_scale(value_2));
    }
  } else if (flag) {
    init(result);
  }
  return flag;
}

void s21_div_sup(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                 s21_decimal *temp_result1) {
  int count1 = bit_count(value_1), count2 = bit_count(value_2);
  s21_decimal part_res = {0}, temp_res = {0};
  for (int i = count2; i >= 0; i--) {
    set_bit(&temp_res, i, get_bit(value_1, count1));
    count1--;
  }
  s21_decimal temp_result = {0};
  *result = temp_result;
  do {
    if (s21_is_greater_or_equal(temp_res, value_2)) {
      s21_sub(temp_res, value_2, &part_res);
      shift_left(result, 1);
      set_bit(result, 0, 1);
      shift_left(&part_res, 1);
      set_bit(&part_res, 0, get_bit(value_1, count1));
      for (int i = 0; i < 96; i++) set_bit(&temp_res, i, get_bit(part_res, i));
    } else {
      shift_left(result, 1);
      set_bit(result, 0, 0);
      shift_left(&temp_res, 1);
      set_bit(&temp_res, 0, get_bit(value_1, count1));
    }
    count1--;
    s21_mul(*result, value_2, &temp_result);
    s21_sub(value_1, temp_result, temp_result1);
  } while (s21_is_greater_or_equal(*temp_result1, value_2));
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0, count1 = bit_count(value_1), count2 = bit_count(value_2),
      div_on_one = 0, sign1 = get_sign(value_1), sign2 = get_sign(value_2);
  s21_decimal positive_one = {{1, 0, 0, 0}};
  s21_decimal part_res = {0}, temp_res = {0};
  int mod = get_bit(*result, 96);
  *result = temp_res;
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  if DECIMAL_ZERO_SOLO (value_2) {
    init(result);
    flag = 3;
  }
  if (DECIMAL_MAX(value_1) && (!flag && !mod)) {
    if (s21_is_equal(value_2, positive_one)) {
      if ((sign1 && !sign2) || (!sign1 && sign2)) {
        div_on_one = 1;
        *result = value_1;
        set_sign(result, 1);
      } else if ((sign1 && sign2) || (!sign1 && !sign2)) {
        div_on_one = 1;
        *result = value_1;
        set_sign(result, 0);
      }
    } else if DECIMAL_MAX (value_2) {
      if ((sign1 && !sign2) || (!sign1 && sign2)) {
        div_on_one = 1;
        (*result).bits[0] = 1;
        set_sign(result, 1);
      } else if ((sign1 && sign2) || (!sign1 && !sign2)) {
        div_on_one = 1;
        (*result).bits[0] = 1;
        set_sign(result, 0);
      }
    } else if (s21_is_less(value_2, positive_one)) {
      if ((sign1 && !sign2) || (!sign1 && sign2)) {
        flag = 2;
      } else if ((sign1 && sign2) || (!sign1 && !sign2)) {
        flag = 1;
      }
    }
  }
  if (flag || DECIMAL_ZERO_SOLO(value_1)) {
    init(result);
  } else if (!div_on_one) {
    if (s21_is_less(value_1, value_2)) {
      temp_res = value_1;
    } else {
      for (int i = count2; i >= 0; i--) {
        set_bit(&temp_res, i, get_bit(value_1, count1));
        count1--;
      }
    }
    s21_decimal temp_result = {0}, temp_result1 = {0};
    do {
      if (s21_is_greater_or_equal(temp_res, value_2)) {
        s21_sub(temp_res, value_2, &part_res);
        shift_left(result, 1);
        set_bit(result, 0, 1);
        shift_left(&part_res, 1);
        set_bit(&part_res, 0, get_bit(value_1, count1));
        for (int i = 0; i < 96; i++)
          set_bit(&temp_res, i, get_bit(part_res, i));
      } else {
        shift_left(result, 1);
        set_bit(result, 0, 0);
        shift_left(&temp_res, 1);
        set_bit(&temp_res, 0, get_bit(value_1, count1));
      }
      count1--;
      s21_mul(*result, value_2, &temp_result);
      s21_sub(value_1, temp_result, &temp_result1);
    } while (s21_is_greater_or_equal(temp_result1, value_2));
    if (mod) {
      *result = temp_result1;
    } else {
      int count_res = bit_count(*result);
      int scale_count = 0, max_value = 96, scale_last = 0;
      s21_decimal res = {0};
      if DECIMAL_ZERO_SOLO ((*result)) max_value = 95;
      while (!DECIMAL_ZERO_SOLO(temp_result1) &&
             scale_last + count_res < max_value) {
        mul_ten(temp_result1, &temp_result1);
        if (s21_is_greater_or_equal(temp_result1, value_2)) {
          s21_div_sup(temp_result1, value_2, &res, &temp_result1);
          mul_ten(*result, result);
          s21_add(*result, res, result);
        }
        scale_count++;
        scale_last = count_res;
        count_res = bit_count(*result);
        scale_last = count_res - scale_last;
      }
      set_scale(result, scale_count);
    }
  }
  return flag;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0, sign1 = get_sign(value_1), scale1 = get_scale(value_1),
      scale2 = get_scale(value_2);
  s21_decimal bleach = {0};
  *result = bleach;
  up_scale(&value_1, &value_2);
  set_scale(&value_1, 0);
  set_scale(&value_2, 0);
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  set_bit(result, 96, 1);
  flag = s21_div(value_1, value_2, result);
  set_bit(result, 96, 0);
  if (sign1)
    set_sign(result, 1);
  else
    set_sign(result, 0);
  (scale1 > scale2) ? set_scale(result, scale1) : set_scale(result, scale2);
  if (flag) init(result);
  return flag;
}

// Операции сравнения

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0, bit1 = 0, bit2 = 0, flag_of_end = 0;
  up_scale(&value_1, &value_2);
  if (get_sign(value_1) && !get_sign(value_2)) {
    flag = 1;
    flag_of_end = 1;
  }
  if (!get_sign(value_1) && get_sign(value_2)) flag_of_end = 1;
  for (int i = 95; i >= 0 && !flag_of_end; i--) {
    bit1 = get_bit(value_1, i);
    bit2 = get_bit(value_2, i);
    if (bit1 != bit2) {
      if (bit1 > bit2) {
        flag_of_end = 1;
      } else if (bit1 < bit2) {
        flag = 1;
        flag_of_end = 1;
      }
    }
  }
  if ((get_sign(value_1) && get_sign(value_2)) && flag_of_end) flag = !flag;
  return flag;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) ? 0 : 1;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0, bit1 = 0, bit2 = 0, flag_of_end = 0,
      scale1 = get_scale(value_1), scale2 = get_scale(value_2);
  if (up_scale(&value_1, &value_2)) {
    if (scale1 > scale2) {
      flag = 0;
      flag_of_end = 1;
    } else {
      flag = 1;
      flag_of_end = 1;
    }
  }
  if (get_sign(value_1) && !get_sign(value_2)) {
    flag_of_end = 1;
  }
  if (!get_sign(value_1) && get_sign(value_2)) {
    if DECIMAL_ZERO_MULTI (value_1, value_2)
      flag = 0;
    else
      flag = 1;
    flag_of_end = 1;
  }
  for (int i = 95; i >= 0 && !flag_of_end; i--) {
    bit1 = get_bit(value_1, i);
    bit2 = get_bit(value_2, i);
    if (bit1 != bit2) {
      if (bit1 < bit2) {
        flag_of_end = 1;
      } else if (bit1 > bit2) {
        flag = 1;
        flag_of_end = 1;
      }
    }
  }
  if ((get_sign(value_1) && get_sign(value_2)) && flag_of_end) flag = !flag;
  return flag;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) ? 0 : 1;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 1, bit1 = 0, bit2 = 0, flag_of_end = 0;
  up_scale(&value_1, &value_2);
  if (get_sign(value_1) == get_sign(value_2)) {
    for (int i = 95; i >= 0 && !flag_of_end; i--) {
      bit1 = get_bit(value_1, i);
      bit2 = get_bit(value_2, i);
      if (bit1 != bit2) {
        flag = 0;
      }
    }
  } else {
    if DECIMAL_ZERO_MULTI (value_1, value_2)
      flag = 1;
    else
      flag = 0;
  }
  return flag;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) ? 0 : 1;
}

// Преобразователи

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = 0, src1 = abs(src);
  if (isnan(src) || isinf(src)) flag = 1;
  init(dst);
  if (!flag) {
    for (int i = 0; i < 32; i++) {
      set_bit(dst, i, src1 % 2);
      src1 /= 2;
    }
    if (src < 0) set_sign(dst, 1);
    if (get_bit(*dst, 31)) {
      init(dst);
      flag = 1;
    }
  }
  return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 0;
  int count = 0;
  int scale = 0;
  float temp_int = 0.0;
  if (isnan(src) || isinf(src)) flag = 1;
  init(dst);
  if (!flag) {
    if (fabs(src) < 1e-28 || fabs(src) > 79228162514264337593543950335.0) {
      flag = 1;
    } else {
      float temp_float = modff(src, &temp_int);
      while (temp_int >= 10000000) {
        temp_int /= 10;
        count = 7;
      }
      float temp_int_1 = fabs(temp_int);
      if (count < 7) {
        while (temp_int_1 >= 1) {
          temp_int_1 /= 10;
          count++;
        }
        scale = 7 - count;
        if (scale <= 7) {
          temp_float *= pow(10, scale);
          temp_int *= pow(10, scale);
          temp_int += temp_float;
        }
      }
      int int_temp = temp_int;
      for (int i = 0; i < 96; i++) {
        set_bit(dst, i, int_temp % 2);
        int_temp /= 2;
      }
      if (src < 0) set_sign(dst, 1);
      set_scale(dst, scale);
    }
  }
  return flag;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  *dst = 0;
  s21_truncate(src, &src);
  flag = s21_goes_in_int(src);
  if (!flag) {
    *dst = src.bits[0];
    if (get_sign(src)) *dst *= -1;
  }
  return flag;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int flag = 0, scale = get_scale(src);
  *dst = 0;
  double dst1 = 0;
  for (int i = 0; i < 96; i++) dst1 += get_bit(src, i) * pow(2, i);
  for (int i = 0; i < scale; i++) dst1 /= 10.0;
  *dst = (float)dst1;
  if (get_sign(src)) *dst *= -1;
  return flag;
}

// Другие функции

int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = 0, sign = get_sign(value);
  s21_decimal bleach = {0};
  *result = bleach;
  s21_decimal temp = {0}, one = {{1, 0, 0, 0}};
  if (sign) {
    s21_truncate(value, &temp);
    if (!s21_is_equal(value, temp)) {
      set_sign(&one, 1);
      s21_add(temp, one, result);
      set_sign(result, 1);
    } else {
      *result = value;
    }
  } else {
    s21_truncate(value, result);
  }
  return flag;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  s21_decimal bleach = {0};
  *result = bleach;
  s21_decimal zero_point_five = {{5, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal exp = {0}, truncated = {0}, one = {{1, 0, 0, 0}};
  if (get_scale(value) > 0) {
    s21_truncate(value, &truncated);
    s21_sub(value, truncated, &exp);
    set_sign(&exp, 0);
    if (s21_is_less_or_equal(exp, zero_point_five)) {
      *result = truncated;
    } else {
      if (!get_sign(value))
        s21_add(truncated, one, result);
      else
        s21_sub(truncated, one, result);
    }
  } else {
    *result = value;
  }
  return flag;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0, scale1 = get_scale(value), sign = get_sign(value);
  s21_decimal bleach = {0};
  *result = bleach;
  if (sign) set_sign(&value, 0);
  s21_decimal temp_result = {{0, 0, 0, 0}}, temp_result1 = {{0, 0, 0, 0}},
              bla = {0};
  set_scale(&value, 0);
  temp_result = value;
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal ten1 = {{10, 0, 0, 0}};
  for (int i = 0; i < scale1 - 1; i++) {
    s21_mul(ten, ten1, &ten);
  }
  if (scale1) {
    s21_div_sup(temp_result, ten, &temp_result1, &bla);
    temp_result = temp_result1;
  }
  *result = temp_result;
  if (sign) set_sign(result, 1);
  return flag;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_decimal bleach = {0};
  *result = bleach;
  (*result).bits[0] = value.bits[0];
  (*result).bits[1] = value.bits[1];
  (*result).bits[2] = value.bits[2];
  (*result).bits[3] = value.bits[3];
  if (get_sign(*result))
    set_sign(result, 0);
  else
    set_sign(result, 1);
  return 0;
}

// Вспомогательные функции

int get_bit(s21_decimal number, int bit) {
  int result = 0;
  unsigned int mask = 1 << (bit % 32);
  if ((number.bits[bit / 32] & mask) != 0) result = 1;
  return result;
}

void set_bit(s21_decimal *number, int bit, int value) {
  unsigned int shift = 1;
  if (bit >= 0 && bit < 128) {
    if (value)
      number->bits[bit / 32] = number->bits[bit / 32] | shift << (bit % 32);
    else
      number->bits[bit / 32] = number->bits[bit / 32] & ~(shift << (bit % 32));
  }
}

int get_sign(s21_decimal number) {
  int result = 0;
  unsigned int mask = 1u << 31;
  if ((number.bits[3] & mask) != 0) result = 1;
  return result;
}

void set_sign(s21_decimal *number, int sign) {
  unsigned int shift = 1;
  if (sign == 1)
    number->bits[3] = number->bits[3] | shift << 31;
  else
    number->bits[3] = number->bits[3] & ~(shift << 31);
}

int get_scale(s21_decimal value) {
  int scale = 0, scale_arr[8] = {0}, j = 0;
  for (int i = 119; i >= 111; i--) {
    scale_arr[j] = get_bit(value, i);
    j++;
  }
  j = 7;
  for (int i = 0; i < 8; i++) {
    scale += scale_arr[i] * pow(2, j);
    j--;
  }
  return scale;
}

void set_scale(s21_decimal *value, int scale) {
  int scale_arr[8] = {0}, tmp = scale;
  for (int i = 7; i >= 0; i--) {
    scale_arr[i] = tmp % 2;
    tmp /= 2;
  }
  int scale_i = 119;
  for (int i = 0; i < 8; i++) {
    set_bit(value, scale_i, scale_arr[i]);
    scale_i--;
  }
}

int mul_ten(s21_decimal value, s21_decimal *result) {
  s21_decimal bleach = {0};
  *result = bleach;
  s21_decimal val1 = value, val2 = value;
  int bit1 = 0, bit2 = 0, temp = 0, flag = 0;
  shift_left(&val1, 1);
  shift_left(&val2, 3);
  for (int i = 0; i < 96; i++) {
    bit1 = get_bit(val1, i);
    bit2 = get_bit(val2, i);
    if (!bit1 && !bit2) {
      if (!temp)
        set_bit(result, i, 0);
      else {
        set_bit(result, i, 1);
        temp = 0;
      }

    } else if (bit1 && bit2) {
      if (!temp) {
        set_bit(result, i, 0);
        temp = 1;
      } else {
        set_bit(result, i, 1);
        temp = 1;
      }
    } else {
      if (!temp) {
        set_bit(result, i, 1);
        temp = 0;
      } else {
        set_bit(result, i, 0);
        temp = 1;
      }
    }
    if ((i == 95 && temp == 1) && (bit1 || bit2)) {
      flag = 2;
      init(result);
    }
  }
  if (get_sign(value)) set_sign(result, 1);
  return flag;
}

int up_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1 = get_scale(*value_1), scale_2 = get_scale(*value_2), error = 0;
  s21_decimal temp_result = {{0, 0, 0, 0}}, temp_result1 = {{0, 0, 0, 0}};
  if (scale_1 > scale_2) {
    temp_result = *value_2;
    for (int i = 0; i < scale_1 - scale_2; i++) {
      if ((error = mul_ten(temp_result, &temp_result1)) == 2) break;
      temp_result = temp_result1;
    }
    if (!error) *value_2 = temp_result;
    set_scale(value_2, scale_1);
  } else if (scale_1 < scale_2) {
    temp_result = *value_1;
    for (int i = 0; i < scale_2 - scale_1; i++) {
      if ((error = mul_ten(temp_result, &temp_result1)) == 2) break;
      temp_result = temp_result1;
    }
    if (!error) *value_1 = temp_result;
    set_scale(value_1, scale_2);
  }
  return error;
}

int bit_count(s21_decimal value) {
  int count = 0;
  for (int i = 96; i > 0; i--) {
    if (get_bit(value, i) == 1) {
      count = i;
      break;
    }
  }
  return count;
}

void invert(s21_decimal *value_2, s21_decimal *value_1) {
  int bit = 0, count = 0;
  for (int i = 95; i > 0; i--) {
    if (get_bit(*value_1, i) == 1) {
      count = i;
      break;
    }
  }
  for (int j = 0; j <= count; j++) {
    bit = get_bit(*value_2, j);
    if (bit == 0)
      bit = 1;
    else
      bit = 0;
    set_bit(value_2, j, bit);
  }
}

void shift_left(s21_decimal *number, int i) {
  do {
    for (int j = 95; j >= 0; j--) {
      if (j == 0)
        set_bit(number, j, 0);
      else
        set_bit(number, j, get_bit(*number, j - 1));
    }
    i--;
  } while (i > 0);
}

void print_bits(s21_decimal temp_res) {
  for (int i = 0; i < 32; i++) {
    if (i == 8 || i == 16) printf("|");
    printf("%c", (temp_res.bits[3] & 0x80000000) ? '1' : '0');
    temp_res.bits[3] <<= 1;
  }
  for (int i = 0; i < 32; i++) {
    printf("%c", (temp_res.bits[2] & 0x80000000) ? '1' : '0');
    temp_res.bits[2] <<= 1;
  }
  for (int i = 0; i < 32; i++) {
    printf("%c", (temp_res.bits[1] & 0x80000000) ? '1' : '0');
    temp_res.bits[1] <<= 1;
  }
  for (int i = 0; i < 32; i++) {
    printf("%c", (temp_res.bits[0] & 0x80000000) ? '1' : '0');
    temp_res.bits[0] <<= 1;
  }
  printf("\n");
}

int s21_goes_in_int(s21_decimal src) {
  int flag = 0;
  for (int i = 32; i < 96 && !flag; i++)
    if (get_bit(src, i)) flag = 1;
  if (!flag) flag = get_bit(src, 31);
  if (!flag) flag = src.bits[0] <= 2147483647 ? 0 : 1;
  return flag;
}

void init(s21_decimal *number) {
  number->bits[3] = 0b00000000000000000000000000000000;
  number->bits[2] = 0b00000000000000000000000000000000;
  number->bits[1] = 0b00000000000000000000000000000000;
  number->bits[0] = 0b00000000000000000000000000000000;
}
