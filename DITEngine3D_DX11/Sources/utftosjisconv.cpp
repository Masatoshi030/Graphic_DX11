#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

// ワイド文字をｓ－ｊｉｓに
std::string wide_to_multi_winapi(std::wstring const& src)
{
	auto const dest_size = ::WideCharToMultiByte(
		CP_ACP, 
		0U, 
		src.data(), 
		-1, 
		nullptr, 
		0, 
		nullptr, 
		nullptr);
	std::vector<char> dest(dest_size, '\0');
	if (::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, dest.data(), (int)(dest.size()), nullptr, nullptr) == 0) {
		throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
	}
	dest.resize(std::char_traits<char>::length(dest.data()));
	dest.shrink_to_fit();
	return std::string(dest.begin(), dest.end());
}

// utf-8をワイド文字(utf-16)に
std::wstring utf8_to_wide_winapi(std::string const& src)
{
	auto const dest_size = ::MultiByteToWideChar(
		CP_UTF8,			 // ソース側がUTF-8
		0U, 
		src.data(), 
		-1, 
		nullptr, 
		0U);
	std::vector<wchar_t> dest(dest_size, L'\0');
	if (::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, dest.data(), (int)(dest.size())) == 0) {
		throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
	}
	dest.resize(std::char_traits<wchar_t>::length(dest.data()));
	dest.shrink_to_fit();
	return std::wstring(dest.begin(), dest.end());
}

// utf8をS-JISに
std::string utf8_to_multi_winapi(std::string const& src)
{
	auto const wide = utf8_to_wide_winapi(src);
	return wide_to_multi_winapi(wide);
}

// s-jisをワイド文字に
std::wstring sjis_to_wide_winapi(std::string const& src)
{
	wchar_t ws[1024];							
	size_t ret;

	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 1024, src.c_str(), _TRUNCATE);

	std::wstring w(ws);

	return w;

}