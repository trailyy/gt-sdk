#pragma once
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <vector>
#include <aclapi.h>

#define print(...) g_utils->fancy_log(__VA_ARGS__)
#define log(...) g_utils->game_log(__VA_ARGS__)

class c_utils
{
public:
    void attach_console();
    void detach_console();
    bool is_console_attached();

    void unprotect_process();
    void erase_pe_header();

    void fancy_log(const char* message, ...)
    {
        va_list va;
        va_start(va, message);  
        printf("[ sdk ] " );
        vprintf(message, va);
        printf("\n");

        va_end(va);
    }

    void game_log(const char* message, ...)
    {
        va_list va;
        va_start(va, message);  
        printf("[ log ] " );
        vprintf(message, va);
        printf("\n");

        va_end(va);
    }

    std::string format(const char* format, ...)
    {
        char buffer[1024];

        va_list va;
        va_start(va, format);

        vsnprintf(buffer, sizeof(buffer), format, va);

        va_end(va);

        return std::string(buffer);
    }

    std::string to_multibyte(wchar_t* buffer)
    {
        auto wstring = std::wstring(buffer);

        if (wstring.empty())
            return "";

        return std::string(wstring.begin(), wstring.end());
    }

    template <typename T, typename... Args>
    T call_vfunc(uint32_t idx, void* thisptr, Args... args)
    {
        using function_t = T(__thiscall***)(void*, Args...);
        auto function = (*static_cast<function_t>(thisptr))[idx];

        return function(pClass, args...);
    }

    template <typename T = void*>
    T get_vfunc(uint32_t idx, void* thisptr)
    {
        void** vtable = *static_cast<void***>(thisptr);
        return reinterpret_cast<T>(vtable[idx]);
    }

    template <typename T>
    inline void read(T& buffer, std::uint8_t*& data)
    {
        buffer = *reinterpret_cast<T*>(data);
        data += sizeof(T);
    }

    template <typename T = std::uint32_t>
    inline void read_string(std::string& buffer, std::uint8_t*& ptr)
    {
        T size = { };
        read<T>(size, ptr);

        buffer = std::string{ reinterpret_cast<char*>(ptr), size };
        ptr += size;
    }

    template <typename T>
    inline void write(T buffer, std::uint8_t*& ptr)
    {
        *reinterpret_cast<T*>(ptr) = buffer;
        ptr += sizeof(T);
    }

    template <typename T = std::uint32_t>
    inline void write_string(const std::string& buffer, std::uint8_t*& ptr)
    {
        write<T>(static_cast<T>(buffer.size()), ptr);

        std::memcpy(ptr, str.data(), buffer.size());
        ptr += buffer.size();
    }

    template <typename T>
    bool write_memory_ex(void* address, T value);
    bool write_memory(void* address, std::string bytes);

    template <typename T>
    T read_memory(uintptr_t address);
};

extern c_utils* g_utils;