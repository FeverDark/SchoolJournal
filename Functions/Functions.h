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

const std::locale loc = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>);

int wstringDateToInt(std::wstring str);

class FUNCTIONS_API Child {
protected:
	std::wstring name;
	int cl;
	std::vector<std::pair<double, int>> marks;
public:
	Child() {}
	virtual ~Child() {}
	virtual void pushMark(int mark, std::wstring date) {}
	virtual std::wstring getName() { return this->name; }
	virtual const std::vector<std::pair<double, int>>& getMarks() const {
		return marks;
	}
	virtual std::vector<std::pair<double, int>> getDateMarks(int l, int r) {
		int k = (r - l) / 86399;
		std::vector<std::pair<double, int>> ans(k);		
		for (int i = 0; i < this->marks.size(); ++i) {
			if (marks[i].second >= l && marks[i].second <= r) {
				ans[(marks[i].second - l) / 86399] = marks[i];
			}
		}
		return ans;
	}
	virtual int getClass() {
		return this->cl;
	}
};

class FUNCTIONS_API Student : public Child {
private:
public:
	Student(std::wstring name, int cl) {
		this->name = name;
		this->cl = cl;
	}
	~Student() {}
	void pushMark(int mark, std::wstring date) {
		marks.push_back(std::make_pair(mark, wstringDateToInt(date)));
	}
};

class FUNCTIONS_API Graduated : public Child {
private:
public:
	Graduated(std::wstring name, int cl) {
		this->name = name;
		this->cl = cl;
	}
	~Graduated() {}
};

class FUNCTIONS_API DB {
private:
	std::map<int, Child*>* db;
	std::map<int, Child*>* viborka;
	std::map<int, std::wstring> subject;
	std::map<int, std::wstring> classes;
public:
	DB() {
		db = new std::map<int, Child*>;
		viborka = new std::map<int, Child*>;
		int id, klass;
		std::wstring str;
		std::wifstream file("subjects.txt");
		file.imbue(loc);
		for (; file.is_open() && !file.eof();) {
			file >> id >> str;
			subject[id] = str;
		}
		file.close();
		file = std::wifstream("classes.txt");
		file.imbue(loc);
		for (; file.is_open() && !file.eof();) {
			file >> id >> str;
			classes[id] = str;
		}
		file.close();
		file = std::wifstream("students.txt");
		file.imbue(loc);
		for (; file.is_open() && !file.eof();) {
			file >> id >> str >> klass;
			str = regex_replace(str, std::wregex(L"_"), L" ");
			db->insert(std::make_pair(id, new Student(str, klass)));
		}
		file.close();
		file = std::wifstream("graduated.txt");
		file.imbue(loc);
		for (; file.is_open() && !file.eof();) {
			file >> id >> str >> klass;
			db->insert(std::make_pair(id, new Graduated(str, klass))) ;
		}
		file.close();
		file = std::wifstream("marks.txt");
		for (; file.is_open() && !file.eof();) {
			file >> id >> klass >> str;
			(*db)[id]->pushMark(klass, str);
		}
		file.close();
	};
	~DB() {
		for (std::map<int, Child*>::iterator it = db->begin(); it != db->end(); ++it) {
			delete it->second;
		}
		delete db;
	}
	const std::map<int, Child*>& getDb() const {
		return *db;
	};
	const std::map<int, std::wstring>& getSubject() const {
		return subject;
	};
	const std::map<int, std::wstring>& getClasses() const {
		return classes;
	};
	std::map<int, Child*>& getStudentsFromClass(int cl) {
		if (cl == 0) {
			return *db;
		} else {
			delete viborka;
			viborka = new std::map<int, Child*>;
			for (std::map<int, Child*>::iterator i = db->begin(); i != db->end(); ++i) {
				if ((*i).second->getClass() == cl) {
					viborka->insert(std::make_pair((*i).first, (*i).second));
				}
			}
			return *viborka;
		}
	};
};

#endif // !FUNCTIONS_H
