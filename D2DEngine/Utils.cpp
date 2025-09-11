#include "pch.h"
#include "Utils.h"

std::wstring FormatBytes(SIZE_T bytes)
{
    constexpr double KB = 1024.0;
    constexpr double MB = KB * 1024.0;
    constexpr double GB = MB * 1024.0;

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    if (bytes >= static_cast<UINT64>(GB))
    {
        oss << (bytes / GB) << " GB";
    }
    else if (bytes >= static_cast<UINT64>(MB))
    {
        oss << (bytes / MB) << " MB";
    }
    else if (bytes >= static_cast<UINT64>(KB))
    {
        oss << (bytes / KB) << " KB";
    }
    else
    {
        oss << bytes << " B";
    }

    std::string str = oss.str();

    std::wstring wstr(str.begin(), str.end());

    return wstr;
}
