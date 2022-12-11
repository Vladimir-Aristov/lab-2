#include <iostream>
#include <initializer_list>
#include <vector>

template<typename T = double>
class Matrix {
private:
    int rows_ = 1;
    int cols_ = 1;
    T* point;
public:
    Matrix(int rows) : rows_(rows) {
        point = new T[rows_];
        for (int i = 0; i < rows_; i++) {
            *(point + i * rows_) = 0;
        }
    }
    Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        point = new T[rows_ * cols_];
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                *(point + i * rows_ + j) = 0;
            }
        }
    }

//    template<typename U>
    Matrix(std::initializer_list<T> lst) {
        cols_ = lst.size();
        point = new T[cols_];
        int i = 0;
        for (auto elem : lst) {
            *(point + i) = elem;
            i++;
        }
    }
//    template<typename U>
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
        this->point = m.point;
    }

    Matrix<T>& operator=(Matrix<T> rhs) {
        this->rows_ = rhs.rows_;
        this->cols_ = rhs.cols_;
        for (int i = 0; i < this->rows_; i++) {
            for (int j = 0; j < this->cols_; j++) {
                this->point + i * rows_ + j = rhs.point + + i * rows_ + j;
            }
        }
    }

    ~Matrix() {delete[] point;}

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
        for (int i = 0; i < m.rows_; i++) {
            for (int j = 0; j < m.cols_; j++) {
                os << *(m.point + i * m.rows_ + j) << " ";
            }
            os << "\n";
        }
        return os;
    }
};

int main() {

    Matrix<int> m1(4);
    std::cout << m1 << "\n";

    Matrix<double> m2(4, 6);
    std::cout << m2 << "\n";
//
    Matrix<int> m5 = { {1, 2, 3}, {4, 5, 6} };
    std::cout << m5 << "\n";

    Matrix<int> m6 = { {1, 2, 3, 4, 5, 6} };
    std::cout << m6 << "\n";

    Matrix<int> m7 = {1, 2, 3, 4, 5, 6};
    std::cout << m7 << "\n";

//    Matrix<int> m8 = { {1}, {2}, {3}, {4}, {5}, {6} };
//    std::cout << m8 << std::endl;

}


