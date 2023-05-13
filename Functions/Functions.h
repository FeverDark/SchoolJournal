// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа FUNCTIONS_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции FUNCTIONS_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.

#ifdef FUNCTIONS_EXPORTS
#define FUNCTIONS_API __declspec(dllexport)
#else
#define FUNCTIONS_API __declspec(dllimport)
#endif

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

struct Mark {
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
	virtual std::vector<std::pair<double, int>> getDateMarks(int l, int r, int subject);
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

struct CompSet {
	bool operator() (Child* a, Child* b) const;
};

class FUNCTIONS_API DB {
private:
	std::map<int, Child*>* db;
	std::map<int, Child*>* viborka;
	std::map<int, std::wstring> subject;
	std::map<int, std::wstring> classes;
public:
	DB();
	~DB();
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

#endif // !FUNCTIONS_H
