#ifndef ENG_VECTOR2_HPP
#define ENG_VECTOR2_HPP

#include <compare>
#include <string>
namespace engine {

struct Vector2 {
public:
    unsigned int X, Y;

    Vector2();
    Vector2(unsigned int X, unsigned int Y);

    std::string ToString() const;

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(const Vector2& other) const;
    Vector2 operator/(const Vector2& other) const;
    Vector2 operator%(const Vector2& other) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(const Vector2& other);
    Vector2& operator/=(const Vector2& other);
    Vector2& operator%=(const Vector2& other);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;
    std::strong_ordering operator<=>(const Vector2& other) const;
    bool operator<(const Vector2& other) const;
    bool operator>(const Vector2& other) const;
};

}

#endif // !ENG_VECTOR2_HPP
