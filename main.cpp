#include <iostream>
#include <initializer_list>
#include <vector>
using std::cout, std::endl;

template<typename T = double>
class Matrix {
private:
    int rows_ = 1;
    int cols_ = 1;
public:
    T* point = nullptr;
    Matrix(int rows = 1, int cols = 1) : rows_(rows), cols_(cols) {
        point = new T[rows_ * cols_];
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                *(point + i * rows_ + j) = 0;
            }
        }
    }

    Matrix(std::initializer_list<T> lst) {
        cols_ = lst.size();
        point = new T[cols_];
        int i = 0;
        for (auto elem : lst) {
            *(point + i) = elem;
            i++;
        }
    }

    Matrix(std::initializer_list<std::initializer_list<T>> lst) {
        rows_ = lst.size();
        cols_ = (lst.begin())->size();
        point = new T[rows_ * cols_];
        int i = 0;
        int j = 0;
        for (auto list : lst) {
            for (auto elem : list) {
                *(point + i * rows_ + j) = elem;
                j++;
            }
            j = 0;
            i++;
        }
    }


    Matrix(const Matrix<T>& m) {
        this->rows_ = m.rows_;
        this->cols_ = m.cols_;
        point = new T[rows_ * cols_];
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                *(point + i * rows_ + j) = *(m.point + i * rows_ + j);
            }
        }
    }

    Matrix( Matrix<T>&& rhs) {
        this->rows_ = rhs.rows_;
        this->cols_ = rhs.cols_;
        delete[] point;

        this->point = rhs.point;

        rhs.point = nullptr;
        rhs.rows_ = 0;
        rhs.cols_ = 0;
//        return *this;
    }

    Matrix<T>& operator=(const Matrix<T>& rhs) {
        this->rows_ = rhs.rows_;
        this->cols_ = rhs.cols_;
        delete[] point;
        point = new T[rows_ * cols_];
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                *(point + i * rows_ + j) = *(rhs.point + i * rows_ + j);
            }
        }
        return *this;
    }

    Matrix<T>& operator=(Matrix<T>&& rhs)  noexcept{
        if (this == &rhs) {
            return *this;
        }
        this->rows_ = rhs.rows_;
        this->cols_ = rhs.cols_;
        delete[] point;

        this->point = rhs.point;

        rhs.point = nullptr;
        rhs.rows_ = 0;
        rhs.cols_ = 0;
        return *this;
    }

    ~Matrix() {delete[] point;}

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
        if (m.point == nullptr) {
            os << "null matrix" << endl;
        } else {
            for (int i = 0; i < m.rows_; i++) {
                for (int j = 0; j < m.cols_; j++) {
                    os << *(m.point + i * m.rows_ + j) << " ";
                }
                os << "\n";
            }
        }
        return os;
    }

    T& operator()(int i, int j) {
        if (i >= rows_ || j >= cols_) {
            throw std::invalid_argument("index out of range\n");
        }
        return point[i * rows_ + j];
    }
    const T& operator()(int i, int j) const {
        if (i >= rows_ || j >= cols_) {
            throw std::invalid_argument("index out of range\n");
        }
        return point[i * rows_ + j];
    }

    friend Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs) {
        if (lhs.rows_ != rhs.cols_) {
            throw std::invalid_argument("someone didn't learn linear algebra");
        }

        Matrix<T> tmp(lhs.rows_, rhs.cols_);
        for (int i = 0; i < lhs.rows_; i++) {
            for (int j = 0; j < rhs.cols_; j++) {
                
            }
        }
    }


};

int main() {

//    Matrix<int> m1(4);
//    std::cout << m1 << endl;
//
//    Matrix<double> m2(4, 6);
//    std::cout << m2 << endl;
//
    Matrix<int> m5 = { {1, 2, 3}, {4, 5, 6} };
//    std::cout << m5 << endl;
//
//    Matrix<int> m6 = { {1, 2, 3, 4, 5, 6} };
//    std::cout << m6 << "\n";
//
//    Matrix<int> m7 = {1, 2, 3, 4, 5, 6};
//    std::cout << m7 << "\n";
//
//    std::initializer_list<std::initializer_list<int>> list = { {1}, {2}, {3}, {4}, {5}, {6} };
//    Matrix<int> m8 = list;
//    std::cout << m8 << std::endl;

    Matrix<int> m9(std::move(m5));
    cout << m9 << endl;
    cout << m5;
}