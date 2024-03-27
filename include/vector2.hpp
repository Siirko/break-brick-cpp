#pragma once
#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>

template <class Num_T> class Vector2
{
  private:
    inline float DEG2RAD(float deg) const { return deg * M_PI / 180.f; }
    inline float RAD2DEG(float rad) const { return rad * 180.f / M_PI; }

  public:
    Vector2();
    Vector2(Num_T x, Num_T y);
    Vector2(const Vector2 &other);
    Vector2(Num_T value);
    ~Vector2() {}

  public:
    Vector2 operator+(const Vector2 &rhs) const;
    Vector2 operator-(const Vector2 &rhs) const;
    Vector2 operator*(Num_T value) const;
    float operator*(const Vector2 &rhs) const;

    Vector2 &operator+=(const Vector2 &rhs);
    Vector2 &operator-=(const Vector2 &rhs);
    Vector2 &operator*=(Num_T value);

    bool operator==(const Vector2 &rhs) const;
    bool operator!=(const Vector2 &rhs) const;

    operator Vector2<int32_t>() const;
    operator Vector2<uint32_t>() const;
    operator Vector2<float>() const;
    operator Vector2<float *>() const;

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &v)
    {
        os << "Vector2(" << v.x << ", " << v.y << ")";
        return os;
    }

  public:
    Vector2 rotate(float angle) const;
    void rotateIp(float angle);

    float angleTo(const Vector2 &other) const;
    float angleTo(Num_T x, Num_T y) const;

    Vector2<float> normalize() const;
    void normalizeIp();

    float dot(const Vector2 &other) const;
    float dot(Num_T x, Num_T y) const;

    float distanceTo(const Vector2 &other) const;
    float distanceTo(Num_T x, Num_T y) const;

    float length() const;
    float lengthSquared() const;

  public:
    Num_T x;
    Num_T y;
};

template <class Num_T> Vector2<Num_T>::Vector2()
{
    x = (Num_T)0;
    y = (Num_T)0;
}
template <class Num_T> Vector2<Num_T>::Vector2(Num_T x, Num_T y)
{
    this->x = x;
    this->y = y;
}

template <class Num_T> Vector2<Num_T>::Vector2(const Vector2 &other)
{
    x = (Num_T)other.x;
    y = (Num_T)other.y;
}
template <class Num_T> Vector2<Num_T>::Vector2(Num_T value)
{
    x = value;
    y = value;
}

template <class Num_T> Vector2<Num_T> Vector2<Num_T>::operator+(const Vector2 &rhs) const
{
    return {x + rhs.x, y + rhs.y};
}
template <class Num_T> Vector2<Num_T> Vector2<Num_T>::operator-(const Vector2 &rhs) const
{
    return {x - rhs.x, y - rhs.y};
}
template <class Num_T> Vector2<Num_T> Vector2<Num_T>::operator*(Num_T value) const { return {x * value, y * value}; }
template <class Num_T> float Vector2<Num_T>::operator*(const Vector2 &rhs) const { return x * rhs.x + y * rhs.y; }

template <class Num_T> Vector2<Num_T> &Vector2<Num_T>::operator+=(const Vector2 &rhs) { return *this = *this + rhs; }
template <class Num_T> Vector2<Num_T> &Vector2<Num_T>::operator-=(const Vector2 &rhs) { return *this = *this - rhs; }
template <class Num_T> Vector2<Num_T> &Vector2<Num_T>::operator*=(Num_T value) { return *this = *this * value; }

template <class Num_T> bool Vector2<Num_T>::operator==(const Vector2<Num_T> &rhs) const
{
    return x == rhs.x && y == rhs.y;
}
template <class Num_T> bool Vector2<Num_T>::operator!=(const Vector2<Num_T> &rhs) const { return !(*this == rhs); }
template <class Num_T> Vector2<Num_T>::operator Vector2<int32_t>() const
{
    return {static_cast<int32_t>(this->x), static_cast<int32_t>(this->y)};
}
template <class Num_T> Vector2<Num_T>::operator Vector2<uint32_t>() const
{
    return {static_cast<uint32_t>(this->x), static_cast<uint32_t>(this->y)};
}
// template <class Num_T> Vector2<Num_T>::operator Vector2<float>() const
// {
//     return {static_cast<float>(this->x), static_cast<float>(this->y)};
// }

// template <class Num_T> Vector2<Num_T>::operator Vector2<float *>() const { return {&x, &y}; }

template <class Num_T> Vector2<Num_T> Vector2<Num_T>::rotate(float angle) const
{
    angle = fmod(angle, 360.f);
    angle = DEG2RAD(angle);
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);

    float tmpX = (cosAngle * x - sinAngle * y);
    float tmpY = (sinAngle * x + cosAngle * y);
    return Vector2<Num_T>(tmpX, tmpY);
}
template <class Num_T> void Vector2<Num_T>::rotateIp(float angle)
{
    Vector2<float> newV = rotate(angle);
    x = newV.x;
    y = newV.y;
}

template <class Num_T> float Vector2<Num_T>::angleTo(const Vector2 &other) const { return angleTo(other.x, other.y); }
template <class Num_T> float Vector2<Num_T>::angleTo(Num_T x, Num_T y) const
{
    auto v = RAD2DEG(atan2(std::abs(y - this->y), std::abs(x - this->x)));
    return v;
}

template <class Num_T> Vector2<float> Vector2<Num_T>::normalize() const
{
    float s = length();
    if (s == 0.f)
    {
        return {0.f, 0.f};
    }
    return {x / s, y / s};
}
template <class Num_T> void Vector2<Num_T>::normalizeIp()
{
    Vector2<float> newV = normalize();
    x = newV.x;
    y = newV.y;
}

template <class Num_T> float Vector2<Num_T>::dot(const Vector2 &other) const { return dot(other.x, other.y); }
template <class Num_T> float Vector2<Num_T>::dot(Num_T x, Num_T y) const { return (this->x * x) + (this->y * y); }

template <class Num_T> float Vector2<Num_T>::distanceTo(const Vector2 &other) const
{
    return distanceTo(other.x, other.y);
}
template <class Num_T> float Vector2<Num_T>::distanceTo(Num_T x, Num_T y) const
{
    return sqrtf(powf(this->x - x, 2.0f) + powf(this->y - y, 2.0f));
}

template <class Num_T> float Vector2<Num_T>::length() const { return sqrtf(lengthSquared()); }
template <class Num_T> float Vector2<Num_T>::lengthSquared() const { return x * x + y * y; }

typedef Vector2<int32_t> Vector2i;
typedef Vector2<uint32_t> Vector2u;
typedef Vector2<float> Vector2f;
