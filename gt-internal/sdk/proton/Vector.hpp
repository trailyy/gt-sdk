#pragma once

template <typename T>
class _Vector2
{
public:
	T x, y;

	inline bool operator==(const _Vector2<T>& v) const
	{
		return x == v.x && y == v.y;
	}

	inline bool operator!=(const _Vector2<T>& v) const
	{
		return x != v.x || y != v.y;
	}

	inline _Vector2<T> operator+(const _Vector2<T>& v) const
	{
		return { x + v.x, y + v.y };
	}

	inline _Vector2<T> operator-(const _Vector2<T>& v) const
	{
		return { x - v.x, y - v.y };
	}

	inline _Vector2<T> operator*(const _Vector2<T>& v) const
	{
		return { x * v.x, y * v.y };
	}

	inline _Vector2<T> operator/(const _Vector2<T>& v) const
	{
		return { x / v.x, y / v.y };
	}

	inline void operator+=(const _Vector2<T>& v)
	{
		x += v.x;
		y += v.y;
	}

	inline void operator-=(const _Vector2<T>& v)
	{
		x -= v.x;
		y -= v.y;
	}

	inline void operator*=(const _Vector2<T>& v)
	{
		x *= v.x;
		y *= v.y;
	}

	inline void operator/=(const _Vector2<T>& v)
	{
		x /= v.x;
		y /= v.y;
	}
};

template <typename T>
class _Vector3
{
public:
	T x, y, z;
};

template <typename T>
class _Vector4
{
public:
	T x, y, z, w;
};

using Vector2 = _Vector2<float>;
using Vector = _Vector3<float>;
using Vector4 = _Vector4<float>;