// Functions.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "Functions.h"

#define DEBUG_VERSION

int wstringDateToInt(std::wstring str) {
	tm t{};
	std::wistringstream ss(str);
	ss >> std::get_time(&t, L"%Y-%m-%d");
	time_t time_stamp = _mkgmtime(&t);
	#ifdef DEBUG_VERSION
	std::ofstream file("debug.txt", std::ofstream::out);
	file << time_stamp;
	file.close();
	#endif
	return time_stamp;
}