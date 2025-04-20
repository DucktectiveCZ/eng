#ifndef ENG_RESULT_HPP
#define ENG_RESULT_HPP

#include "Panic.hpp"
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>

namespace engine {
struct Error {
    enum ErrorType {
        Unknown = 1,
        Sdl,
        InvalidState,
        InvalidGame,
        Io,
        InvalidFormat,
        UnsupportedPlatform,
        UnknownEnumVariant,
        NotImplemented,
        Lua,
        LuaUnexpectedNil,
        LuaWrongType,
    };

    Error(const ErrorType& et);
    Error(const ErrorType& et, std::string_view msg);

    std::string ToString() const;

    ErrorType Type;
    std::string_view Message;
};

struct Unit { };

template <typename T = Unit>
class [[nodiscard]] Result final {
private:
    std::variant<T, Error> data;

public:
    explicit Result(T data)
        : data(std::move(data))
    {
    }
    template <typename U = T, std::enable_if_t<std::is_same_v<U, Unit>, int> = 0>
    Result()
        : data(Unit{})
    {}

    Result(Error data)
        : data(std::move(data))
    {
    }
    Result(Error::ErrorType errorType)
        : data(std::move(Error(errorType)))
    {
    }

    static Result<T> Ok(T val)
    {
        return Result<T>(std::move(val));
    }
    static Result<T> Err(T val)
    {
        return Result<T>(std::move(val));
    }

    bool IsOk() const
    {
        return std::holds_alternative<T>(data);
    }
    bool IsErr() const
    {
        return !IsOk();
    }
    const T& Unwrap() const
    {
        if (!IsOk()) {
            Panic(fmt::format("Result isn't ok. Err: {}", std::get<Error>(data).ToString()));
            // FIXME: `std::get` could throw or crash if `data` doesn't
            // contain an `Error`
        }
        return std::get<T>(data);
    }
    const Error& UnwrapErr() const
    {
        if (IsOk()) {
            Panic("Result is ok");
        }
        return std::get<Error>(data);
    }
    const T& UnwrapOrDefault(const T& d) const
    {
        if (!IsOk()) {
            return d;
        }
        return std::get<T>(data);
    }
    void Discard() const
    {
        return;
    }
};
}

#endif // !ENG_RESULT_HPP
