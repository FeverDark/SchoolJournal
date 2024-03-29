﻿// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа FUNCTIONS_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции FUNCTIONS_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef FUNCTIONS_EXPORTS
#define FUNCTIONS_API __declspec(dllexport)
#else
#define FUNCTIONS_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <clocale>
#include <cwctype>
#include <codecvt>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <regex>
#include <algorithm>

int wstringDateToInt(std::wstring str);
std::wstring intDateToWstring(int t);

struct FUNCTIONS_API Mark {
	double mark;
	int time;
	int subject;
	Mark(double mark, int time, int subject);
};

class FUNCTIONS_API Child {
protected:
	std::wstring name;
	int cl;
	std::vector<Mark> marks;
	int type = 0;
	double nowmark = 0;
public:
	Child();
	virtual ~Child();
	virtual void pushMark(int mark, std::wstring date, int subject);
	virtual std::wstring getName();
	virtual const std::vector<Mark>& getMarks() const;
	virtual void getDateMarks(std::vector<std::pair<double, int>>& ans, int l, int r, int subject);
	virtual void getDateMassMarks(double* (&mark), int* (&ti), int l, int r, int subject);
	virtual int getClass();
	virtual void deleteMark(int t, int subject);
	virtual void changeMark(int t, int mark, int subject);
	virtual int getType();
	virtual double getMark();
	virtual Child* copy();
};

class FUNCTIONS_API Student : public Child {
private:
public:
	Student(std::wstring name, int cl);
	~Student();
	void pushMark(int mark, std::wstring date, int subject);
	void deleteMark(int t, int subject);
	void changeMark(int t, int mark, int subject);
	Student(const Student& temp);
	Child* copy();
};

class FUNCTIONS_API Graduated : public Child {
private:
	double finalmark;
public:
	Graduated(std::wstring name, int cl, double mark);
	~Graduated();
	double getMark();
	Graduated(const Graduated& temp);
	Child* copy();
};

struct Comp
{
	bool operator()(Child* s, double i);
	bool operator()(double i, Child* s);
};

struct FUNCTIONS_API CompSet {
	bool operator() (Child* a, Child* b) const;
};

class DB {
public:
	std::map<int, Child*>* db;
	std::map<int, Child*>* viborka;
	std::map<int, std::wstring> subject;
	std::map<int, std::wstring> classes;
	DB();
	~DB();
	DB(const DB& temp);
	DB& operator=(const DB& temp);
	const std::map<int, Child*>& getDb() const;
	const std::map<int, std::wstring>& getSubject() const;
	const std::map<int, std::wstring>& getClasses() const;
	const std::map<int, Child*>& getStudentsFromClass(int cl, std::wstring finder);
	const std::map<int, Child*>& getGraduated();
	void deleteMark(std::wstring name, int t, int subject);
	void changeMark(std::wstring name, int mark, int t, int subject);
	void medalStudents(std::multiset<Child*, CompSet>& all);
	void saveFiles();
};

class FUNCTIONS_API Gasket {
private:
	static Gasket* instance;
	Gasket();
	Gasket(const Gasket&);
	Gasket& operator=(Gasket&);
public:
	static Gasket* getInstance();
	~Gasket();
	DB* db;
	std::vector<std::wstring> getClasses();
	void getMassClasses(int& size, wchar_t** (&str));
	std::vector<std::wstring> getSubject();
	void getMassSubject(int& size, wchar_t** (&str));
	std::vector<Child*> getGraduated();
	void getMassGraduated(int& size, Child** (&mass));
	std::vector<Child*> getStudentsFromClass(int cl, std::wstring finder);
	void getStudentsFromClassToMass(int& size, Child** (&mass), int cl, std::wstring finder);
	void deleteMark(std::wstring name, int t, int subject);
	void changeMark(std::wstring name, int mark, int t, int subject);
	void medalStudents(std::multiset<Child*, CompSet>& all);
	void medalMassStudents(int& size, Child** (&mass));
};

#endif // !FUNCTIONS_H
