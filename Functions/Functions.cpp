// Functions.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "Functions.h"

#define DEBUG_VERSION

int wstringDateToInt(wstring str) {
	tm t{};
	wistringstream ss(str);
	ss >> get_time(&t, L"%Y-%m-%d");
	time_t time_stamp = mktime(&t);
	#ifdef DEBUG_VERSION
	ofstream file("debug.txt", ofstream::out);
	file << time_stamp;
	file.close();
	#endif
	return time_stamp;
}