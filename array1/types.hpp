#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstddef>
#include <cstdint>

#if defined(SINGLE_PRECISION)
    using real_t = float;
#elif defined(LONG_DOUBLE_PRECISION)
    using real_t = long double;
#else
    using real_t = double;
#endif

namespace types {

    // メインのスカラー型（変更に強いように別名化）
    using real = real_t;
    
    // 固定幅整数型（明示的なビット数指定）
    using int8  = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;
    
    using uint8  = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;
    
    // 添字やサイズ用（標準の size_t を使う）
    using Size = std::size_t;
    using Index = std::size_t;
    
} // namespace types

#endif /* TYPES_HPP */