#include <iostream>
#include <initializer_list>
#include <vector>
using std::cout, std::endl;

template<typename T = double>
class Matrix {
private:
    int rows_ = 1;
    int cols_ = 1;
    T* point = nullptr;
public:
    // task 2
    explicit Matrix(int rows = 1, int cols = 1) : rows_(rows), cols_(cols) {
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

    // task 3
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
    //
    Matrix( Matrix<T>&& rhs) noexcept {
        this->rows_ = rhs.rows_;
        this->cols_ = rhs.cols_;
        delete[] point;

        this->point = rhs.point;

        rhs.point = nullptr;
        rhs.rows_ = 0;
        rhs.cols_ = 0;
    }
    //task 4
    Matrix<T>& operator=(const Matrix<T>& rhs) {
        if (this == &rhs) {
            return *this;
        }
        this->rows_ = rhs.rows_;
        this->cols_ = rhs.cols_;
        delete[] point;

        point = new T[rows_ * cols_];
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                 point[i * rows_ + j] = rhs.point[i * rows_ + j];
            }
        }
        return *this;
    }
    // task 5
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
    // task 6
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
    // task 7
    T& operator()(int i, int j) {
        if (i >= rows_ || j >= cols_) {
            throw std::invalid_argument("index out of range\n");
        }
        return *(point + i * rows_ + j);
    }
    const T& operator()(int i, int j) const {
        if (i >= rows_ || j >= cols_) {
            throw std::invalid_argument("index out of range\n");
        }
        return *(point + i * rows_ + j);
    }
    // task 8
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
                for (int k = 0; k < lhs.cols_; k++) {
                    tmp(i, j) += lhs(i, k) * rhs(k, j);
                }
            }
        }
        return tmp;
    }

    friend Matrix<T> operator*(T num, Matrix<T> m) {
        m *= num;
        return m;
    }

    friend Matrix<T> operator*(Matrix<T> m, T num) {
        m *= num;
        return m;
    }

    // task 9
    Matrix<T> operator+=(const Matrix<T>& rhs) {
        if (this->rows_ != rhs.rows_ or this->cols_ != rhs.cols_) {
            throw std::invalid_argument("problems with linear algebra..");
        }
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                *(point + i * rows_ + j) += *(rhs.point + i * rows_ + j);
            }
        }
        return *this;
    }

    Matrix<T> operator-=(const Matrix<T>& rhs) {
        if (this->rows_ != rhs.rows_ or this->cols_ != rhs.cols_) {
            throw std::invalid_argument("problems with linear algebra..");
        }
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                *(point + i * rows_ + j) -= *(rhs.point + i * rows_ + j);
            }
        }
        return *this;
    }

    Matrix<T>& operator*=(T num) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                *(point + i * rows_ + j) *= num;
            }
        }
        return *this;
    }
};

int main() {
    cout << "column: " << endl;
    Matrix<int> m1(2);
    std::cout << m1 << endl;

    cout << "2-D empty matrix:" << endl;
    Matrix<double> m2(4, 6);
    std::cout << m2 << endl;

    cout << "2-D matrix" << endl;
    Matrix<int> m5 = { {1, 2, 3}, {4, 5, 6} };
    std::cout << m5 << endl;

    cout << "2 string matrices: " << endl;
    Matrix<int> m6 = { {1, 2, 3, 4, 5, 6} };
    std::cout << m6 << "\n";

    Matrix<double> m7 = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    std::cout << m7 << "\n";

    std::initializer_list<std::initializer_list<int>> list = { {1}, {2}, {3}, {4}, {5}, {6} };
    cout << "column matrix: " << endl;
    Matrix<int> m8 = list;
    std::cout << m8 << std::endl;

    cout << "copy operator: " << endl;
    Matrix<int> m3(m1);
    cout << m1 << endl;

    cout << "assign operator: " << endl;
    m1 = m6;
    cout << m1 << endl;

    cout << "move operator:" << endl;
    Matrix<double> m4(std::move(m2));
    cout << "new matrix: " << endl;
    cout << m4 << endl;
    cout << "initial matrix: " << endl;
    cout << m2 << endl;

    cout << "operator():" << endl;
    Matrix<int> m = {{1, 2, 4}, {4, 5, 6}};
    cout << "0, 2 coordinates value: " << m(0, 2) << endl;
    m(0, 1) = 7;
    cout << m << endl;

    cout << "multiplying matrix on number" << endl;
    cout << m7 * 3 << endl;
    cout << 3 * m7 << endl;

    cout << "summarizing matrices: " << endl;
    Matrix<int> m10 = {1, 2, 3, 4, 5, 6};
    Matrix<int> m11 = {1, 2, 3, 4, 5, 6};
    try {
        cout << m10 + m11 << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    cout << "subtracting matrices: " << endl;
    try {
        cout << m10 - m11 << endl;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    cout << "multiplying matrices: " << endl;
    cout << "first (and 2nd) matrix: " << endl;
    Matrix<int> m20 = {{1, 1},
                       {2, 2}};
    cout << m20 << endl;
    Matrix<int> m21 = {{1, 1},
                       {2, 2}};

    try {
        cout << "result" << endl << m20 * m21;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }
}