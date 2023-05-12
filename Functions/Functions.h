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

#include <string>
#include <vector>
#include <map>
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

using namespace std;

const std::locale loc = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>);

int wstringDateToInt(wstring str);

class FUNCTIONS_API Child {
protected:
	wstring name;
	int cl;
	vector<pair<double, int>> marks;
public:
	Child() {}
	virtual ~Child() {}
	virtual void pushMark(int mark, wstring date) {}
	virtual wstring getName() { return this->name; }
	virtual const vector<pair<double, int>>& getMarks() const {
		return marks;
	}
};

class FUNCTIONS_API Student : public Child {
private:
public:
	Student(wstring name, int cl) {
		this->name = name;
		this->cl = cl;
	}
	~Student() {}
	void pushMark(int mark, wstring date) {
		marks.push_back(make_pair(mark, wstringDateToInt(date)));
	}
};

class FUNCTIONS_API Graduated : public Child {
private:
public:
	Graduated(wstring name, int cl) {
		this->name = name;
		this->cl = cl;
	}
	~Graduated() {}
};

class FUNCTIONS_API DB {
private:
	map<int, Child*>* db;
	map<int, wstring> subject;
	map<int, wstring> classes;
public:
	DB() {
		db = new map<int, Child*>;
		int id, klass;
		wstring str;
		wifstream file("subjects.txt");
		file.imbue(loc);
		for (; file.is_open() and !file.eof();) {
			file >> id >> str;
			subject[id] = str;
		}
		file.close();
		file = wifstream("classes.txt");
		file.imbue(loc);
		for (; file.is_open() && !file.eof();) {
			file >> id >> str;
			classes[id] = str;
		}
		file.close();
		file = wifstream("students.txt");
		file.imbue(loc);
		for (; file.is_open() && !file.eof();) {
			file >> id >> str >> klass;
			str = regex_replace(str, std::wregex(L"_"), L" ");
			db->insert(make_pair(id, new Student(str, klass)));
		}
		file.close();
		file = wifstream("graduated.txt");
		file.imbue(loc);
		for (; file.is_open() && !file.eof();) {
			file >> id >> str >> klass;
			db->insert(make_pair(id, new Graduated(str, klass))) ;
		}
		file.close();
		file = wifstream("marks.txt");
		for (; file.is_open() && !file.eof();) {
			file >> id >> klass >> str;
			(*db)[id]->pushMark(klass, str);
		}
		file.close();
	};
	~DB() {
		for (map<int, Child*>::iterator it = db->begin(); it != db->end(); ++it) {
			delete it->second;
		}
		delete db;
	}
	const map<int, Child*>& getDb() const {
		return *db;
	};
	const map<int, wstring>& getSubject() const {
		return subject;
	};
	const map<int, wstring>& getClasses() const {
		return classes;
	};
};

