// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include<cassert>


using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    if (s <= 0 || s > MAX_VECTOR_SIZE)
        throw"Vector size should be grater than zero";
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) :sz(v.sz)
  {
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 1;
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] this->pMem;
      this->sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) {
          return *this;
      }
      TDynamicVector tmp(v);
      swap(*this, tmp);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return *this;
  }

  size_t size() const 
  { 
      return this->sz; 
  }

  // индексация
  T& operator[](size_t ind)
  {
      return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind > sz)
          throw out_of_range ("Invalid index");
      return this->pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind > sz)
          throw out_of_range ("Invalid index");
      return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz)
          return 0;
      for (size_t i = 0; i < v.sz; i++) {
          if (this->pMem[i] != v.pMem[i])
              return 0;
      }

      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);

      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = this->pMem[i] + val;
      }

      return tmp;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector tmp(sz);

      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = this->pMem[i] - val;
      }

      return tmp;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(sz);

      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = this->pMem[i] * val;
      }

      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw domain_error ("Objects have different size");
      }

      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = this->pMem[i] + v.pMem[i];
      }

      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw domain_error ("Objects have different size");
      }

      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = this->pMem[i] - v.pMem[i];
      }

      return tmp;
  }
  T operator*(const TDynamicVector& v))
  {
      if (sz != v.sz)
          throw domain_error ("Vectors are different in size");
      T tmp = 0;
      for (size_t i = 0; i < sz; i++) {
          tmp += pMem[i] * v.pMem[i];
      }
      return tmp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s <= 0 || s > MAX_MATRIX_SIZE)
          throw length_error ("Invalid index");
      for (size_t i = 0; i < sz; i++)
          this->pMem[i] = TDynamicVector<T>(sz);

  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  T& at(size_t a, size_t b)
  {
      if (a < 0 || a >= sz || b < 0 || b >= sz)
          throw out_of_range ("Index out of range");
      return pMem[a].at(b);
  }
  const T& at(size_t a, size_t b) const
  {
      if (a < 0 || a >= sz || b < 0 || b >= sz)
          throw out_of_range ("Index out of range");
      return pMem[a].at(b);
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz)
          return 0;
      for (size_t i = 0; i < m.sz; i++) {
          if (this->pMem[i] != m.pMem[i])
              return 0;
      }

      return 1;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      TDynamicVector<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = this->pMem[i] * val;
      }

      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = this->pMem[i] * v.pMem[i];
      }

      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz)
          throw domain_error ("Matrices have different size");
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              tmp.pMem[i][j] = this->pMem[i][j] + m.pMem[i][j];

      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz)
          throw domain_error("Matrices have different size");

      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              tmp.pMem[i][j] = this->pMem[i][j] - m.pMem[i][j];
          }
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz)
          throw domain_error("Matrices have different size");

      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              for (size_t k = 0; k < sz; k++)
                  tmp.pMem[i][j] = this->pMem[i][k] * m.pMem[k][j];

      return tmp;
  }

  size_t size() const
  {
      return this->sz;
  }


  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
 
      for (int i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << endl;
      return ostr;
  }
};

#endif
