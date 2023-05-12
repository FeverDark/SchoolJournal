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

using namespace std;

// Этот класс экспортирован из библиотеки DLL
class FUNCTIONS_API CFunctions {
public:
	CFunctions(void);
	// TODO: добавьте сюда свои методы.
};

extern FUNCTIONS_API int nFunctions;

FUNCTIONS_API int fnFunctions(void);

const std::locale loc = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>);

class Child {
protected:
	wstring name;
	int cl;
	vector<double> marks;
public:
	Child() {

	}
	virtual ~Child() {

	}
};

class Student : public Child {
private:
public:
	Student(wstring name, int cl) {
		this->name = name;
		this->cl = cl;
	}
	~Student() {}
};

class Graduated : public Child {
private:
public:
	Graduated(wstring name, int cl) {
		this->name = name;
		this->cl = cl;
	}
	~Graduated() {}
};

class DB {
private:
	map<int, Child*>* db;
	map<int, wstring> subject;
	map<int, wstring> classes;
public:
	DB() {
		db = new map<int, Child*>;
		int id, klass;
		wstring str;
		wifstream file("subjects");
		file.imbue(loc);
		for (; file.is_open() && !file.eof();) {
			file >> id >> str;
			subject[id] = str;
		}
		file.close();
		file = wifstream("classes");
		for (; file.is_open() && !file.eof();) {
			file >> id >> str;
			classes[id] = str;
		}
		file.close();
		file = wifstream("students");
		for (; file.is_open() && !file.eof();) {
			file >> id >> str >> klass;
			db->insert(make_pair(id, new Student(str, klass)));
		}
		file.close();
		file = wifstream("graduated");
		for (; file.is_open() && !file.eof();) {
			file >> id >> str >> klass;
			db->insert(make_pair(id, new Graduated(str, klass))) ;
		}
		file.close();
	};
	~DB() {
		for (map<int, Child*>::iterator it = db->begin(); it != db->end(); ++it) {
			delete it->second;
		}
		delete db;
	}
};

