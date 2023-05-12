// Functions.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "Functions.h"


// Пример экспортированной переменной
FUNCTIONS_API int nFunctions=0;

// Пример экспортированной функции.
FUNCTIONS_API int fnFunctions(void)
{
    return 0;
}

// Конструктор для экспортированного класса.
CFunctions::CFunctions()
{
    return;
}
