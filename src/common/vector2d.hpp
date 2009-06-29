// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __CTRL_VECTOR2D_HPP__
#define __CTRL_VECTOR2D_HPP__

#include <math.h>
#include <ostream>

template<typename T>
class Vector2D
{
public:
	Vector2D() {}
	Vector2D(T x, T y) : x_(x), y_(y) {}
	~Vector2D() {}

	Vector2D(const Vector2D& self) {
		if (this == &self) return;
		this->x_ = self.x_;
		this->y_ = self.y_;
	}

	Vector2D& operator=(const Vector2D& v) {
		this->x_ = v.x_;
		this->y_ = v.y_;
		return *this;
	}

	T getX() const { return x_; }
	void setX(T x) { x_ = x; }

	T getY() const { return y_; }
	void setY(T y) { y_ = y; }

	Vector2D& operator+=(const Vector2D& v) {
		this->x_ += v.x_;
		this->y_ += v.y_;
		return *this;
	}

	Vector2D& operator-=(const Vector2D& v) {
		this->x_ -= v.x_;
		this->y_ -= v.y_;
		return *this;
	}

	Vector2D& operator*=(const Vector2D& v) {
		this->x_ *= v.x_;
		this->y_ *= v.y_;
		return *this;
	}

	Vector2D& operator/=(const Vector2D& v) {
		this->x_ /= v.x_;
		this->y_ /= v.y_;
		return *this;
	}

	template<typename U>
	Vector2D& operator*=(const U& scala) {
		this->x_ *= scala;
		this->y_ *= scala;
		return *this;
	}

	template<typename U>
	Vector2D& operator/=(const U& scala) {
		this->x_ /= scala;
		this->y_ /= scala;
		return *this;
	}

	Vector2D operator-() {
		return Vector2D(-this->x_, -this->y_);
	}

	double length2() {
		return x_ * x_ + y_ * y_;
	}

	double length() {
		return ::sqrt(length2());
	}

	Vector2D norm() {
		Vector2D vec(*this);
		return vec / length();
	}

	double dot(const Vector2D& v) {
		T x = this->x_ * v.x_;
		T y = this->y_ * v.y_;
		return x + y;
	}

private:
	T x_;
	T y_;
};

template<typename T>
Vector2D<T> operator+(const Vector2D<T>& v1, const Vector2D<T>& v2) {
	Vector2D<T> ret(v1);
	return ret += v2;
}

template<typename T>
Vector2D<T> operator-(const Vector2D<T>& v1, const Vector2D<T>& v2) {
	Vector2D<T> ret(v1);
	return ret -= v2;
}

template<typename T>
Vector2D<T> operator*(const Vector2D<T>& v1, const Vector2D<T>& v2) {
	Vector2D<T> ret(v1);
	return ret *= v2;
}

template<typename T>
Vector2D<T> operator/(const Vector2D<T>& v1, const Vector2D<T>& v2) {
	Vector2D<T> ret(v1);
	return ret /= v2;
}

template<typename T>
Vector2D<T> operator*(const Vector2D<T>& v1, T scala) {
	Vector2D<T> ret(v1);
	return ret *= scala;
}

template<typename T>
Vector2D<T> operator/(const Vector2D<T>& v1, T scala) {
	Vector2D<T> ret(v1);
	return ret /= scala;
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const Vector2D<T> v) {
	os << "(" << v.getX() << "," << v.getY() << ")";
	return os;
}

#endif // __CTRL_VECTOR2D_HPP__
