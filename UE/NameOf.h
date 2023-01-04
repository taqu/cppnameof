#pragma once
#include "CoreMinimal.h"
#include <type_traits>
#include <utility>
#include <string_view>
#include <array>

namespace cppnameof
{
#define NAMEOF_API ENUMNAME_API

#if 201703L <= __cplusplus || 1914<=_MSC_VER
#    define CPPNAMEOF_ENABLED (1)
using nameof_enum_enabled = std::true_type;
#    ifndef CPPNAMEOF_ENUM_MIN
#        define CPPNAMEOF_ENUM_MIN (0)
#    endif

#    ifndef CPPNAMEOF_ENUM_MAX
#        define CPPNAMEOF_ENUM_MAX (255)
#    endif

#    ifndef CPPNAMEOF_BUFFER_SIZE
#        define CPPNAMEOF_BUFFER_SIZE (64)
#    endif
#else
#    ifndef CPPNAMEOF_ENABLED
#        undef CPPNAMEOF_ENABLED
#    endif
#    define CPPNAMEOF_ENABLED (0)

#    ifndef CPPNAMEOF_BUFFER_SIZE
#        undef CPPNAMEOF_BUFFER_SIZE
#    endif
#    define CPPNAMEOF_BUFFER_SIZE (0)

using nameof_enum_enabled = std::false_type;
#endif

using string_viewascii = std::string_view;

constexpr bool is_num(char c) noexcept
{
    switch(c){
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return true;
    default:
        return false;
    }
}

template <class T, T t>
constexpr auto enum_name() noexcept
{
    static_assert(std::is_enum_v<T>, "T should be enum type.");
    if constexpr(nameof_enum_enabled::value) {
#if defined(__clang__)
        constexpr string_viewascii name = string_viewascii{ __PRETTY_FUNCTION__ };
        constexpr auto begin = name.rfind('=') + 2;
        if constexpr(string_viewascii::npos == begin){
            return string_viewascii{};
        }
        constexpr auto end = name.find(']', begin);
        if constexpr(string_viewascii::npos == end){
            return string_viewascii{};
        }
        constexpr auto length = end-begin;
        if constexpr(length<=0){
            return string_viewascii{};
        }
        if constexpr('-' == name[begin]){
            return string_viewascii{};
        }
        if constexpr(is_num(name[begin])){
            return string_viewascii{};
        }
        return string_viewascii(&name[0]+begin, length);
#elif defined(__GNUC__)
        constexpr string_viewascii name = string_viewascii{ __PRETTY_FUNCTION__ };
        constexpr auto begin = name.rfind('=') + 2;
        if constexpr(string_viewascii::npos == begin){
            return string_viewascii{};
        }
        constexpr auto end = name.find(']', begin);
        if constexpr(string_viewascii::npos == end){
            return string_viewascii{};
        }
        constexpr auto length = end-begin;
        if constexpr(length<=0){
            return string_viewascii{};
        }
        if constexpr('(' == name[begin]){
            return string_viewascii{};
        }
        return string_viewascii(&name[0]+begin, length);
#elif defined(_MSC_VER)
        constexpr string_viewascii name = string_viewascii{ __FUNCSIG__ };
        constexpr auto begin = name.find(',') + 1;
        if constexpr(string_viewascii::npos == begin){
            return string_viewascii{};
        }
        constexpr auto end = name.find('>');
        if constexpr(string_viewascii::npos == end){
            return string_viewascii{};
        }
        constexpr auto length = end-begin;
        if constexpr(length<=0){
            return string_viewascii{};
        }
        if constexpr('(' == name[begin]){
            return string_viewascii{};
        }
        return string_viewascii(&name[0]+begin, length);
#else
        return string_viewascii{};
#endif
    } else {
        return string_viewascii{};
    }
}

//------------------------------------
template<class T, int32_t Min, class I>
struct enum_names;

template<class T, int32_t Min, int32_t ...I>
struct enum_names<T, Min, std::integer_sequence<int32_t, I...>>
{
    static const std::array<string_viewascii, sizeof...(I)> names_;
};

template<class T, int32_t Min, int32_t ...I>
const std::array<string_viewascii, sizeof...(I)> enum_names<T, Min, std::integer_sequence<int32_t, I...>>::names_ =
{
    enum_name<T, static_cast<T>(I+Min)>()...
};

template <class T, int32_t Min=CPPNAMEOF_ENUM_MIN, int32_t Max=CPPNAMEOF_ENUM_MAX>
string_viewascii nameof_enum(T x)
{
    static_assert(std::is_enum_v<T>, "T should be enum type.");
    static_assert((Min<=Max), "Min should be less than or equal to Max");
    static const auto& names = cppnameof::enum_names<T, Min, std::make_integer_sequence<int32_t, Max-Min+1>>::names_;
    return names[static_cast<int32_t>(x)-Min];
}

template<class T>
const T* to_utf8(int32_t size, const char* str);

template<>
NAMEOF_API const char* to_utf8<char>(int32_t size, const char* str);

template<>
NAMEOF_API const char16_t* to_utf8<char16_t>(int32_t size, const char* str);

template<>
NAMEOF_API const char32_t* to_utf8<char32_t>(int32_t size, const char* str);

template<>
NAMEOF_API const wchar_t* to_utf8<wchar_t>(int32_t size, const char* str);

template <class T, int32_t Min=CPPNAMEOF_ENUM_MIN, int32_t Max=CPPNAMEOF_ENUM_MAX>
const TCHAR* NAMEOF_ENUM_TCHAR(T x)
{
    string_viewascii view = nameof_enum<T, Min, Max>(x);
    return to_utf8<TCHAR>(view.length(), view.data());
}

} // namespace cppnameof

