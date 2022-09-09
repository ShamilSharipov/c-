#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  static double Help(const S21Matrix* Matrix);
  static void minor(int row, int cols, const S21Matrix* other, S21Matrix* M);
  void Clean();
  void inCorrectMatrix() const;
  void newMemory();

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix& other) const;
  const double& operator()(int i, int j) const;
  double& operator()(int i, int j);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;

  double Determinant() const;
  S21Matrix InverseMatrix() const;

  int GetRows() const;
  int GetCols() const;
  void SetRows(int new_rows);
  void SetCols(int new_cols);
};

#endif  // SRC_S21_MATRIX_OOP_H_
