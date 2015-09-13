#pragma once
#include <codecvt>

inline std::wstring widen(const std::string &narrow_string)
{
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(narrow_string.c_str());
}

inline std::string narrow(const std::wstring &wide_string)
{
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(wide_string);
}
