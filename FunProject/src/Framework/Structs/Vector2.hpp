#pragma once
#include <string_view>
#include "SDL/SDL_types.h"
#include <atomic>

template<typename T>
struct Vector2 final
{
	T x, y;
	Vector2() noexcept:x(static_cast<T>(0)), y(static_cast<T>(0))
	{}
	Vector2(T X, T Y) noexcept : x(X), y(Y)
	{}
	Vector2(const Vector2<T>& vec) noexcept = default;

	template<typename U>
	explicit Vector2(const Vector2<U>& vec) noexcept: x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y))
	{}

	void operator += (const Vector2<T>& right)
	{
		x += right.x;
		y += right.y;
	}

	void operator -= (const Vector2<T>& right)
	{
		x -= right.x;
		y -= right.y;
	}

	void operator *=(const T& right)
	{
		x *= right;
		y *= right;
	}

	void operator *= (const Vector2<T>& right)
	{
		x *= right.x;
		y *= right.y;
	}

	void operator /= (const T& right)
	{
		x /= right;
		y /= right;
	}

	void operator /= (const Vector2<T>& right)
	{
		x /= right.x;
		y /= right.y;
	}

	template<typename U>
	void operator += (const Vector2<U>& right)
	{
		x += static_cast<T>(right.x);
		y += static_cast<T>(right.y);
	}

	template<typename U>
	void operator -= (const Vector2<U>& right)
	{
		x -= static_cast<T>(right.x);
		y -= static_cast<T>(right.y);
	}
	
	template<typename U>
	void operator *= (const U& right)
	{
		T r = static_cast<T>(right);
		x += r;
		y += r;
	}
	template<typename U>
	void operator *= (const Vector2<U>& right)
	{
		x *= static_cast<T>(right.x);
		y *= static_cast<T>(right.y);
	}

	template<typename U>
	void operator /= (const Vector2<U>& right)
	{
		x /= static_cast<T>(right.x);
		y /= static_cast<T>(right.y);
	}

	template<typename U>
	void operator /= (const U& right)
	{
		T r = static_cast<T>(right);
		x /= r;
		y /= r;
	}	

	template<typename U>
	void operator =(const Vector2<U>& vec)
	{
		x = static_cast<T>(vec.x);
		y = static_cast<T>(vec.y);
	}

	std::string ToString()
	{
		return "x: " + std::to_string(x) + ", y: " + std::to_string(y);
	}
};

typedef Vector2<Uint32> Vector2u;
typedef Vector2<Sint32> Vector2i;
typedef std::atomic<Vector2u> AtomicVec2u;
typedef std::atomic<Vector2i> AtomicVec2i;

template<typename T>
inline static Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template<typename T>
inline static Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x - right.x, left.y - right.y);
}

template<typename T>
inline static Vector2<T> operator *(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x * right.x, left.y * right.y);
}

template<typename T>
inline static Vector2<T> operator *(const Vector2<T>& left, const T& right)
{
	return Vector2<T>(left.x * right, left.y * right);
}

template<typename T>
inline static Vector2<T> operator /(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x / right.x, left.y / right.y);
}

template<typename T>
inline static Vector2<T> operator /(const Vector2<T>& left, const T& right)
{
	return Vector2<T>(left.x / right, left.y / right);
}

template<typename T>
inline static bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
{
	return left.x == right.x && left.y == right.y;
}

template<typename T>
inline static bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
{
	return left.x != right.x || left.y != right.y;
}