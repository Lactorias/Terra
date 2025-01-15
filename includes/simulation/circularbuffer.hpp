#ifndef CIRCULAR
#define CIRCULAR

#include <array>
#include <cstdint>
#include <vector>

template <typename T>
class CircularBuffer {
public:
    int32_t static const m_capacity = 10;
    CircularBuffer(int32_t capacity) {}

    auto add(const T &object) -> void {
        m_buffer[m_head] = object;
        m_head = (m_head + 1) % m_capacity;
    }

    auto get_buffer() const -> const std::array<T, m_capacity> & {
        return m_buffer;
    }

    auto get_buffer() -> std::array<T, m_capacity> & { return m_buffer; }

private:
    std::array<T, m_capacity> m_buffer;
    int32_t m_head{};
    int32_t m_size{};
};

#endif // CIRCULARBUFFER
