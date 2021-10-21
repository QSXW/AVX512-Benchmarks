#pragma once

#include <cstdint>
#include <new>

#if defined( _MSC_VER )
#   define SLALIGN(x) __declspec(align(x))
#	define SLALIGN_STRUCT(x) struct __declspec(align(x))
#	define SLALIGN_CLASS(x) class __declspec(align(x)))
#   define SL_ASSEMBLY __asm

#   define sl_disable_optimizations optimize("", off)
#   define sl_enable_optimizations  optimize("", on)

#pragma warning(disable: 4996)

#elif defined( __GNUC__ )
#   define SLALIGN(x) __attribute__((aligned(x)))
#	define SLALIGN_STRUCT(x) struct __attribute__((aligned(x)))
#	define SLALIGN_CLASS(x) class __attribute__((aligned(x)))
#   define SL_ASSEMBLY __asm__
#endif

namespace sl
{

template <class T, size_t align>
inline T *aligned_malloc(size_t size)
{
	auto ptr = ::_aligned_malloc(size * sizeof(T), align);
	return ptr ? static_cast<T *>(ptr) : throw std::bad_alloc{};
}

inline void aligned_free(void* ptr)
{
	_aligned_free(ptr);
}

#include <cassert>

#define SLASSERT(...) assert(__VA_ARGS__)

#define SLBIND(x) std::bind(&x, this, std::placeholders::_1)

#define SLDEBUG defined( DEBUG) || defined( _DEBUG )

#if defined( WIN32 ) || defined( _WIN32 )
#   define WINDOWS
#   define SLSURFACE "VK_KHR_win32_surface"
#elif defined( __ANDROID__ )
#   define ANDROID
elif defined(__linux__)
#   define LINUX
#elif defined( __APPLE__ ) || defined( __MACH__ )
#   define APPLE
#endif

#ifndef NOEXCEPT
#define NOEXCEPT noexcept
#endif

#ifndef NODISCARD
#define NODISCARD [[nodiscard]]
#endif

#define BIT(x) (1 << (x))

#define U8(str) u8##str

#define SL_ARRAY_LEN(a) sizeof(a) / sizeof((a)[0])

using INT8   = char;
using UINT8  = unsigned char;
using INT16  = short;
using UINT16 = unsigned short;
using INT32  = int;
using UINT32 = unsigned int;
using INT64  = int64_t;
using UINT64 = uint64_t;

template <class T>
inline constexpr void *CleanUpObject(T *ptr, int value = 0, size_t size = sizeof(T))
{
    return memset(ptr, value, size);
}

}
