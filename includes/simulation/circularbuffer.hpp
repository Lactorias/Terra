#ifndef CIRCULAR
#define CIRCULAR

#include <array>
#include <cstddef>
#include <cstdint>

template <typename T, std::size_t capacity>
class CircularBuffer {
public:
    CircularBuffer() {}

    auto add(const T &object) -> void {
        m_buffer[m_head] = object;
        m_head = (m_head + 1) % capacity;
    }

    auto get_buffer() const -> const std::array<T, capacity> & {
        return m_buffer;
    }

    auto get_buffer() -> std::array<T, capacity> & { return m_buffer; }

    [[nodiscard]]
    auto size() const noexcept -> int32_t {
        return m_size;
    }

    auto operator[](size_t index) noexcept -> T & { return m_buffer[index]; }

private:
    std::array<T, capacity> m_buffer;
    size_t m_head{};
    size_t m_size{};
};

#endif // CIRCULARBUFFER
