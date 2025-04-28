#include "BinaryBuffer.hpp"

#include <cstddef>
#include <iterator>
#include <vector>

namespace engine {

BinaryBuffer::BinaryBuffer()
   : m_Bytes()
{
}
BinaryBuffer::BinaryBuffer(const size_t initialCapacity)
    : m_Bytes()
{
    m_Bytes.reserve(initialCapacity);
}

void BinaryBuffer::Push(const std::byte value)
{
    m_Bytes.push_back(value);
}

void BinaryBuffer::Insert(const size_t pos, const std::byte value)
{
    auto it = std::next(m_Bytes.begin(), pos);
    m_Bytes.insert(it, value);
}

void BinaryBuffer::Remove(const size_t pos)
{
    auto it = std::next(m_Bytes.begin(), pos);
    m_Bytes.erase(it);
}

void BinaryBuffer::Reserve(const size_t count)
{
    m_Bytes.reserve(count);
}

const std::vector<std::byte>& BinaryBuffer::GetBytes() const {
    return m_Bytes;
}

std::vector<std::byte>& BinaryBuffer::GetBytes() {
    return m_Bytes;
}

} // namespace engine
