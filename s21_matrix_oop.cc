#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(2, 2) {}

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows_ = rows;
  this->cols_ = cols;
  if (this->rows_ <= 0 || this->cols_ <= 0) {
    throw(std::range_error("Error!\nIncorrect matrix"));
  }
  this->newMemory();
}

S21Matrix::S21Matrix(const S21Matrix& other) { *this = other; }

S21Matrix::S21Matrix(S21Matrix&& other) { *this = other; }

S21Matrix::~S21Matrix() { Clean(); }

void S21Matrix::Clean() {
  if ((rows_ > 0 && cols_ > 0) && matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }

    delete[] matrix_;
    matrix_ = nullptr;
  }
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->inCorrectMatrix();
  other.inCorrectMatrix();
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix Sum(this->rows_, this->cols_);
  Sum = *this;
  return Sum += other;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  other.inCorrectMatrix();

  if (this == &other) {
    return *this;
  }

  if (this->matrix_ != nullptr) {
    this->Clean();
  }

  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;

  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  other.inCorrectMatrix();

  if (this == &other) {
    return *this;
  }
  if (this->matrix_ != nullptr) {
    this->Clean();
  }
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->newMemory();
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->inCorrectMatrix();
  other.inCorrectMatrix();
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  if (this->cols_ == other.cols_ && this->rows_ == other.rows_) {
    for (int i = 0; i < this->rows_; ++i) {
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix Sub(this->rows_, this->cols_);
  Sub = *this;
  return Sub -= other;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->inCorrectMatrix();
  other.inCorrectMatrix();
  S21Matrix res(this->rows_, other.cols_);
  if (this->cols_ != other.rows_) {
    throw(std::range_error("Error!\nCols != Rows"));
  }
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        res.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  this->inCorrectMatrix();
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] *= num;
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator*(double num) const {
  this->inCorrectMatrix();
  S21Matrix Mul(this->rows_, this->cols_);
  Mul = *this;
  return Mul *= num;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix Mul(this->rows_, other.cols_);
  Mul = *this;
  return Mul *= other;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  this->inCorrectMatrix();
  other.inCorrectMatrix();
  return this->EqMatrix(other);
}

double& S21Matrix::operator()(int i, int j) {
  this->inCorrectMatrix();
  if (i > this->rows_ || j > this->cols_ || i < 0 || j < 0) {
    throw(std::out_of_range("Matrix index out of bounds"));
  }
  return this->matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
  this->inCorrectMatrix();
  if (i > this->rows_ || j > this->cols_ || i < 0 || j < 0) {
    throw(std::out_of_range("Matrix index out of bounds"));
  }
  return this->matrix_[i][j];
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          return false;
        } else {
          continue;
        }
      }
    }
    return true;
  }
  return false;
}

void S21Matrix::SumMatrix(const S21Matrix& other) { *this += other; }

void S21Matrix::SubMatrix(const S21Matrix& other) { *this -= (other); }

void S21Matrix::MulNumber(const double num) { *this *= num; }

void S21Matrix::MulMatrix(const S21Matrix& other) { *this *= other; }

S21Matrix S21Matrix::Transpose() const {
  this->inCorrectMatrix();
  S21Matrix transpose(this->rows_, this->cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      transpose.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return transpose;
}

S21Matrix S21Matrix::CalcComplements() const {
  this->inCorrectMatrix();
  if (this->cols_ != this->rows_) {
    throw(std::range_error("Error!\nMatrices not square"));
  }
  S21Matrix res(this->rows_, this->cols_);

  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      double result = 0.0;
      S21Matrix* M = new S21Matrix(this->rows_ - 1, this->cols_ - 1);
      minor(i + 1, j + 1, this, M);
      result = M->Determinant();
      res.matrix_[i][j] = pow((-1), i + j) * result;
      M->~S21Matrix();
      delete M;
      M = nullptr;
    }
  }
  return res;
}

void S21Matrix::minor(int row, int cols, const S21Matrix* other, S21Matrix* M) {
  if (other->matrix_ != NULL) {
    int k = 0;
    int z = 0;

    for (int i = 0; i < other->rows_; ++i) {
      k = i;
      if (k > row - 1) {
        k--;
      }

      for (int j = 0; j < other->cols_; ++j) {
        z = j;
        if (z > cols - 1) {
          z--;
        }

        if (i != (row - 1) && j != (cols - 1)) {
          M->matrix_[k][z] = other->matrix_[i][j];
        }
      }
    }
  }
}

double S21Matrix::Determinant() const {
  this->inCorrectMatrix();
  if (this->rows_ != this->cols_) {
    throw(std::range_error("Error!\nMatrix is not square"));
  }
  double res = 0;
  res = this->matrix_[0][0];
  if (this->rows_ > 1) {
    res = S21Matrix::Help(this);
  }
  return res;
}

double S21Matrix::Help(const S21Matrix* other) {
  double res = 0.0;

  if (other->rows_ == 2 && other->cols_ == 2) {
    res = other->matrix_[0][0] * other->matrix_[1][1] -
          other->matrix_[0][1] * other->matrix_[1][0];
  } else {
    for (int i = 0; i < other->rows_; ++i) {
      S21Matrix* M = NULL;
      M = new S21Matrix(other->rows_ - 1, other->cols_ - 1);
      S21Matrix::minor(1, i + 1, other, M);
      res += pow((-1), i) * other->matrix_[0][i] * S21Matrix::Help(M);
      M->~S21Matrix();
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  this->inCorrectMatrix();
  double det = 0;

  det = this->Determinant();
  if (det == 0.0) {
    throw(std::range_error("Error!\nDeterminant is 0"));
  }
  S21Matrix res = this->CalcComplements();
  res = res.Transpose();
  res.MulNumber((1.0 / det));
  return res;
}

void S21Matrix::inCorrectMatrix() const {
  if (this->matrix_ == nullptr || this->rows_ <= 0 || this->cols_ <= 0) {
    throw(std::range_error("Error!\nIncorrect matrix"));
  }
}

int S21Matrix::GetRows() const { return (this->rows_); }

int S21Matrix::GetCols() const { return (this->cols_); }

void S21Matrix::SetRows(int new_rows) {
  S21Matrix res(new_rows, cols_);
  int count = 0;
  if (rows_ > new_rows) {
    count = new_rows;
  } else if (rows_ < new_rows) {
    count = rows_;
  }
  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < cols_; ++j) {
      res.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = res;
}

void S21Matrix::SetCols(int new_cols) {
  S21Matrix res(rows_, new_cols);
  int count = 0;
  if (cols_ > new_cols) {
    count = new_cols;
  } else if (cols_ < new_cols) {
    count = cols_;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < count; ++j) {
      res.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = res;
}

void S21Matrix::newMemory() {
  rows_ = fabs(rows_);
  cols_ = fabs(cols_);
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}
