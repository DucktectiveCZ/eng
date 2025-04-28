#include "Vector2.hpp"

#include <string>

#include <fmt/format.h>

namespace engine {

Vector2::Vector2() : X(0), Y(0) {}

Vector2::Vector2(unsigned int X, unsigned int Y) : X(X), Y(Y) {}

std::string Vector2::ToString() const {
    return fmt::format("({}, {})", X, Y);
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(X + other.X, Y + other.Y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(X - other.X, Y - other.Y);
}

Vector2 Vector2::operator*(const Vector2& other) const {
    return Vector2(X * other.X, Y * other.Y);
}

Vector2 Vector2::operator/(const Vector2& other) const {
    return Vector2(X / other.X, Y / other.Y);
}

Vector2 Vector2::operator%(const Vector2& other) const {
    return Vector2(X % other.X, Y % other.Y);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    X += other.X;
    Y += other.Y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    X -= other.X;
    Y -= other.Y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& other) {
    X *= other.X;
    Y *= other.Y;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2& other) {
    X /= other.X;
    Y /= other.Y;
    return *this;
}

Vector2& Vector2::operator%=(const Vector2& other) {
    X %= other.X;
    Y %= other.Y;
    return *this;
}

bool Vector2::operator==(const Vector2& other) const {
    return X == other.X && Y == other.Y;
}

bool Vector2::operator!=(const Vector2& other) const {
    return !(*this == other);
}

std::strong_ordering Vector2::operator<=>(const Vector2& other) const {
    if (auto cmp = X <=> other.X; cmp != 0) return cmp;
    return Y <=> other.Y;
}

bool Vector2::operator<(const Vector2& other) const {
    return (X < other.X) || (X == other.X && Y < other.Y);
}

bool Vector2::operator>(const Vector2& other) const {
    return (X > other.X) || (X == other.X && Y > other.Y);
}

} // namespace engine
