/*

Copyright (c) 2016, Project OSRM contributors
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef STRONG_TYPEDEF_HPP
#define STRONG_TYPEDEF_HPP

#include <functional>
#include <iostream>
#include <type_traits>

namespace osrm
{

/* Creates strongly typed wrappers around scalar types.
 * Useful for stopping accidental assignment of lats to lons,
 * etc.  Also clarifies what this random "int" value is
 * being used for.
 */
#define OSRM_STRONG_TYPEDEF(From, To)                                                              \
    class To final                                                                                 \
    {                                                                                              \
        static_assert(std::is_arithmetic<From>(), "");                                             \
        From x;                                                                                    \
        friend std::ostream &operator<<(std::ostream &stream, const To &inst);                     \
                                                                                                   \
      public:                                                                                      \
        To() = default;                                                                            \
        explicit To(const From x_) : x(x_) {}                                                      \
        explicit operator From &() { return x; }                                                   \
        explicit operator From() const { return x; }                                               \
        To operator+(const To rhs_) const { return To(x + static_cast<const From>(rhs_)); }        \
        To operator-(const To rhs_) const { return To(x - static_cast<const From>(rhs_)); }        \
        To operator*(const To rhs_) const { return To(x * static_cast<const From>(rhs_)); }        \
        To operator/(const To rhs_) const { return To(x / static_cast<const From>(rhs_)); }        \
        bool operator<(const To z_) const { return x < static_cast<const From>(z_); }              \
        bool operator>(const To z_) const { return x > static_cast<const From>(z_); }              \
        bool operator<=(const To z_) const { return x <= static_cast<const From>(z_); }            \
        bool operator>=(const To z_) const { return x >= static_cast<const From>(z_); }            \
        bool operator==(const To z_) const { return x == static_cast<const From>(z_); }            \
        bool operator!=(const To z_) const { return x != static_cast<const From>(z_); }            \
    };                                                                                             \
    inline std::ostream &operator<<(std::ostream &stream, const To &inst)                          \
    {                                                                                              \
        return stream << inst.x;                                                                   \
    }

#define OSRM_STRONG_TYPEDEF_HASHABLE(From, To)                                                     \
    namespace std                                                                                  \
    {                                                                                              \
    template <> struct hash<To>                                                                    \
    {                                                                                              \
        std::size_t operator()(const To &k) const                                                  \
        {                                                                                          \
            return std::hash<From>()(static_cast<const From>(k));                                  \
        }                                                                                          \
    };                                                                                             \
    }
}

#endif // OSRM_STRONG_TYPEDEF_HPP
