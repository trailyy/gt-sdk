#pragma once
#include "utils.hpp"

bool console_attached = false;

c_utils* g_utils = new c_utils();

std::vector<uint8_t> string_to_bytes(std::string str)
{
    std::vector<std::uint8_t> bytes;

    char* start = const_cast<char*>(str.data());
    char* end = start + str.size();

    for (char* c = start; c < end; ++c)
        bytes.push_back(static_cast<std::uint8_t>(std::strtoul(c, &c, 16)));

    return bytes;
};

std::vector<uint8_t> pattern_to_bytes(const char* pat)
{
    std::vector<uint8_t> bytes{};

    auto start = (char*)pat;
    auto end = start + strlen(pat);

    for (auto curr = start; curr < end; ++curr)
    {
        if (*curr == '?')
        {
            ++curr;

            if (*curr == '?')
                ++curr;

            bytes.push_back(-1);

            continue;
        }

        bytes.push_back(strtoul(curr, &curr, 16));
    }

    return bytes;
};

void c_utils::attach_console()
{
    AllocConsole();
    freopen("CONOUT$", "w", NULL);
    print("console ready");

    console_attached = true;
}

void c_utils::detach_console()
{
    print("detaching console");
    FreeConsole();

    console_attached = false;
}

bool c_utils::is_console_attached()
{
    return console_attached;
}

void c_utils::unprotect_process() // total junk
{

}

void c_utils::erase_pe_header()
{

}

template <typename T>
bool c_utils::write_memory_ex(void* address, T value)
{
    DWORD old = 0;

    if (!VirtualProtect(address, sizeof(T), PAGE_EXECUTE_READWRITE, &old))
        return false;

    memcpy(address, (void*)&value, sizeof(value));

    return VirtualProtect(address, sizeof(T), old, &old);
}

bool c_utils::write_memory(void* address, std::string bytes_s)
{
    DWORD old = 0;

    std::vector<std::uint8_t> bytes = string_to_bytes(bytes_s);

    if (!VirtualProtect(address, bytes.size(), PAGE_EXECUTE_READWRITE, &old))
        return false;

    memcpy(address, bytes.data(), bytes.size());

    return VirtualProtect(address, bytes.size(), old, &old);
}

template <typename T>
T c_utils::read_memory(uintptr_t address)
{
    T ret = *(T*)(address);
    return ret;
}