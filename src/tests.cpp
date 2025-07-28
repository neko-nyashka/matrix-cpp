#include <gtest/gtest.h>

#include "s21_matrix_oop.h"
TEST(S21MatrixAccessors, GettersWorkCorrectly) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.S21Get_rows(), 3);
  EXPECT_EQ(m.S21Get_cols(), 4);
}

TEST(S21MatrixMemory, AllocateMatrixCreatesZeroMatrix) {
  S21Matrix m(2, 2);

  double** matrix = m.S21Get_matrix();
  ASSERT_NE(matrix, nullptr);

  for (int i = 0; i < m.S21Get_rows(); ++i) {
    EXPECT_NE(matrix[i], nullptr);
    for (int j = 0; j < m.S21Get_cols(); ++j) {
      EXPECT_DOUBLE_EQ(matrix[i][j], 0.0);
    }
  }

  m.S21DeallocateMatrix();
}

TEST(S21MatrixMemory, DeallocateMatrixFreesMemory) {
  S21Matrix m(2, 2);
  m.S21DeallocateMatrix();

  double** matrix = m.S21Get_matrix();
  EXPECT_EQ(matrix, nullptr);
}

TEST(S21MatrixConstructor, DefaultConstructorCreates2x2Matrix) {
  S21Matrix m;
  EXPECT_EQ(m.S21Get_rows(), 2);
  EXPECT_EQ(m.S21Get_cols(), 2);

  double** matrix = m.S21Get_matrix();
  ASSERT_NE(matrix, nullptr);

  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j) EXPECT_DOUBLE_EQ(matrix[i][j], 0.0);
}

TEST(S21MatrixConstructor, ParamConstructorCreatesCorrectMatrix) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.S21Get_rows(), 3);
  EXPECT_EQ(m.S21Get_cols(), 4);

  double** matrix = m.S21Get_matrix();
  ASSERT_NE(matrix, nullptr);

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j) EXPECT_DOUBLE_EQ(matrix[i][j], 0.0);
}

TEST(S21MatrixConstructor, ParamConstructorThrowsIfInvalid) {
  EXPECT_THROW(S21Matrix(-1, 2), std::out_of_range);
  EXPECT_THROW(S21Matrix(3, 0), std::out_of_range);
  EXPECT_THROW(S21Matrix(0, 0), std::out_of_range);
}

TEST(S21MatrixDestructor, DestructorFreesMemory) {
  S21Matrix* m = new S21Matrix(2, 2);
  double** matrix_before = m->S21Get_matrix();
  ASSERT_NE(matrix_before, nullptr);
  delete m;
  SUCCEED();
}

TEST(S21MatrixMutators, SetRowsPositiveValid) {
  S21Matrix m(2, 3);
  m.S21Set_rows(4);

  EXPECT_EQ(m.S21Get_rows(), 4);
  EXPECT_EQ(m.S21Get_cols(), 3);

  double** matrix = m.S21Get_matrix();
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) EXPECT_DOUBLE_EQ(matrix[i][j], 0.0);
  for (int i = 2; i < 4; i++)
    for (int j = 0; j < 3; j++) EXPECT_DOUBLE_EQ(matrix[i][j], 0.0);
}

TEST(S21MatrixMutators, SetRowsSmaller) {
  S21Matrix m(4, 2);
  m.S21Set_rows(2);
  EXPECT_EQ(m.S21Get_rows(), 2);
}

TEST(S21MatrixMutators, SetRowsThrowsIfInvalid) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m.S21Set_rows(0), std::out_of_range);
  EXPECT_THROW(m.S21Set_rows(-3), std::out_of_range);
}

TEST(S21MatrixMutators, SetRowsSameDoesNothing) {
  S21Matrix m(3, 3);
  m.S21Set_rows(3);
  EXPECT_EQ(m.S21Get_rows(), 3);
}
TEST(S21MatrixMutators, SetColsPositiveValid) {
  S21Matrix m(3, 2);
  m.S21Set_cols(4);

  EXPECT_EQ(m.S21Get_rows(), 3);
  EXPECT_EQ(m.S21Get_cols(), 4);

  double** matrix = m.S21Get_matrix();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) EXPECT_DOUBLE_EQ(matrix[i][j], 0.0);
    for (int j = 2; j < 4; j++) EXPECT_DOUBLE_EQ(matrix[i][j], 0.0);
  }
}

TEST(S21MatrixMutators, SetColsSmaller) {
  S21Matrix m(2, 4);
  m.S21Set_cols(2);
  EXPECT_EQ(m.S21Get_cols(), 2);
}

TEST(S21MatrixMutators, SetColsThrowsIfInvalid) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m.S21Set_cols(0), std::out_of_range);
  EXPECT_THROW(m.S21Set_cols(-1), std::out_of_range);
}

TEST(S21MatrixMutators, SetColsSameDoesNothing) {
  S21Matrix m(3, 3);
  m.S21Set_cols(3);
  EXPECT_EQ(m.S21Get_cols(), 3);
}
TEST(S21MatrixConstructors, CopyConstructorCopiesData) {
  S21Matrix m1(2, 2);
  double** mat = m1.S21Get_matrix();
  mat[0][0] = 5.5;
  mat[1][1] = 3.3;

  S21Matrix m2(m1);

  EXPECT_EQ(m2.S21Get_rows(), 2);
  EXPECT_EQ(m2.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(m2.S21Get_matrix()[0][0], 5.5);
  EXPECT_DOUBLE_EQ(m2.S21Get_matrix()[1][1], 3.3);
}
TEST(S21MatrixConstructors, MoveConstructorTransfersOwnership) {
  S21Matrix m1(2, 2);
  double** mat = m1.S21Get_matrix();
  mat[0][0] = 9.9;

  S21Matrix m2(std::move(m1));

  EXPECT_EQ(m2.S21Get_rows(), 2);
  EXPECT_EQ(m2.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(m2.S21Get_matrix()[0][0], 9.9);

  EXPECT_EQ(m1.S21Get_matrix(), nullptr);
  EXPECT_EQ(m1.S21Get_rows(), 0);
  EXPECT_EQ(m1.S21Get_cols(), 0);
}
TEST(S21MatrixOperators, MoveAssignmentOperatorWorks) {
  S21Matrix a(2, 2);
  a.S21Get_matrix()[0][0] = 1.0;

  S21Matrix b(1, 1);
  b = std::move(a);

  EXPECT_EQ(b.S21Get_rows(), 2);
  EXPECT_EQ(b.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(b.S21Get_matrix()[0][0], 1.0);
}
TEST(S21MatrixOperations, EqMatrixReturnsTrueOnEqual) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a.S21Get_matrix()[1][1] = 5.0;
  b.S21Get_matrix()[1][1] = 5.0;
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(S21MatrixOperations, EqMatrixReturnsFalseOnDifferentSize) {
  S21Matrix a(2, 2);
  S21Matrix b(3, 2);
  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(S21MatrixOperations, EqMatrixReturnsFalseOnDifferentValues) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a.S21Get_matrix()[0][0] = 1.0;
  b.S21Get_matrix()[0][0] = 2.0;
  EXPECT_FALSE(a.EqMatrix(b));
}
TEST(S21MatrixOperations, SumMatrixAddsCorrectly) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a.S21Get_matrix()[0][0] = 1.0;
  b.S21Get_matrix()[0][0] = 2.0;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[0][0], 3.0);
}

TEST(S21MatrixOperations, SumMatrixThrowsOnDifferentSize) {
  S21Matrix a(2, 2);
  S21Matrix b(3, 2);
  EXPECT_THROW(a.SumMatrix(b), std::out_of_range);
}
TEST(S21MatrixOperations, SubMatrixSubtractsCorrectly) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a.S21Get_matrix()[0][0] = 5.0;
  b.S21Get_matrix()[0][0] = 3.0;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[0][0], 2.0);
}

TEST(S21MatrixOperations, SubMatrixThrowsOnDifferentSize) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 3);
  EXPECT_THROW(a.SubMatrix(b), std::out_of_range);
}
TEST(S21MatrixOperations, MulNumberMultipliesCorrectly) {
  S21Matrix a(2, 2);
  a.S21Get_matrix()[1][1] = 2.0;
  a.MulNumber(3.0);
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[1][1], 6.0);
}
TEST(S21MatrixOperations, MulMatrixMultipliesCorrectly) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);

  a.S21Get_matrix()[0][0] = 1;
  a.S21Get_matrix()[0][1] = 2;
  a.S21Get_matrix()[0][2] = 3;
  a.S21Get_matrix()[1][0] = 4;
  a.S21Get_matrix()[1][1] = 5;
  a.S21Get_matrix()[1][2] = 6;

  b.S21Get_matrix()[0][0] = 7;
  b.S21Get_matrix()[0][1] = 8;
  b.S21Get_matrix()[1][0] = 9;
  b.S21Get_matrix()[1][1] = 10;
  b.S21Get_matrix()[2][0] = 11;
  b.S21Get_matrix()[2][1] = 12;

  a.MulMatrix(b);

  EXPECT_EQ(a.S21Get_rows(), 2);
  EXPECT_EQ(a.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[0][0], 58);
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[0][1], 64);
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[1][0], 139);
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[1][1], 154);
}

TEST(S21MatrixOperations, MulMatrixThrowsOnInvalidSize) {
  S21Matrix a(2, 3);
  S21Matrix b(4, 2);
  EXPECT_THROW(a.MulMatrix(b), std::invalid_argument);
}
TEST(S21MatrixOperations, TransposeWorksCorrectly) {
  S21Matrix a(2, 3);
  a.S21Get_matrix()[0][1] = 7;
  a.S21Get_matrix()[1][2] = 9;

  S21Matrix t = a.Transpose();

  EXPECT_EQ(t.S21Get_rows(), 3);
  EXPECT_EQ(t.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(t.S21Get_matrix()[1][0], 7);
  EXPECT_DOUBLE_EQ(t.S21Get_matrix()[2][1], 9);
}

TEST(S21MatrixAdvanced, GetMinorMatrixCorrect) {
  S21Matrix a(3, 3);
  int val = 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) a.S21Get_matrix()[i][j] = val++;

  S21Matrix minor = a.S21Get_minor_matrix(1, 1);

  EXPECT_EQ(minor.S21Get_rows(), 2);
  EXPECT_EQ(minor.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(minor.S21Get_matrix()[0][0], 1.0);
  EXPECT_DOUBLE_EQ(minor.S21Get_matrix()[0][1], 3.0);
  EXPECT_DOUBLE_EQ(minor.S21Get_matrix()[1][0], 7.0);
  EXPECT_DOUBLE_EQ(minor.S21Get_matrix()[1][1], 9.0);
}

TEST(S21MatrixAdvanced, GetMinorMatrixThrowsOnSmallMatrix) {
  S21Matrix a(1, 1);
  EXPECT_THROW(a.S21Get_minor_matrix(0, 0), std::logic_error);
}

TEST(S21MatrixAdvanced, Determinant1x1) {
  S21Matrix a(1, 1);
  a.S21Get_matrix()[0][0] = 5.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), 5.0);
}

TEST(S21MatrixAdvanced, Determinant2x2) {
  S21Matrix a(2, 2);
  a.S21Get_matrix()[0][0] = 1.0;
  a.S21Get_matrix()[0][1] = 2.0;
  a.S21Get_matrix()[1][0] = 3.0;
  a.S21Get_matrix()[1][1] = 4.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), -2.0);
}

TEST(S21MatrixAdvanced, Determinant3x3) {
  S21Matrix a(3, 3);
  a.S21Get_matrix()[0][0] = 6;
  a.S21Get_matrix()[0][1] = 1;
  a.S21Get_matrix()[0][2] = 1;
  a.S21Get_matrix()[1][0] = 4;
  a.S21Get_matrix()[1][1] = -2;
  a.S21Get_matrix()[1][2] = 5;
  a.S21Get_matrix()[2][0] = 2;
  a.S21Get_matrix()[2][1] = 8;
  a.S21Get_matrix()[2][2] = 7;
  EXPECT_DOUBLE_EQ(a.Determinant(), -306.0);
}

TEST(S21MatrixAdvanced, DeterminantThrowsOnNonSquare) {
  S21Matrix a(2, 3);
  EXPECT_THROW(a.Determinant(), std::invalid_argument);
}
TEST(S21MatrixAdvanced, CalcComplements2x2) {
  S21Matrix a(2, 2);
  a.S21Get_matrix()[0][0] = 3;
  a.S21Get_matrix()[0][1] = 4;
  a.S21Get_matrix()[1][0] = 2;
  a.S21Get_matrix()[1][1] = 5;

  S21Matrix result = a.CalcComplements();

  EXPECT_DOUBLE_EQ(result.S21Get_matrix()[0][0], 5);
  EXPECT_DOUBLE_EQ(result.S21Get_matrix()[0][1], -2);
  EXPECT_DOUBLE_EQ(result.S21Get_matrix()[1][0], -4);
  EXPECT_DOUBLE_EQ(result.S21Get_matrix()[1][1], 3);
}

TEST(S21MatrixAdvanced, CalcComplements1x1) {
  S21Matrix a(1, 1);
  a.S21Get_matrix()[0][0] = 5;

  S21Matrix result = a.CalcComplements();
  EXPECT_DOUBLE_EQ(result.S21Get_matrix()[0][0], 1);
}

TEST(S21MatrixAdvanced, CalcComplementsThrowsOnNonSquare) {
  S21Matrix a(2, 3);
  EXPECT_THROW(a.CalcComplements(), std::invalid_argument);
}
TEST(S21MatrixAdvanced, InverseMatrix2x2) {
  S21Matrix a(2, 2);
  a.S21Get_matrix()[0][0] = 4;
  a.S21Get_matrix()[0][1] = 7;
  a.S21Get_matrix()[1][0] = 2;
  a.S21Get_matrix()[1][1] = 6;

  S21Matrix result = a.InverseMatrix();

  EXPECT_NEAR(result.S21Get_matrix()[0][0], 0.6, 1e-7);
  EXPECT_NEAR(result.S21Get_matrix()[0][1], -0.7, 1e-7);
  EXPECT_NEAR(result.S21Get_matrix()[1][0], -0.2, 1e-7);
  EXPECT_NEAR(result.S21Get_matrix()[1][1], 0.4, 1e-7);
}

TEST(S21MatrixAdvanced, InverseMatrixThrowsIfDetZero) {
  S21Matrix a(2, 2);
  a.S21Get_matrix()[0][0] = 1;
  a.S21Get_matrix()[0][1] = 2;
  a.S21Get_matrix()[1][0] = 2;
  a.S21Get_matrix()[1][1] = 4;

  EXPECT_THROW(a.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixAdvanced, InverseMatrixThrowsIfNotSquare) {
  S21Matrix a(2, 3);
  EXPECT_THROW(a.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixOperators, SumOperatorValid) {
  S21Matrix a(2, 2), b(2, 2);
  a.S21Get_matrix()[0][0] = 1;
  b.S21Get_matrix()[0][0] = 2;
  S21Matrix res = a + b;
  EXPECT_DOUBLE_EQ(res.S21Get_matrix()[0][0], 3);
}

TEST(S21MatrixOperators, SubOperatorValid) {
  S21Matrix a(2, 2), b(2, 2);
  a.S21Get_matrix()[1][1] = 5;
  b.S21Get_matrix()[1][1] = 2;
  S21Matrix res = a - b;
  EXPECT_DOUBLE_EQ(res.S21Get_matrix()[1][1], 3);
}

TEST(S21MatrixOperators, MulMatrixOperatorValid) {
  S21Matrix a(2, 3), b(3, 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) a.S21Get_matrix()[i][j] = 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) b.S21Get_matrix()[i][j] = 2;

  S21Matrix res = a * b;
  EXPECT_DOUBLE_EQ(res.S21Get_matrix()[0][0], 6);
  EXPECT_DOUBLE_EQ(res.S21Get_matrix()[1][1], 6);
}

TEST(S21MatrixOperators, MulNumberOperatorValid) {
  S21Matrix a(2, 2);
  a.S21Get_matrix()[0][0] = 2;
  S21Matrix res = a * 3.0;
  EXPECT_DOUBLE_EQ(res.S21Get_matrix()[0][0], 6);
}
TEST(S21MatrixOperators, SumOperatorThrows) {
  S21Matrix a(2, 2), b(3, 3);
  EXPECT_THROW(a + b, std::out_of_range);
}

TEST(S21MatrixOperators, SubOperatorThrows) {
  S21Matrix a(2, 2), b(1, 2);
  EXPECT_THROW(a - b, std::out_of_range);
}

TEST(S21MatrixOperators, MulMatrixOperatorThrows) {
  S21Matrix a(2, 3), b(4, 2);
  EXPECT_THROW(a * b, std::invalid_argument);
}
TEST(S21MatrixOperators, CompoundPlusEquals) {
  S21Matrix a(2, 2), b(2, 2);
  a.S21Get_matrix()[0][0] = 1;
  b.S21Get_matrix()[0][0] = 2;
  a += b;
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[0][0], 3);
}

TEST(S21MatrixOperators, CompoundMinusEquals) {
  S21Matrix a(2, 2), b(2, 2);
  a.S21Get_matrix()[0][1] = 5;
  b.S21Get_matrix()[0][1] = 1;
  a -= b;
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[0][1], 4);
}

TEST(S21MatrixOperators, CompoundMulMatrixEquals) {
  S21Matrix a(2, 3), b(3, 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) a.S21Get_matrix()[i][j] = 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) b.S21Get_matrix()[i][j] = 2;
  a *= b;
  EXPECT_EQ(a.S21Get_rows(), 2);
  EXPECT_EQ(a.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[0][0], 6);
}

TEST(S21MatrixOperators, CompoundMulNumberEquals) {
  S21Matrix a(2, 2);
  a.S21Get_matrix()[1][1] = 3;
  a *= 2.0;
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[1][1], 6.0);
}
TEST(S21MatrixOperators, EqualOperatorTrue) {
  S21Matrix a(2, 2), b(2, 2);
  a.S21Get_matrix()[1][1] = 4;
  b.S21Get_matrix()[1][1] = 4;
  EXPECT_TRUE(a == b);
}

TEST(S21MatrixOperators, EqualOperatorFalse) {
  S21Matrix a(2, 2), b(2, 2);
  a.S21Get_matrix()[1][0] = 3;
  b.S21Get_matrix()[1][0] = 7;
  EXPECT_FALSE(a == b);
}
TEST(S21MatrixOperators, AccessOperatorValid) {
  S21Matrix a(3, 3);
  a(1, 1) = 7.5;
  EXPECT_DOUBLE_EQ(a.S21Get_matrix()[1][1], 7.5);
}

TEST(S21MatrixOperators, AccessOperatorThrows) {
  S21Matrix a(2, 2);
  EXPECT_THROW(a(2, 0), std::out_of_range);
  EXPECT_THROW(a(-1, 1), std::out_of_range);
}
TEST(S21MatrixAssignmentTest, BasicCopyAssignment) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B;
  B = A;

  EXPECT_EQ(B.S21Get_rows(), 2);
  EXPECT_EQ(B.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(B(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(B(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(B(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(B(1, 1), 4.0);
}

TEST(S21MatrixAssignmentTest, PreviousDataIsCleared) {
  S21Matrix A(2, 2);
  A(0, 0) = 9.0;

  S21Matrix B(3, 3);
  B(1, 1) = 99.0;

  B = A;

  EXPECT_EQ(B.S21Get_rows(), 2);
  EXPECT_EQ(B.S21Get_cols(), 2);
  EXPECT_DOUBLE_EQ(B(0, 0), 9.0);
}

TEST(S21MatrixAssignmentTest, ChainAssignment) {
  S21Matrix A(2, 2);
  A(0, 0) = 5.0;

  S21Matrix B, C;
  C = B = A;

  EXPECT_DOUBLE_EQ(B(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(C(0, 0), 5.0);
}