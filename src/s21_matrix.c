#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;

  if (rows <= 0 || columns <= 0 || result == NULL) {
    error = 1;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      error = 1;
    } else {
      result->rows = rows;
      result->columns = columns;
      int alloc_success = 1;

      for (int i = 0; i < rows && alloc_success; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          alloc_success = 0;
          error = 1;
        }
      }

      if (!alloc_success) {
        s21_remove_matrix(result);
      }
    }
  }

  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) {
        if (A->matrix[i] != NULL) free(A->matrix[i]);
      }
      free(A->matrix);
      A->matrix = NULL;
    }
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 1;
  if (A == NULL || B == NULL || A->rows != B->rows ||
      A->columns != B->columns || A->rows <= 0 || A->columns <= 0 ||
      B->rows <= 0 || B->columns <= 0) {
    res = 0;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double a = round(A->matrix[i][j] * 1e7) / 1e7;
        double b = round(B->matrix[i][j] * 1e7) / 1e7;
        if (fabs(a - b) > 1e-7) {
          res = 0;
        }
      }
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (A == NULL || B == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    res = 1;
  } else {
    if (A->columns != B->columns || A->rows != B->rows) {
      res = 2;
    } else {
      s21_create_matrix(A->rows, A->columns, result);
      result->columns = A->columns;
      result->rows = A->rows;
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A == NULL || B == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    error = 1;
  } else {
    if (A->columns != B->columns || A->rows != B->rows) {
      error = 2;
    } else {
      s21_create_matrix(A->rows, A->columns, result);
      result->columns = A->columns;
      result->rows = A->rows;
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    error = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    result->columns = A->columns;
    result->rows = A->rows;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A == NULL || B == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    error = 1;
  } else if (A->columns != B->rows) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    result->rows = A->rows;
    result->columns = B->columns;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    error = 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    result->rows = A->columns;
    result->columns = A->rows;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return error;
}
int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  double det = 0;

  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    error = 1;
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    int n = A->rows;
    if (n == 1) {
      det = A->matrix[0][0];
    } else if (n == 2) {
      det =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      matrix_t M;
      double minor_det;
      int sign = 1;

      for (int i = 0; i < n && !error; i++) {
        error = s21_minor(i, 0, A, &M);
        if (!error) {
          error = s21_determinant(&M, &minor_det);
          if (!error) det += sign * A->matrix[i][0] * minor_det;
          sign *= -1;
          s21_remove_matrix(&M);
        }
      }
    }
  }

  if (!error) *result = det;

  return error;
}

void s21_get_minor_matrix(matrix_t *A, int i_, int j_, matrix_t *M) {
  int mi = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != i_) {
      int mj = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != j_) {
          M->matrix[mi][mj] = A->matrix[i][j];
          mj++;
        }
      }
      mi++;
    }
  }
}
int s21_minor(int i_, int j_, matrix_t *A, matrix_t *M) {
  int error = 0;

  if (A == NULL || M == NULL || A->rows <= 0 || A->columns <= 0) {
    error = 1;
  } else if (A->rows <= 1 || A->columns <= 1) {
    error = 2;
  } else {
    error = s21_create_matrix(A->rows - 1, A->columns - 1, M);

    if (!error) {
      s21_get_minor_matrix(A, i_, j_, M);
    }
  }

  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A == NULL || result == NULL || A->rows <= 1 || A->columns <= 1) {
    error = 1;
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    result->rows = A->columns;
    result->columns = A->rows;
    int sign;
    matrix_t M;
    for (int i = 0; i < result->rows && !error; i++) {
      for (int j = 0; j < result->columns && !error; j++) {
        sign = (i + j) % 2 ? -1 : 1;
        error = s21_minor(i, j, A, &M);
        if (!error) {
          error = s21_determinant(&M, &(result->matrix[i][j]));
          if (!error) result->matrix[i][j] *= sign;
          s21_remove_matrix(&M);
        }
      }
    }
  }

  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  double det = 0;

  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    error = 1;
  } else if (A->rows != A->columns) {
    error = 2;
  } else if (A->rows == 1 && A->columns == 1 && A->matrix[0][0] != 0) {
    s21_create_matrix(1, 1, result);
    result->columns = 1;
    result->rows = 1;
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
  } else if (A->rows == 1 && A->columns == 1 && A->matrix[0][0] == 0) {
    error = 2;
  } else {
    error = s21_determinant(A, &det);
    if (!error) {
      if (det == 0) {
        error = 2;
      } else {
        matrix_t complements, transposed;
        error = s21_calc_complements(A, &complements);
        if (!error) {
          error = s21_transpose(&complements, &transposed);
          if (!error) error = s21_mult_number(&transposed, 1.0 / det, result);
          if (!error) s21_remove_matrix(&transposed);
          if (!error) s21_remove_matrix(&complements);
        }
      }
    }
  }
  return error;
}
