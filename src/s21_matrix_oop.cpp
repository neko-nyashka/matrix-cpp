#include "s21_matrix_oop.h"

int S21Matrix::S21Get_rows() const { return rows_; }
int S21Matrix::S21Get_cols() const { return cols_; }
double** S21Matrix::S21Get_matrix() const { return matrix_; }

void S21Matrix::S21DeallocateMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}
void S21Matrix::S21AllocateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::~S21Matrix() { S21DeallocateMatrix(); }

S21Matrix::S21Matrix() {
  rows_ = 2;
  cols_ = 2;
  matrix_ = nullptr;
  S21AllocateMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::out_of_range(
        "Поля матрицы должны быть положительными целыми числами\n");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = nullptr;
  S21AllocateMatrix();
}

void S21Matrix::S21Set_rows(int rows) {
  if (rows <= 0) {
    throw std::out_of_range("Число строк матрицы должно быть положительным\n");
  }
  if (rows != rows_) {
    double** new_matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
      new_matrix[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        if (i < rows_)
          new_matrix[i][j] = matrix_[i][j];
        else
          new_matrix[i][j] = 0.0;
      }
    }
    S21DeallocateMatrix();
    matrix_ = new_matrix;
    rows_ = rows;
  }
}

void S21Matrix::S21Set_cols(int cols) {
  if (cols <= 0) {
    throw std::out_of_range(
        "Число столбцов матрицы должно быть положительным\n");
  }
  if (cols != cols_) {
    for (int i = 0; i < rows_; i++) {
      double* new_row = new double[cols];
      for (int j = 0; j < cols; j++) {
        if (j < cols_)
          new_row[j] = matrix_[i][j];
        else
          new_row[j] = 0.0;
      }
      delete[] matrix_[i];
      matrix_[i] = new_row;
    }
    cols_ = cols;
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    S21DeallocateMatrix();

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21DeallocateMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    S21AllocateMatrix();
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  }
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) res = false;
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Сложение возможно только для матриц одинаковых размерностей\n");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Вычитание возможно только для матриц одинаковых размерностей\n");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Умножение возможно только если число столбцов первой матрицы равно "
        "числу строк второй матрицы\n");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}
S21Matrix S21Matrix::S21Get_minor_matrix(int i_, int j_) {
  if (rows_ <= 1 || cols_ <= 1) {
    throw std::logic_error(
        "Вычисление минора возможно для матрицы большей размерности чем 1х1\n");
  }
  if (i_ < 0 || i_ >= rows_ || j_ < 0 || j_ >= cols_) {
    throw std::out_of_range("Некорректные индексы\n");
  }
  S21Matrix result(rows_ - 1, cols_ - 1);
  int mi = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != i_) {
      int mj = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != j_) {
          result.matrix_[mi][mj] = matrix_[i][j];
          mj++;
        }
      }
      mi++;
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double det = 0;
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица не является квадратной\n");
  }
  int n = rows_;
  if (n == 1) {
    det = matrix_[0][0];
  } else if (n == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    double minor_det;
    int sign = 1;
    for (int i = 0; i < n; i++) {
      S21Matrix M(S21Get_minor_matrix(i, 0));
      minor_det = M.Determinant();
      det += sign * matrix_[i][0] * minor_det;
      sign *= -1;
    }
  }

  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица не является квадратной\n");
  }

  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result.matrix_[0][0] = 1;

  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix minor(S21Get_minor_matrix(i, j));
        double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
        result.matrix_[i][j] = sign * minor.Determinant();
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица не является квадратной\n");
  }
  double det = Determinant();
  if (det == 0) {
    throw std::invalid_argument("Определитель матрицы равен 0\n");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    S21Matrix temp = CalcComplements().Transpose();
    temp.MulNumber(1.0 / det);
    result = std::move(temp);
  }

  return result;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Сложение возможно только для матриц одинаковых размерностей\n");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Вычитание возможно только для матриц одинаковых размерностей\n");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return result;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Умножение возможно только если число столбцов первой матрицы равно "
        "числу строк второй матрицы\n");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] * num;
    }
  }
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("Индекс за границами матрицы\n");
  }
  return matrix_[row][col];
}
