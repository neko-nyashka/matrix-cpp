#include <check.h>

#include "s21_matrix.c"
#include "s21_matrix.h"
START_TEST(test_sum_correct) {
  matrix_t A, B, R, E;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 6;
  E.matrix[0][1] = 8;
  E.matrix[1][0] = 10;
  E.matrix[1][1] = 12;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_sum_with_zero) {
  matrix_t A, B, R, E;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0;
      B.matrix[i][j] = 0;
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 0);

  s21_create_matrix(3, 3, &E);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      E.matrix[i][j] = 0;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_sum_negative) {
  matrix_t A, B, R, E;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 4;
  E.matrix[0][1] = 4;
  E.matrix[1][0] = 4;
  E.matrix[1][1] = 4;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_sum_diff_sizes) {
  matrix_t A, B, R;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_null_input) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_sum_matrix(NULL, &B, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_invalid_sizes) {
  matrix_t A, B, R;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;
  B.rows = 2;
  B.columns = -1;
  B.matrix = NULL;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 1);
}
END_TEST

START_TEST(test_sum_large_matrix) {
  matrix_t A, B, R, E;
  int size = 100;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size, size, &B);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i - j;
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 0);

  s21_create_matrix(size, size, &E);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      E.matrix[i][j] = (i + j) + (i - j);
      ck_assert_double_eq_tol(R.matrix[i][j], E.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_sub_correct) {
  matrix_t A, B, R, E;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = 6;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 8;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 4;
  E.matrix[0][1] = 4;
  E.matrix[1][0] = 4;
  E.matrix[1][1] = 4;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_sub_with_zero) {
  matrix_t A, B, R, E;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 5.5;
      B.matrix[i][j] = 0;
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), 0);

  s21_create_matrix(3, 3, &E);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      E.matrix[i][j] = 5.5;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_sub_negative) {
  matrix_t A, B, R, E;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = -6;
  E.matrix[0][1] = -8;
  E.matrix[1][0] = -10;
  E.matrix[1][1] = -12;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_sub_diff_sizes) {
  matrix_t A, B, R;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_null_input) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &R), 1);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &R), 1);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_invalid_sizes) {
  matrix_t A, B, R;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;
  B.rows = 2;
  B.columns = -1;
  B.matrix = NULL;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), 1);
}
END_TEST

START_TEST(test_sub_large_matrix) {
  matrix_t A, B, R, E;
  int size = 100;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size, size, &B);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i - j;
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), 0);

  s21_create_matrix(size, size, &E);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      E.matrix[i][j] = (i + j) - (i - j);
      ck_assert_double_eq_tol(R.matrix[i][j], E.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_sub_itself) {
  matrix_t A, R, E;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  ck_assert_int_eq(s21_sub_matrix(&A, &A, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 0;
  E.matrix[0][1] = 0;
  E.matrix[1][0] = 0;
  E.matrix[1][1] = 0;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_number_correct) {
  matrix_t A, R, E;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  double number = 2.5;
  ck_assert_int_eq(s21_mult_number(&A, number, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 2.5;
  E.matrix[0][1] = 5.0;
  E.matrix[1][0] = 7.5;
  E.matrix[1][1] = 10.0;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_number_zero) {
  matrix_t A, R, E;
  s21_create_matrix(3, 3, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 5.5;
    }
  }

  double number = 0.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &R), 0);

  s21_create_matrix(3, 3, &E);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      E.matrix[i][j] = 0.0;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_number_negative) {
  matrix_t A, R, E;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  double number = -1.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = -1;
  E.matrix[0][1] = -2;
  E.matrix[1][0] = -3;
  E.matrix[1][1] = -4;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_number_null_input) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_mult_number(NULL, 2.0, &R), 1);
  ck_assert_int_eq(s21_mult_number(&A, 2.0, NULL), 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_number_invalid_matrix) {
  matrix_t A, R;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  ck_assert_int_eq(s21_mult_number(&A, 2.0, &R), 1);
}
END_TEST

START_TEST(test_mult_number_large_matrix) {
  matrix_t A, R, E;
  int size = 100;
  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = i + j;
    }
  }

  double number = 1.5;
  ck_assert_int_eq(s21_mult_number(&A, number, &R), 0);

  s21_create_matrix(size, size, &E);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      E.matrix[i][j] = (i + j) * number;
      ck_assert_double_eq_tol(R.matrix[i][j], E.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_number_fractional) {
  matrix_t A, R, E;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  double number = 0.333333;
  ck_assert_int_eq(s21_mult_number(&A, number, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 1 * number;
  E.matrix[0][1] = 2 * number;
  E.matrix[1][0] = 3 * number;
  E.matrix[1][1] = 4 * number;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(R.matrix[i][j], E.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_number_zero_matrix) {
  matrix_t A, R, E;
  s21_create_matrix(3, 3, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0.0;
    }
  }

  double number = 5.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &R), 0);

  s21_create_matrix(3, 3, &E);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      E.matrix[i][j] = 0.0;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST
START_TEST(test_mult_matrix_correct) {
  matrix_t A, B, R, E;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  B.matrix[0][0] = 7;
  B.matrix[0][1] = 8;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 10;
  B.matrix[2][0] = 11;
  B.matrix[2][1] = 12;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 58;
  E.matrix[0][1] = 64;
  E.matrix[1][0] = 139;
  E.matrix[1][1] = 154;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_matrix_incompatible_sizes) {
  matrix_t A, B, R;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_null_input) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_mult_matrix(NULL, &B, &R), 1);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &R), 1);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_invalid_sizes) {
  matrix_t A, B, R;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;
  B.rows = 2;
  B.columns = -1;
  B.matrix = NULL;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 1);
}
END_TEST

START_TEST(test_mult_matrix_large) {
  matrix_t A, B, R, E;
  int size = 10;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size, size, &B);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i - j;
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 0);

  s21_create_matrix(size, size, &E);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      E.matrix[i][j] = 0;
      for (int k = 0; k < size; k++) {
        E.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
      ck_assert_double_eq_tol(R.matrix[i][j], E.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_matrix_zero) {
  matrix_t A, B, R, E;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = 0;
      B.matrix[i][j] = 0;
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 0);

  s21_create_matrix(2, 2, &E);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      E.matrix[i][j] = 0;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_mult_matrix_identity) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1;
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      B.matrix[i][j] = (i == j) ? 1 : 0;
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 0);
  ck_assert_int_eq(s21_eq_matrix(&R, &A), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_matrix_negative_values) {
  matrix_t A, B, R, E;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  B.matrix[0][0] = -5;
  B.matrix[0][1] = -6;
  B.matrix[1][0] = -7;
  B.matrix[1][1] = -8;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 19;
  E.matrix[0][1] = 22;
  E.matrix[1][0] = 43;
  E.matrix[1][1] = 50;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST
START_TEST(test_transpose_correct) {
  matrix_t A, R, E;
  s21_create_matrix(2, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  ck_assert_int_eq(s21_transpose(&A, &R), 0);

  s21_create_matrix(3, 2, &E);
  E.matrix[0][0] = 1;
  E.matrix[0][1] = 4;
  E.matrix[1][0] = 2;
  E.matrix[1][1] = 5;
  E.matrix[2][0] = 3;
  E.matrix[2][1] = 6;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_transpose_square) {
  matrix_t A, R, E;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  ck_assert_int_eq(s21_transpose(&A, &R), 0);

  s21_create_matrix(3, 3, &E);
  E.matrix[0][0] = 1;
  E.matrix[0][1] = 4;
  E.matrix[0][2] = 7;
  E.matrix[1][0] = 2;
  E.matrix[1][1] = 5;
  E.matrix[1][2] = 8;
  E.matrix[2][0] = 3;
  E.matrix[2][1] = 6;
  E.matrix[2][2] = 9;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_transpose_single_element) {
  matrix_t A, R, E;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 42;

  ck_assert_int_eq(s21_transpose(&A, &R), 0);

  s21_create_matrix(1, 1, &E);
  E.matrix[0][0] = 42;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_transpose_null_input) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_transpose(NULL, &R), 1);
  ck_assert_int_eq(s21_transpose(&A, NULL), 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transpose_invalid_sizes) {
  matrix_t A, R;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  ck_assert_int_eq(s21_transpose(&A, &R), 1);
}
END_TEST

START_TEST(test_transpose_zero_matrix) {
  matrix_t A, R, E;
  s21_create_matrix(3, 2, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = 0;
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &R), 0);

  s21_create_matrix(2, 3, &E);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      E.matrix[i][j] = 0;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_transpose_large_matrix) {
  matrix_t A, R, E;
  int rows = 10, cols = 15;
  s21_create_matrix(rows, cols, &A);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = i * cols + j;
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &R), 0);

  s21_create_matrix(cols, rows, &E);
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      E.matrix[i][j] = A.matrix[j][i];
      ck_assert_double_eq_tol(R.matrix[i][j], E.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_transpose_negative_values) {
  matrix_t A, R, E;
  s21_create_matrix(2, 3, &A);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = -4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -6;

  ck_assert_int_eq(s21_transpose(&A, &R), 0);

  s21_create_matrix(3, 2, &E);
  E.matrix[0][0] = -1;
  E.matrix[0][1] = -4;
  E.matrix[1][0] = -2;
  E.matrix[1][1] = -5;
  E.matrix[2][0] = -3;
  E.matrix[2][1] = -6;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST
START_TEST(test_minor_3x3_center) {
  matrix_t A, M, E;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &M);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  s21_get_minor_matrix(&A, 1, 1, &M);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 1;
  E.matrix[0][1] = 3;
  E.matrix[1][0] = 7;
  E.matrix[1][1] = 9;

  ck_assert_int_eq(s21_eq_matrix(&M, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_minor_3x3_corner) {
  matrix_t A, M, E;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &M);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  s21_get_minor_matrix(&A, 0, 0, &M);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 5;
  E.matrix[0][1] = 6;
  E.matrix[1][0] = 8;
  E.matrix[1][1] = 9;

  ck_assert_int_eq(s21_eq_matrix(&M, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_minor_4x4_middle) {
  matrix_t A, M, E;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(3, 3, &M);

  int counter = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = counter++;
    }
  }

  s21_get_minor_matrix(&A, 2, 1, &M);

  s21_create_matrix(3, 3, &E);
  E.matrix[0][0] = 1;
  E.matrix[0][1] = 3;
  E.matrix[0][2] = 4;
  E.matrix[1][0] = 5;
  E.matrix[1][1] = 7;
  E.matrix[1][2] = 8;
  E.matrix[2][0] = 13;
  E.matrix[2][1] = 15;
  E.matrix[2][2] = 16;

  ck_assert_int_eq(s21_eq_matrix(&M, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_minor_2x2) {
  matrix_t A, M, E;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 1, &M);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  s21_get_minor_matrix(&A, 0, 0, &M);

  s21_create_matrix(1, 1, &E);
  E.matrix[0][0] = 4;

  ck_assert_int_eq(s21_eq_matrix(&M, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_minor_edge_row_col) {
  matrix_t A, M, E;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &M);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  s21_get_minor_matrix(&A, 0, 2, &M);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 4;
  E.matrix[0][1] = 5;
  E.matrix[1][0] = 7;
  E.matrix[1][1] = 8;

  ck_assert_int_eq(s21_eq_matrix(&M, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_minor_large_matrix) {
  matrix_t A, M;
  int size = 10;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size - 1, size - 1, &M);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = i * size + j;
    }
  }

  s21_get_minor_matrix(&A, size / 2, size / 2, &M);

  ck_assert_double_eq(M.matrix[0][0], A.matrix[0][0]);
  ck_assert_double_eq(M.matrix[size - 2][size - 2],
                      A.matrix[size - 1][size - 1]);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(test_minor_negative_values) {
  matrix_t A, M, E;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &M);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = -4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -6;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = -8;
  A.matrix[2][2] = -9;

  s21_get_minor_matrix(&A, 1, 1, &M);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = -1;
  E.matrix[0][1] = -3;
  E.matrix[1][0] = -7;
  E.matrix[1][1] = -9;

  ck_assert_int_eq(s21_eq_matrix(&M, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
  s21_remove_matrix(&E);
}

START_TEST(test_minor_success_3x3) {
  matrix_t A, M;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int result = s21_minor(1, 1, &A, &M);
  ck_assert_int_eq(result, 0);

  ck_assert_int_eq(M.rows, 2);
  ck_assert_int_eq(M.columns, 2);
  ck_assert_double_eq(M.matrix[0][0], 1);
  ck_assert_double_eq(M.matrix[0][1], 3);
  ck_assert_double_eq(M.matrix[1][0], 7);
  ck_assert_double_eq(M.matrix[1][1], 9);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(test_minor_invalid_input) {
  matrix_t A, M;
  s21_create_matrix(3, 3, &A);

  ck_assert_int_eq(s21_minor(1, 1, NULL, &M), 1);
  ck_assert_int_eq(s21_minor(1, 1, &A, NULL), 1);

  matrix_t invalid;
  invalid.rows = -1;
  invalid.columns = 3;
  invalid.matrix = NULL;
  ck_assert_int_eq(s21_minor(1, 1, &invalid, &M), 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_minor_too_small_matrix) {
  matrix_t A, M;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  ck_assert_int_eq(s21_minor(0, 0, &A, &M), 2);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_minor_edge_positions) {
  matrix_t A, M;
  s21_create_matrix(4, 4, &A);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i * 4 + j + 1;
    }
  }

  ck_assert_int_eq(s21_minor(0, 0, &A, &M), 0);
  ck_assert_int_eq(M.matrix[0][0], 6);
  ck_assert_int_eq(M.matrix[2][2], 16);
  s21_remove_matrix(&M);

  ck_assert_int_eq(s21_minor(3, 3, &A, &M), 0);
  ck_assert_int_eq(M.matrix[0][0], 1);
  ck_assert_int_eq(M.matrix[2][2], 11);
  s21_remove_matrix(&M);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_minor_rectangular_matrix) {
  matrix_t A, M;
  s21_create_matrix(2, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  ck_assert_int_eq(s21_minor(0, 1, &A, &M), 0);
  ck_assert_int_eq(M.rows, 1);
  ck_assert_int_eq(M.columns, 2);
  ck_assert_double_eq(M.matrix[0][0], 4);
  ck_assert_double_eq(M.matrix[0][1], 6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(test_minor_memory_allocation_failure) {
  matrix_t A, M;
  s21_create_matrix(1000, 1000, &A);
  int result = s21_minor(500, 500, &A, &M);
  ck_assert(result == 0 || result == 1);

  s21_remove_matrix(&A);
  if (result == 0) {
    s21_remove_matrix(&M);
  }
}
END_TEST

START_TEST(test_minor_negative_values_2) {
  matrix_t A, M;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = -4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -6;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = -8;
  A.matrix[2][2] = -9;

  ck_assert_int_eq(s21_minor(1, 1, &A, &M), 0);
  ck_assert_double_eq(M.matrix[0][0], -1);
  ck_assert_double_eq(M.matrix[1][1], -9);

  s21_remove_matrix(&A);
  s21_remove_matrix(&M);
}
END_TEST
START_TEST(test_calc_complements_3x3) {
  matrix_t A, R, E;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(3, 3, &E);
  E.matrix[0][0] = 0;
  E.matrix[0][1] = 10;
  E.matrix[0][2] = -20;
  E.matrix[1][0] = 4;
  E.matrix[1][1] = -14;
  E.matrix[1][2] = 8;
  E.matrix[2][0] = -8;
  E.matrix[2][1] = -2;
  E.matrix[2][2] = 4;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_calc_complements_2x2) {
  matrix_t A, R, E;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 4;
  E.matrix[0][1] = -3;
  E.matrix[1][0] = -2;
  E.matrix[1][1] = 1;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_calc_complements_1x1) {
  matrix_t A, R;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_null_input) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_calc_complements(NULL, &R), 1);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_non_square) {
  matrix_t A, R;
  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_calc_complements(&A, &R), 2);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_zero_det) {
  matrix_t A, R, E;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(3, 3, &E);
  E.matrix[0][0] = -3;
  E.matrix[0][1] = 6;
  E.matrix[0][2] = -3;
  E.matrix[1][0] = 6;
  E.matrix[1][1] = -12;
  E.matrix[1][2] = 6;
  E.matrix[2][0] = -3;
  E.matrix[2][1] = 6;
  E.matrix[2][2] = -3;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_calc_complements_large_matrix) {
  matrix_t A, R;
  int size = 5;
  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = (i == j) ? 1 : 0;
    }
  }

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, 0);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      double expected = (i == j) ? 1 : 0;
      ck_assert_double_eq_tol(R.matrix[i][j], expected, 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_calc_complements_negative_values) {
  matrix_t A, R, E;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  int res = s21_calc_complements(&A, &R);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = -4;
  E.matrix[0][1] = 3;
  E.matrix[1][0] = 2;
  E.matrix[1][1] = -1;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST
START_TEST(test_determinant_1x1) {
  matrix_t A;
  double result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, 5.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, -2.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3_nonzero) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, -40.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4x4) {
  matrix_t A;
  double result;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 2.0;
  A.matrix[0][3] = -1.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 1.0;
  A.matrix[2][3] = 0.0;
  A.matrix[3][0] = 0.0;
  A.matrix[3][1] = 0.0;
  A.matrix[3][2] = 0.0;
  A.matrix[3][3] = 1.0;

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, 1.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_null_input) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_determinant(NULL, &result), 1);
  ck_assert_int_eq(s21_determinant(&A, NULL), 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_non_square) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_determinant(&A, &result), 2);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_invalid_matrix) {
  matrix_t A;
  double result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  ck_assert_int_eq(s21_determinant(&A, &result), 1);
}
END_TEST

START_TEST(test_determinant_zero_matrix) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0.0;
    }
  }

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_upper_triangular) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 5.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 6.0;

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, 24.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_large_matrix) {
  matrix_t A;
  double result;
  int size = 5;
  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = (i == j) ? (i + 1) : 0.0;
    }
  }

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, 120.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_negative_values) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;

  int res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result, -2.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST
START_TEST(test_inverse_3x3) {
  matrix_t A, R, E;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(3, 3, &E);
  E.matrix[0][0] = 1;
  E.matrix[0][1] = -1;
  E.matrix[0][2] = 1;
  E.matrix[1][0] = -38;
  E.matrix[1][1] = 41;
  E.matrix[1][2] = -34;
  E.matrix[2][0] = 27;
  E.matrix[2][1] = -29;
  E.matrix[2][2] = 24;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_inverse_2x2) {
  matrix_t A, R, E;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = -2;
  E.matrix[0][1] = 1;
  E.matrix[1][0] = 1.5;
  E.matrix[1][1] = -0.5;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_inverse_null_input) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_inverse_matrix(NULL, &R), 1);
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_non_square) {
  matrix_t A, R;
  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 2);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_singular_matrix) {
  matrix_t A, R;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 2);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_1x1) {
  matrix_t A, R, E;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(1, 1, &E);
  E.matrix[0][0] = 0.2;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_inverse_1x1_zero) {
  matrix_t A, R;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 0;

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, 2);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_zero_det) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;

  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 2);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_large_matrix) {
  matrix_t A, R;
  int size = 4;
  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = (i == j) ? (i + 1) : 0;
    }
  }

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, 0);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      double expected = (i == j) ? 1.0 / (i + 1) : 0;
      ck_assert_double_eq_tol(R.matrix[i][j], expected, 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_inverse_negative_values) {
  matrix_t A, R, E;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, 0);

  s21_create_matrix(2, 2, &E);
  E.matrix[0][0] = 2;
  E.matrix[0][1] = -1;
  E.matrix[1][0] = -1.5;
  E.matrix[1][1] = 0.5;

  ck_assert_int_eq(s21_eq_matrix(&R, &E), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(test_inverse_identity_matrix) {
  matrix_t A, R;
  int size = 3;
  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = (i == j) ? 1 : 0;
    }
  }

  int res = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(res, 0);

  ck_assert_int_eq(s21_eq_matrix(&R, &A), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST
START_TEST(test_create_normal) {
  matrix_t mat;
  int res = s21_create_matrix(3, 4, &mat);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(mat.rows, 3);
  ck_assert_int_eq(mat.columns, 4);
  ck_assert_ptr_nonnull(mat.matrix);

  for (int i = 0; i < mat.rows; i++) {
    for (int j = 0; j < mat.columns; j++) {
      ck_assert_double_eq(mat.matrix[i][j], 0.0);
    }
  }

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_square) {
  matrix_t mat;
  int res = s21_create_matrix(5, 5, &mat);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(mat.rows, 5);
  ck_assert_int_eq(mat.columns, 5);
  ck_assert_ptr_nonnull(mat.matrix);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_single_element) {
  matrix_t mat;
  int res = s21_create_matrix(1, 1, &mat);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(mat.rows, 1);
  ck_assert_int_eq(mat.columns, 1);
  ck_assert_ptr_nonnull(mat.matrix);
  ck_assert_double_eq(mat.matrix[0][0], 0.0);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_zero_rows) {
  matrix_t mat;
  int res = s21_create_matrix(0, 5, &mat);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_create_zero_cols) {
  matrix_t mat;
  int res = s21_create_matrix(5, 0, &mat);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_create_negative_rows) {
  matrix_t mat;
  int res = s21_create_matrix(-3, 4, &mat);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_create_negative_cols) {
  matrix_t mat;
  int res = s21_create_matrix(3, -4, &mat);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_create_null_result) {
  int res = s21_create_matrix(3, 4, NULL);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_create_memory_failure) {
  matrix_t mat;
  int res = s21_create_matrix(10000, 10000, &mat);

  ck_assert(res == 0 || res == 1);
  if (res == 0) {
    s21_remove_matrix(&mat);
  }
}
END_TEST

START_TEST(test_create_matrix_structure) {
  matrix_t mat;
  int res = s21_create_matrix(2, 3, &mat);

  ck_assert_int_eq(res, 0);
  ck_assert_ptr_nonnull(mat.matrix);
  for (int i = 0; i < mat.rows; i++) {
    ck_assert_ptr_nonnull(mat.matrix[i]);
  }

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_remove_normal) {
  matrix_t mat;
  s21_create_matrix(3, 4, &mat);

  s21_remove_matrix(&mat);

  ck_assert_ptr_null(mat.matrix);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST

START_TEST(test_remove_null_matrix) {
  matrix_t mat = {0};
  mat.matrix = NULL;
  mat.rows = 0;
  mat.columns = 0;

  s21_remove_matrix(&mat);

  ck_assert_ptr_null(mat.matrix);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST

START_TEST(test_remove_null_input) { s21_remove_matrix(NULL); }
END_TEST

START_TEST(test_remove_already_removed) {
  matrix_t mat;
  s21_create_matrix(2, 2, &mat);
  s21_remove_matrix(&mat);

  s21_remove_matrix(&mat);

  ck_assert_ptr_null(mat.matrix);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST

START_TEST(test_remove_large_matrix) {
  matrix_t mat;
  s21_create_matrix(100, 100, &mat);

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      mat.matrix[i][j] = i * 100 + j;
    }
  }

  s21_remove_matrix(&mat);

  ck_assert_ptr_null(mat.matrix);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST
START_TEST(test_eq_equal) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_not_equal) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.1;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_different_sizes) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_null_input) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_eq_matrix(NULL, &A), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), 0);
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_precision) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 0.123456789;
  B.matrix[0][0] = 0.123456788;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_empty_matrix) {
  matrix_t A, B;
  A.rows = 0;
  A.columns = 0;
  B.rows = 0;
  B.columns = 0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
}
END_TEST

START_TEST(test_eq_negative_values) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;

  B.matrix[0][0] = -1.0;
  B.matrix[0][1] = -2.0;
  B.matrix[1][0] = -3.0;
  B.matrix[1][1] = -4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_large_matrix) {
  matrix_t A, B;
  int size = 100;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size, size, &B);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = i * size + j;
      B.matrix[i][j] = i * size + j;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  B.matrix[size - 1][size - 1] += 1e-8;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  B.matrix[size - 1][size - 1] += 0.1;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_equal_7) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.1234567;
  A.matrix[0][1] = 2.2345678;
  A.matrix[1][0] = 3.3456789;
  A.matrix[1][1] = 4.4567890;

  B.matrix[0][0] = 1.1234567;
  B.matrix[0][1] = 2.2345678;
  B.matrix[1][0] = 3.3456789;
  B.matrix[1][1] = 4.4567890;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_not_equal_7) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.1234567;
  A.matrix[0][1] = 2.2345678;
  A.matrix[1][0] = 3.3456789;
  A.matrix[1][1] = 4.4567890;

  B.matrix[0][0] = 1.1234567;
  B.matrix[0][1] = 2.2345678;
  B.matrix[1][0] = 3.3456789;
  B.matrix[1][1] = 4.4567891;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_precision_7) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 0.1234567499;
  B.matrix[0][0] = 0.1234567501;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_precision_6) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 0.1234564999;
  B.matrix[0][0] = 0.1234565001;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_edge_cases) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1.0000000;
  B.matrix[0][0] = 1.0000001;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  A.matrix[0][0] = 1.0000000;
  B.matrix[0][0] = 1.00000001;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_very_small_numbers) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 0.0000001;
  B.matrix[0][0] = 0.0000002;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  A.matrix[0][0] = 0.0000001;
  B.matrix[0][0] = 0.0000010;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_very_large_numbers) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1234567.0000000;
  B.matrix[0][0] = 1234567.0000001;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);

  A.matrix[0][0] = 1234567.0000000;
  B.matrix[0][0] = 1234567.0000010;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_matrix_suite(void) {
  Suite *s = suite_create("s21_matrix");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sum_correct);
  tcase_add_test(tc_core, test_sum_with_zero);
  tcase_add_test(tc_core, test_sum_negative);
  tcase_add_test(tc_core, test_sum_diff_sizes);
  tcase_add_test(tc_core, test_sum_null_input);
  tcase_add_test(tc_core, test_sum_invalid_sizes);
  tcase_add_test(tc_core, test_sum_large_matrix);
  tcase_add_test(tc_core, test_sub_correct);
  tcase_add_test(tc_core, test_sub_with_zero);
  tcase_add_test(tc_core, test_sub_negative);
  tcase_add_test(tc_core, test_sub_diff_sizes);
  tcase_add_test(tc_core, test_sub_null_input);
  tcase_add_test(tc_core, test_sub_invalid_sizes);
  tcase_add_test(tc_core, test_sub_large_matrix);
  tcase_add_test(tc_core, test_sub_itself);
  tcase_add_test(tc_core, test_mult_number_correct);
  tcase_add_test(tc_core, test_mult_number_zero);
  tcase_add_test(tc_core, test_mult_number_negative);
  tcase_add_test(tc_core, test_mult_number_null_input);
  tcase_add_test(tc_core, test_mult_number_invalid_matrix);
  tcase_add_test(tc_core, test_mult_number_large_matrix);
  tcase_add_test(tc_core, test_mult_number_fractional);
  tcase_add_test(tc_core, test_mult_number_zero_matrix);
  tcase_add_test(tc_core, test_mult_matrix_correct);
  tcase_add_test(tc_core, test_mult_matrix_incompatible_sizes);
  tcase_add_test(tc_core, test_mult_matrix_null_input);
  tcase_add_test(tc_core, test_mult_matrix_invalid_sizes);
  tcase_add_test(tc_core, test_mult_matrix_large);
  tcase_add_test(tc_core, test_mult_matrix_zero);
  tcase_add_test(tc_core, test_mult_matrix_identity);
  tcase_add_test(tc_core, test_mult_matrix_negative_values);
  tcase_add_test(tc_core, test_transpose_correct);
  tcase_add_test(tc_core, test_transpose_square);
  tcase_add_test(tc_core, test_transpose_single_element);
  tcase_add_test(tc_core, test_transpose_null_input);
  tcase_add_test(tc_core, test_transpose_invalid_sizes);
  tcase_add_test(tc_core, test_transpose_zero_matrix);
  tcase_add_test(tc_core, test_transpose_large_matrix);
  tcase_add_test(tc_core, test_transpose_negative_values);
  tcase_add_test(tc_core, test_minor_3x3_center);
  tcase_add_test(tc_core, test_minor_3x3_corner);
  tcase_add_test(tc_core, test_minor_4x4_middle);
  tcase_add_test(tc_core, test_minor_2x2);
  tcase_add_test(tc_core, test_minor_edge_row_col);
  tcase_add_test(tc_core, test_minor_large_matrix);
  tcase_add_test(tc_core, test_minor_negative_values);
  tcase_add_test(tc_core, test_minor_success_3x3);
  tcase_add_test(tc_core, test_minor_invalid_input);
  tcase_add_test(tc_core, test_minor_too_small_matrix);
  tcase_add_test(tc_core, test_minor_edge_positions);
  tcase_add_test(tc_core, test_minor_rectangular_matrix);
  tcase_add_test(tc_core, test_minor_memory_allocation_failure);
  tcase_add_test(tc_core, test_minor_negative_values_2);
  tcase_add_test(tc_core, test_calc_complements_3x3);
  tcase_add_test(tc_core, test_calc_complements_2x2);
  tcase_add_test(tc_core, test_calc_complements_1x1);
  tcase_add_test(tc_core, test_calc_complements_null_input);
  tcase_add_test(tc_core, test_calc_complements_non_square);
  tcase_add_test(tc_core, test_calc_complements_zero_det);
  tcase_add_test(tc_core, test_calc_complements_large_matrix);
  tcase_add_test(tc_core, test_calc_complements_negative_values);
  tcase_add_test(tc_core, test_determinant_1x1);
  tcase_add_test(tc_core, test_determinant_2x2);
  tcase_add_test(tc_core, test_determinant_3x3);
  tcase_add_test(tc_core, test_determinant_3x3_nonzero);
  tcase_add_test(tc_core, test_determinant_4x4);
  tcase_add_test(tc_core, test_determinant_null_input);
  tcase_add_test(tc_core, test_determinant_non_square);
  tcase_add_test(tc_core, test_determinant_invalid_matrix);
  tcase_add_test(tc_core, test_determinant_zero_matrix);
  tcase_add_test(tc_core, test_determinant_upper_triangular);
  tcase_add_test(tc_core, test_determinant_large_matrix);
  tcase_add_test(tc_core, test_determinant_negative_values);
  tcase_add_test(tc_core, test_inverse_3x3);
  tcase_add_test(tc_core, test_inverse_2x2);
  tcase_add_test(tc_core, test_inverse_null_input);
  tcase_add_test(tc_core, test_inverse_non_square);
  tcase_add_test(tc_core, test_inverse_singular_matrix);
  tcase_add_test(tc_core, test_inverse_1x1);
  tcase_add_test(tc_core, test_inverse_1x1_zero);
  tcase_add_test(tc_core, test_inverse_zero_det);
  tcase_add_test(tc_core, test_inverse_large_matrix);
  tcase_add_test(tc_core, test_inverse_negative_values);
  tcase_add_test(tc_core, test_inverse_identity_matrix);
  tcase_add_test(tc_core, test_create_normal);
  tcase_add_test(tc_core, test_create_square);
  tcase_add_test(tc_core, test_create_single_element);
  tcase_add_test(tc_core, test_create_zero_rows);
  tcase_add_test(tc_core, test_create_zero_cols);
  tcase_add_test(tc_core, test_create_negative_rows);
  tcase_add_test(tc_core, test_create_negative_cols);
  tcase_add_test(tc_core, test_create_null_result);
  tcase_add_test(tc_core, test_create_memory_failure);
  tcase_add_test(tc_core, test_create_matrix_structure);
  tcase_add_test(tc_core, test_remove_normal);
  tcase_add_test(tc_core, test_remove_null_matrix);
  tcase_add_test(tc_core, test_remove_null_input);
  tcase_add_test(tc_core, test_remove_already_removed);
  tcase_add_test(tc_core, test_remove_large_matrix);
  tcase_add_test(tc_core, test_eq_equal);
  tcase_add_test(tc_core, test_eq_not_equal);
  tcase_add_test(tc_core, test_eq_different_sizes);
  tcase_add_test(tc_core, test_eq_null_input);
  tcase_add_test(tc_core, test_eq_precision);
  tcase_add_test(tc_core, test_eq_empty_matrix);
  tcase_add_test(tc_core, test_eq_negative_values);
  tcase_add_test(tc_core, test_eq_large_matrix);
  tcase_add_test(tc_core, test_eq_equal_7);
  tcase_add_test(tc_core, test_eq_not_equal_7);
  tcase_add_test(tc_core, test_eq_precision_7);
  tcase_add_test(tc_core, test_eq_precision_6);
  tcase_add_test(tc_core, test_eq_edge_cases);
  tcase_add_test(tc_core, test_eq_very_small_numbers);
  tcase_add_test(tc_core, test_eq_very_large_numbers);
  suite_add_tcase(s, tc_core);
  return s;
}
int main(void) {
  int number_failed;
  Suite *s = s21_matrix_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
