#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <array>
#define toDeg(rad) (rad * 180.0 / M_PI)
#define toRad(deg) (deg * M_PI / 180)


template <class T, std::size_t N >
class Vector;

template <class T, std::size_t N >
Vector<T, N> operator*(Vector<T, N>& left, const Vector<T, N>& right);
template <class T, std::size_t N >
Vector<T, N> operator*(Vector<T, N>& left, T right);
template <class T, std::size_t N >
Vector<T, N> operator+(Vector<T, N>& left, const Vector<T, N>& right);
template <class T, std::size_t N >
Vector<T, N> operator+(Vector<T, N>& left, T right);
template <class T, std::size_t N >
T operator|(Vector<T, N>& left, const Vector<T, N>& right);//Dot Product

//Start declaration of class.
template <class T, std::size_t N >
class Vector
{
private:
	std::array<T,N> *Values;
public:
	Vector();
	Vector<T, N> &operator=(const Vector<T, N>&);
	T &operator[](const int&);
    T &operator[](const int&)const;
	Vector<T, N> &operator+=(const Vector<T, N>&);
	Vector<T, N> &operator*=(const Vector<T, N>&);
	Vector<T, N> &operator+=(T);
	Vector<T, N> &operator*=(T);

	friend Vector<T, N> operator*<T, N>(Vector<T, N>&, const Vector<T, N>&);
	friend Vector<T, N> operator*<T, N>(Vector<T, N>&, T);
	friend Vector<T, N> operator+<T, N>(Vector<T, N>&, const Vector<T, N>&);
	friend Vector<T, N> operator+<T, N>(Vector<T, N>&, T);
	friend T operator|<T, N>(Vector<T, N>&, const Vector<T, N>&);

	const T getValue(size_t) const;
	void setValue(size_t, const T);
};