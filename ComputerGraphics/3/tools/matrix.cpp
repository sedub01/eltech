#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

#include "../include/matrix.h"

using std::to_string;

template <typename T>
Matrix<T>::Matrix(size_t n_row, size_t m_column): n(n_row), m(m_column)
{
    a = (T**)malloc(n*sizeof(T*));

    for(size_t i = 0; i < n; ++i)
        a[i] = (T*)malloc(m*sizeof(T));

    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < m; ++j)
            a[i][j] = 0;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& clonner) : n(clonner.n), m(clonner.m)
{
    a = (T**)malloc(n*sizeof(T*));

    for(size_t i = 0; i < n; ++i)
        a[i] = (T*)malloc(m*sizeof(T));

    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < m; ++j)
            a[i][j] = clonner.a[i][j];
}

template<typename T>
Matrix<T>::~Matrix()
{
    for(size_t i = 0; i < n; ++i)
        free(a[i]);
    free(a);
}

template<typename T>
T Matrix<T>::get(size_t i, size_t j)
{
    if(/*i < 0 || */i >= n)
        throw printOutOfBound("i", i);
    if(/*j < 0 || */j >= m)
        throw printOutOfBound("j", j);
    return a[i][j];
}

template<typename T>
void Matrix<T>::set(T value, size_t i, size_t j)
{
    if(/*i < 0 || */i >= n)
        throw printOutOfBound("i", i);
    if(/*j < 0 || */j >= m)
        throw printOutOfBound("j", j);
    a[i][j] = value;
}

template<typename T>
Matrix<T> Matrix<T>::multiply(const Matrix& one, const Matrix& two)
{
    if(one.m != two.n)
        throw "Matrix is not multiplable (one.m_column = " + to_string(one.m) + ", two.n_row = " + to_string(two.n) + "). ";

    /*n1xm1 * n2xm2 -> n1xm2*/
    Matrix<T> res(one.n, two.m);

    for(size_t res_i = 0; res_i < res.n; ++res_i)
        for(size_t res_j = 0; res_j < res.m; ++res_j)
        {
            T buff = 0;
            for(size_t other_i = 0; other_i < one.m; ++other_i)
                buff += one.a[res_i][other_i] * two.a[other_i][res_j];
            res.a[res_i][res_j] = buff;
        }
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::multiply(const Matrix& other) const
{
    return Matrix<T>::multiply(*this, other);
}

template<typename T>
Matrix<T> Matrix<T>::add(const Matrix& one, const Matrix& two)
{
    if(!(one.n == two.n && one.m == two.m))
        throw "Matrix is not addeble. Its size different. ";

    /*n1xm1 * n2xm2 -> n1xm2*/
    Matrix<T> res(one.n, two.m);

    for(size_t i = 0; i < res.n; ++i)
        for(size_t j = 0; j < res.m; ++j)
            res.a[i][j] = one.a[i][j] + two.a[i][j];
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::add(const Matrix& other) const
{
    return Matrix<T>::add(*this, other);
}

template<typename T>
string Matrix<T>::toString()
{
    std::ostringstream res;
    for(size_t i = 0; i < n; ++i)
    {
        if(i == 0)
            res << "";
        for(size_t j = 0; j < m; ++j)
        {
            res << std::setw(5) << a[i][j];
            if(i == n-1)
            {
                if(j != m-1)
                    res << ", ";
            }
            else
                res << ", ";
        }
        if(i == n-1)
            res << "";
        else
            res << "\n";
    }
    return res.str();
}

template<typename T>
string Matrix<T>::str()
{
    return toString();
}

/*template<class T>
ostream& operator<< (ostream &out, const Matrix<T> &ma)
{
    out << ma.toString();
    return out;
}*/

template<typename T>
string Matrix<T>::printOutOfBound(string ij, size_t ij_val)
{
    return "Out of bounds: n_row = " + to_string(n) + ", m_column = " + to_string(m) + ", and " + ij + " = " + to_string(ij_val) + ". ";
}

template<typename T>
Matrix<T> Matrix<T>::inverse() const
{
    if(this->n != this->m)
        throw "The matrix must be square: n=" + std::to_string(this->n) + ", " + std::to_string(this->m) + ". ";
    Matrix<T> res(*this);
    bool check = matrix_inverse(this->a, res.a, this->n);
    if(check == false)
        throw "Cannot inverse this matrix. ";
    return res;
}

// Функция, производящая обращение матрицы.
// Принимает:
//     matrix - матрица для обращения
//     result - матрица достаточного размера для вмещения результата
//     size   - размерность матрицы
// Возвращает:
//     true в случае успешного обращения, false в противном случае
bool matrix_inverse(double **matrix, double **result, const int size)
{   
    // Изначально результирующая матрица является единичной
    // Заполняем единичную матрицу
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
            result[i][j] = 0.0;
        
        result[i][i] = 1.0;
    }
    
    // Копия исходной матрицы
    double **copy = new double *[size]();
    
    // Заполняем копию исходной матрицы
    for (int i = 0; i < size; ++i)
    {
        copy[i] = new double [size];
        
        for (int j = 0; j < size; ++j)
            copy[i][j] = matrix[i][j];
    }
    
    // Проходим по строкам матрицы (назовём их исходными)
    // сверху вниз. На данном этапе происходит прямой ход
    // и исходная матрица превращается в верхнюю треугольную
    for (int k = 0; k < size; ++k)
    {
        // Если элемент на главной диагонали в исходной
        // строке - нуль, то ищем строку, где элемент
        // того же столбца не нулевой, и меняем строки
        // местами
        if (fabs(copy[k][k]) < 1e-8)
        {
            // Ключ, говорязий о том, что был произведён обмен строк
            bool changed = false;
            
            // Идём по строкам, расположенным ниже исходной
            for (int i = k + 1; i < size; ++i)
            {
                // Если нашли строку, где в том же столбце
                // имеется ненулевой элемент
                if (fabs(copy[i][k]) > 1e-8)
                {
                    // Меняем найденную и исходную строки местами
                    // как в исходной матрице, так и в единичной
                    std::swap(copy[k],   copy[i]);
                    std::swap(result[k], result[i]);
                    
                    // Взводим ключ - сообщаем о произведённом обмене строк
                    changed = true;
                    
                    break;
                }
            }
            
            // Если обмен строк произведён не был - матрица не может быть
            // обращена
            if (!changed)
            {
                // Чистим память
                for (int i = 0; i < size; ++i)
                    delete [] copy[i];
                
                delete [] copy;
                
                // Сообщаем о неудаче обращения
                return false;
            }
        }
        
        // Запоминаем делитель - диагональный элемент
        double div = copy[k][k];
        
        // Все элементы исходной строки делим на диагональный
        // элемент как в исходной матрице, так и в единичной
        for (int j = 0; j < size; ++j)
        {
            copy[k][j]   /= div;
            result[k][j] /= div;
        }
        
        // Идём по строкам, которые расположены ниже исходной
        for (int i = k + 1; i < size; ++i)
        {
            // Запоминаем множитель - элемент очередной строки,
            // расположенный под диагональным элементом исходной
            // строки
            double multi = copy[i][k];
            
            // Отнимаем от очередной строки исходную, умноженную
            // на сохранённый ранее множитель как в исходной,
            // так и в единичной матрице
            for (int j = 0; j < size; ++j)
            {
                copy[i][j]   -= multi * copy[k][j];
                result[i][j] -= multi * result[k][j];
            }
        }
    }
    
    // Проходим по вернхней треугольной матрице, полученной
    // на прямом ходе, снизу вверх
    // На данном этапе происходит обратный ход, и из исходной
    // матрицы окончательно формируется единичная, а из единичной -
    // обратная
    for (int k = size - 1; k > 0; --k)
    {
        // Идём по строкам, которые расположены выше исходной
        for (int i = k - 1; i + 1 > 0; --i)
        {
            // Запоминаем множитель - элемент очередной строки,
            // расположенный над диагональным элементом исходной
            // строки
            double multi = copy[i][k];
            
            // Отнимаем от очередной строки исходную, умноженную
            // на сохранённый ранее множитель как в исходной,
            // так и в единичной матрице
            for (int j = 0; j < size; ++j)
            {
                copy[i][j]   -= multi * copy[k][j];
                result[i][j] -= multi * result[k][j];
            }
        }
    }
    
    // Чистим память
    for (int i = 0; i < size; ++i)
        delete [] copy[i];
    
    delete [] copy;
    
    // Сообщаем об успехе обращения
    return true;
}

// https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function

template class Matrix<double>;
//template class Matrix<int>;
