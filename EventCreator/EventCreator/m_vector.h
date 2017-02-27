#pragma once

#include "stdafx.h"

#define PI 3.14159265358979323846f

template <typename T, int N>
struct m_vector;

template <typename T, int N>
bool operator==(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

template <typename T, int N>
bool operator!=(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        if (a[i] == b[i])
            return true;
    return false;
}

template <typename T, int N>
bool operator>(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        if (a[i] <= b[i])
            return false;
    return true;
}

template <typename T, int N>
bool operator<(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        if (a[i] >= b[i])
            return false;
    return true;
}

template <typename T, int N>
bool operator>=(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        if (a[i] < b[i])
            return false;
    return true;
}

template <typename T, int N>
bool operator<=(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        if (a[i] > b[i])
            return false;
    return true;
}

//Arithmetics

template <typename T, int N>
inline m_vector<T, N> operator+(const m_vector<T, N> & a) {
    return a;
}

template <typename T, int N>
m_vector<T, N> operator-(const m_vector<T, N> & a) {
    m_vector<T, N> b;
    for (int i = 0; i < N; i++)
        b[i] = -a[i];
    return b;
}

// +

template <typename T, int N>
m_vector<T, N> operator+(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    return c;
}

template <typename T, int N>
m_vector<T, N> operator+=(m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        a[i] += b[i];
    return a;
}

template <typename T, int N>
m_vector<T, N> operator+(const m_vector<T, N> & a, T b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a[i] + b;
    return c;
}

template <typename T, int N>
m_vector<T, N> operator+(T a, const m_vector<T, N> & b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a + b[i];
    return c;
}

template <typename T, int N>
m_vector<T, N> operator+=(m_vector<T, N> & a, T b) {
    for (int i = 0; i < N; i++)
        a[i] += b;
    return a;
}

// -

template <typename T, int N>
m_vector<T, N> operator-(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a[i] - b[i];
    return c;
}

template <typename T, int N>
m_vector<T, N> operator-=(m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        a[i] -= b[i];
    return a;
}

template <typename T, int N>
m_vector<T, N> operator-(const m_vector<T, N> & a, T b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a[i] - b;
    return c;
}

template <typename T, int N>
m_vector<T, N> operator-(T a, const m_vector<T, N> & b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a - b[i];
    return c;
}

template <typename T, int N>
m_vector<T, N> operator-=(m_vector<T, N> & a, T b) {
    for (int i = 0; i < N; i++)
        a[i] -= b;
    return a;
}

// *

template <typename T, int N>
m_vector<T, N> operator*(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a[i] * b[i];
    return c;
}

template <typename T, int N>
m_vector<T, N> operator*=(m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        a[i] *= b[i];
    return a;
}

template <typename T, int N>
m_vector<T, N> operator*(const m_vector<T, N> & a, T b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a[i] * b;
    return c;
}

template <typename T, int N>
m_vector<T, N> operator*(T a, const m_vector<T, N> & b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a * b[i];
    return c;
}

template <typename T, int N>
m_vector<T, N> operator*=(m_vector<T, N> & a, T b) {
    for (int i = 0; i < N; i++)
        a[i] *= b;
    return a;
}

// /

template <typename T, int N>
m_vector<T, N> operator/(const m_vector<T, N> & a, const m_vector<T, N> & b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a[i] / b[i];
    return c;
}

template <typename T, int N>
m_vector<T, N> operator/=(m_vector<T, N> & a, const m_vector<T, N> & b) {
    for (int i = 0; i < N; i++)
        a[i] /= b[i];
    return a;
}

template <typename T, int N>
m_vector<T, N> operator/(const m_vector<T, N> & a, T b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a[i] / b;
    return c;
}

template <typename T, int N>
m_vector<T, N> operator/(T a, const m_vector<T, N> & b) {
    m_vector<T, N> c;
    for (int i = 0; i < N; i++)
        c[i] = a / b[i];
    return c;
}

template <typename T, int N>
m_vector<T, N> operator/=(m_vector<T, N> & a, T b) {
    for (int i = 0; i < N; i++)
        a[i] /= b;
    return a;
}


template <typename T, int N>
std::ostream & operator<<(std::ostream & s, const m_vector<T, N> & a) {
    s << "[";
    for (int i = 0; i < N - 1; i++)
        s << a[i] << "|";
    s << a[N - 1] << "]";
    return s;
}



template <typename T, int N>
struct m_vector{
public:
    __declspec(property(get = getX, put = setX)) T x;
    __declspec(property(get = getY, put = setY)) T y;
    __declspec(property(get = getZ, put = setZ)) T z;
    __declspec(property(get = getW, put = setW)) T w;

    __declspec(property(get = getX, put = setX)) T s;
    __declspec(property(get = getY, put = setY)) T t;
    __declspec(property(get = getZ, put = setZ)) T u;
    __declspec(property(get = getW, put = setW)) T v;

    __declspec(property(get = getX, put = setX)) T r;
    __declspec(property(get = getY, put = setY)) T g;
    __declspec(property(get = getZ, put = setZ)) T b;
    __declspec(property(get = getW, put = setW)) T a;

    __declspec(property(get = getX, put = setX)) T pitch;
    __declspec(property(get = getY, put = setY)) T yaw;
    __declspec(property(get = getY, put = setY)) T turn;
    __declspec(property(get = getZ, put = setZ)) T roll;

    T data[N];

    inline T getX() const {
        return data[0];
    }
    inline void setX(T a) {
        data[0] = a;
    }
    inline T getY() const {
        return data[1];
    }
    inline void setY(T a) {
        data[1] = a;
    }
    inline T getZ() const {
        return data[2];
    }
    inline void setZ(T a) {
        data[2] = a;
    }
    inline T getW() const {
        return data[3];
    }
    inline void setW(T a) {
        data[3] = a;
    }

    m_vector() {
        for (int i = 0; i < N; i++)
            data[i] = 0;
    }

    m_vector(T k) {
        for (int i = 0; i < N; i++)
            data[i] = k;
    }

    m_vector(T x, T y) : m_vector(){
        setX(x);
        setY(y);
    }

    m_vector(T x, T y, T z) : m_vector() {
        setX(x);
        setY(y);
        setZ(z);
    }

    m_vector(T x, T y, T z, T w) : m_vector() {
        setX(x);
        setY(y);
        setZ(z);
        setW(w);
    }

    template<int M>
    m_vector(m_vector<T, M> a, T t = 0) {
        for (int i = 0; i < N; i++) {
            if (i >= M)
                data[i] = t;
            else
                data[i] = a[i];
        }
    }

    inline T operator[](int i) const {
        return data[i];
    }

    inline T & operator[](int i) {
        return data[i];
    }

    T dot(const m_vector<T, N> & a) const {
        T c = 0;
        for (int i = 0; i < N; i++) {
            c += data[i] * a.data[i];
        }
        return c;
    }

    T lengthSquared() const {
        return dot(*this);
    }

    T length() const {
        return sqrt(lengthSquared());
    }

    m_vector<T, N> normalize() const {
        for (int i = 0; i < N; i++) {
            if (data[i] != 0) {
                return *this / length();
            }
        }
        return m_vector<T, N>(0);
    }

    m_vector<T, N> cross(const m_vector<T, N> & a) const {
        m_vector<T, N> c;
        c.x = y * a.z - z * a.y;
        c.y = z * a.x - x * a.z;
        c.z = x * a.y - y * a.x;
        return c;
    }

    inline m_vector<T, N> vectorTo(const m_vector<T, N> & a) const {
        return a - *this;
    }

    float distanceTo(const m_vector<T, N> & a) const {
        return vectorTo(a).length();
    }
};

template <typename T>
m_vector<T, 2> rotate(m_vector<T, 2> a, double angle) {
    double rad = angle * PI / 180.0f;
    double preCos = cos(rad);
    double preSin = sin(rad);

    return m_vector<T, 2>(a.x * preCos - a.y * preSin, a.x * preSin + a.y * preCos);
}

typedef unsigned int uint;

typedef m_vector<float, 2> vec2;
typedef m_vector<float, 3> vec3;
typedef m_vector<float, 4> vec4;

typedef m_vector<int, 2> ivec2;
typedef m_vector<int, 3> ivec3;
typedef m_vector<int, 4> ivec4;

typedef m_vector<uint, 2> uvec2;
typedef m_vector<uint, 3> uvec3;
typedef m_vector<uint, 4> uvec4;
