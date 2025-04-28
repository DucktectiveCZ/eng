#ifndef ENG_BINARY_BUFFER_HPP
#define ENG_BINARY_BUFFER_HPP

#include <cstddef>
#include <vector>

namespace engine {

class BinaryBuffer final {
public:
    BinaryBuffer();
    BinaryBuffer(const size_t initialCapacity);
    ~BinaryBuffer() = default;

    void Push(const std::byte value);
    void Insert(const size_t pos, const std::byte value);
    void Remove(const size_t pos);

    void Reserve(const size_t count);

    const std::vector<std::byte>& GetBytes() const;
    std::vector<std::byte>& GetBytes();

private:
    std::vector<std::byte> m_Bytes;
};

}

#endif // !ENG_BINARY_BUFFER_HPP
