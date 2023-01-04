#include "NameOf.h"

namespace cppnameof
{
    template<>
    const char* to_utf8<char>(int32_t, const char* str)
    {
        return str;
    }

    template<>
    const char16_t* to_utf8<char16_t>(int32_t size, const char* str)
    {
#if UE_BUILD_SHIPPING
        return u"";
#else
        static char16_t buffer[CPPNAMEOF_BUFFER_SIZE];
        size = FMath::Min(size, CPPNAMEOF_BUFFER_SIZE-1);
        for(int32_t i=0; i<size; ++i){
            buffer[i] = str[i];
        }
        buffer[size] = u'\0';
        return buffer;
#endif
    }

    template<>
    const char32_t* to_utf8<char32_t>(int32 size, const char* str)
    {
#if UE_BUILD_SHIPPING
        return U"";
#else
        static char32_t buffer[CPPNAMEOF_BUFFER_SIZE];
        size = FMath::Min(size, CPPNAMEOF_BUFFER_SIZE-1);
        for(int32_t i=0; i<size; ++i){
            buffer[i] = str[i];
        }
        buffer[size] = U'\0';
        return buffer;
#endif
    }

    template<>
    const wchar_t* to_utf8<wchar_t>(int32 size, const char* str)
    {
#if UE_BUILD_SHIPPING
        return TEXT("");
#else
        static wchar_t buffer[CPPNAMEOF_BUFFER_SIZE];
        size = FMath::Min(size, CPPNAMEOF_BUFFER_SIZE-1);
        for(int32_t i=0; i<size; ++i){
            buffer[i] = str[i];
        }
        buffer[size] = TEXT('\0');
        return buffer;
#endif
    }
}
