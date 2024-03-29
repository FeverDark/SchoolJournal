﻿// Functions.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "Functions.h"

const std::locale loc = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>);

int wstringDateToInt(std::wstring str) {
	tm t{};
	std::wistringstream ss(str);
	ss >> std::get_time(&t, L"%Y-%m-%d");
	time_t time_stamp = _mkgmtime(&t);
	return time_stamp;
}

std::wstring intDateToWstring(int t) {
	time_t old = (time_t)t;
	tm* q = new tm{ 0 };
	gmtime_s(q, &old);
	std::wstringstream tmp;
	tmp << std::put_time(q, L"%Y-%m-%d");
	delete q;
	return tmp.str();
}

Mark::Mark(double mark, int time, int subject) {
	this->mark = mark;
	this->time = time;
	this->subject = subject;
}

Child::Child() {}
Child:: ~Child() {}
void Child::pushMark(int mark, std::wstring date, int subject) {}
std::wstring Child::getName() { return this->name; }
const std::vector<Mark>& Child::getMarks() const {
	return marks;
}
void Child::getDateMarks(std::vector<std::pair<double, int>>& ans, int l, int r, int subject) {
	int k = (r - l) / 86399;
	for (int i = 0; i < this->marks.size(); ++i) {
		if (marks[i].time >= l && marks[i].time <= r && marks[i].subject == subject) {
			ans[(marks[i].time - l) / 86399] = std::make_pair(marks[i].mark, marks[i].time);
		}
	}
}
void Child::getDateMassMarks(double* (&mark), int* (&ti), int l, int r, int subject) {
	int k = (r - l) / 86399;
	mark = new double[k];
	ti = new int[k];
	for (int i = 0; i < k; ++i) {
		mark[i] = 0;
		ti[i] = 0;
	}
	for (int i = 0; i < this->marks.size(); ++i) {
		if (marks[i].time >= l && marks[i].time <= r && marks[i].subject == subject) {
			mark[(marks[i].time - l) / 86399] = marks[i].mark;
			ti[(marks[i].time - l) / 86399] = marks[i].time;
		}
	}
}
int Child::getClass() {
	return this->cl;
}
void Child::deleteMark(int t, int subject) {}
void Child::changeMark(int t, int mark, int subject) {}
int Child::getType() {
	return this->type;
}
double Child::getMark() {
	return round(nowmark * 100) / 100;
}
Child* Child::copy() {
	return NULL;
}

Student::Student(std::wstring name, int cl) {
	this->name = name;
	this->cl = cl;
	this->type = 1;
}
Student::~Student() {}
void Student::pushMark(int mark, std::wstring date, int subject) {
	marks.push_back(Mark(mark, wstringDateToInt(date), subject));
	nowmark = 0;
	for (std::vector<Mark>::const_iterator j = marks.begin(); j != marks.end(); ++j) {
		nowmark += (*j).mark;
	}
	nowmark /= marks.size();
}
void Student::deleteMark(int t, int subject) {
	time_t old = (time_t)t;
	tm* q = new tm{ 0 };
	gmtime_s(q, &old);
	for (std::vector<Mark>::const_iterator i = marks.begin(); i != marks.end(); ++i) {
		old = (time_t)(*i).time;
		tm* temp = new tm{ 0 };
		gmtime_s(temp, &old);
		if (temp->tm_year == q->tm_year && temp->tm_mon == q->tm_mon && temp->tm_mday == q->tm_mday && (*i).subject == subject) {
			delete q;
			delete temp;
			marks.erase(i);
			nowmark = 0;
			for (std::vector<Mark>::const_iterator j = marks.begin(); j != marks.end(); ++j) {
				nowmark += (*j).mark;
			}
			nowmark /= marks.size();
			return;
		}
		delete temp;
	}
	delete q;
}
void Student::changeMark(int t, int mark, int subject) {
	time_t old = (time_t)t;
	tm* q = new tm{ 0 };
	gmtime_s(q, &old);
	for (std::vector<Mark>::iterator i = marks.begin(); i != marks.end(); ++i) {
		old = (time_t)(*i).time;
		tm* temp = new tm{ 0 };
		gmtime_s(temp, &old);
		if (temp->tm_year == q->tm_year && temp->tm_mon == q->tm_mon && temp->tm_mday == q->tm_mday && (*i).subject == subject) {
			(*i).mark = mark;
			(*i).time = t;
			delete q;
			delete temp;
			nowmark = 0;
			for (std::vector<Mark>::const_iterator j = marks.begin(); j != marks.end(); ++j) {
				nowmark += (*j).mark;
			}
			nowmark /= marks.size();
			return;
		}
		delete temp;
	}
	std::wstringstream tmp;
	tmp << std::put_time(q, L"%Y-%m-%d");
	this->pushMark(mark, tmp.str(), subject);
	delete q;
	nowmark = 0;
	for (std::vector<Mark>::const_iterator j = marks.begin(); j != marks.end(); ++j) {
		nowmark += (*j).mark;
	}
	nowmark /= marks.size();
}
Student::Student(const Student& temp) {
	name = temp.name;
	cl = temp.cl;
	type = temp.type;
}
Child* Student::copy() {
	return new Student(*this);
}

Graduated::Graduated(std::wstring name, int cl, double mark) {
	this->name = name;
	this->cl = cl;
	this->finalmark = mark;
	this->type = 2;
}
Graduated::~Graduated() {}
double Graduated::getMark() {
	return round(finalmark * 100) / 100;
}
Graduated::Graduated(const Graduated& temp) {
	name = temp.name;
	cl = temp.cl;
	type = temp.type;
	finalmark = temp.finalmark;
}
Child* Graduated::copy() {
	return new Graduated(*this);
}

bool Comp::operator()(Child* s, double i) { return s->getMark() < i; }
bool Comp::operator()(double i, Child* s) { return i < s->getMark(); }

bool CompSet::operator() (Child* a, Child* b) const {
	return a->getMark() < b->getMark();
}

DB::DB() {
	db = new std::map<int, Child*>;
	viborka = new std::map<int, Child*>;
	int id, klass;
	std::wstring str;
	std::wifstream file("subjects.txt");
	file.imbue(loc);
	for (; file.is_open() && !file.eof();) {
		id = NULL;
		file >> id >> str;
		str = regex_replace(str, std::wregex(L"_"), L" ");
		if (id != NULL)
			subject[id] = str;
	}
	file.close();
	file = std::wifstream("classes.txt");
	file.imbue(loc);
	for (; file.is_open() && !file.eof();) {
		id = NULL;
		file >> id >> str;
		if (id != NULL)
			classes[id] = str;
	}
	file.close();
	file = std::wifstream("students.txt");
	file.imbue(loc);
	for (; file.is_open() && !file.eof();) {
		id = NULL;
		file >> id >> str >> klass;
		str = regex_replace(str, std::wregex(L"_"), L" ");
		if (id != NULL)
			db->insert(std::make_pair(id, new Student(str, klass)));
	}
	file.close();
	file = std::wifstream("graduated.txt");
	file.imbue(loc);
	for (; file.is_open() && !file.eof();) {
		id = NULL;
		double mark;
		file >> id >> str >> klass >> mark;
		str = regex_replace(str, std::wregex(L"_"), L" ");
		if (id != NULL)
			db->insert(std::make_pair(id, new Graduated(str, klass, mark)));
	}
	file.close();
	file = std::wifstream("marks.txt");
	for (; file.is_open() && !file.eof();) {
		id = NULL;
		int subject;
		file >> id >> klass >> str >> subject;
		if(id != NULL)
			(*db)[id]->pushMark(klass, str, subject);
	}
	file.close();
};
DB::~DB() {
	saveFiles();
	for (std::map<int, Child*>::const_iterator it = db->begin(); it != db->end(); ++it) {
		delete it->second;
	}
	delete db;
	delete viborka;
}
const std::map<int, Child*>& DB::getDb() const {
	return *db;
};
const std::map<int, std::wstring>& DB::getSubject() const {
	return subject;
};
const std::map<int, std::wstring>& DB::getClasses() const {
	return classes;
};
const std::map<int, Child*>& DB::getStudentsFromClass(int cl, std::wstring finder) {
	viborka->clear();
	delete viborka;
	viborka = new std::map<int, Child*>;
	for (std::map<int, Child*>::iterator i = db->begin(); i != db->end(); ++i) {
		if (((*i).second->getClass() == cl || cl == 0) && (finder == L"" || (*i).second->getName().find(finder) != std::wstring::npos) && (*i).second->getType() == 1) {
			viborka->insert(std::make_pair(i->first, i->second));
		}
	}
	return *viborka;
};
DB::DB(const DB& temp) {
	db = new std::map<int, Child*>;
	viborka = new std::map<int, Child*>;
	for (std::map<int, std::wstring>::const_iterator i = temp.classes.begin(); i != temp.classes.end(); ++i) {
		classes.insert(std::make_pair(i->first, i->second));
	}
	for (std::map<int, std::wstring>::const_iterator i = temp.subject.begin(); i != temp.subject.end(); ++i) {
		subject.insert(std::make_pair(i->first, i->second));
	}
	for (std::map<int, Child*>::const_iterator i = temp.db->begin(); i != temp.db->end(); ++i) {
		db->insert(std::make_pair(i->first, i->second->copy()));
	}
};
DB& DB::operator=(const DB& temp) {
	if (this != &temp) {
		for (std::map<int, Child*>::const_iterator it = db->begin(); it != db->end(); ++it) {
			delete it->second;
		}
		classes.clear();
		subject.clear();
		db->clear();
		viborka->clear();
		delete db;
		delete viborka;
		db = new std::map<int, Child*>;
		viborka = new std::map<int, Child*>;
		for (std::map<int, std::wstring>::const_iterator i = temp.classes.begin(); i != temp.classes.end(); ++i) {
			classes.insert(std::make_pair(i->first, i->second));
		}
		for (std::map<int, std::wstring>::const_iterator i = temp.subject.begin(); i != temp.subject.end(); ++i) {
			subject.insert(std::make_pair(i->first, i->second));
		}
		for (std::map<int, Child*>::const_iterator i = temp.db->begin(); i != temp.db->end(); ++i) {
			db->insert(std::make_pair(i->first, i->second->copy()));
		}
	}
	return *this;
};
const std::map<int, Child*>& DB::getGraduated() {
	viborka->clear();
	delete viborka;
	viborka = new std::map<int, Child*>;
	for (std::map<int, Child*>::iterator i = db->begin(); i != db->end(); ++i) {
		if ((*i).second->getType() == 2) {
			viborka->insert(std::make_pair(i->first, i->second));
		}
	}
	return *viborka;
}
void DB::deleteMark(std::wstring name, int t, int subject) {
	for (std::map<int, Child*>::iterator i = db->begin(); i != db->end(); ++i) {
		if ((*i).second->getName() == name) {
			(*i).second->deleteMark(t, subject);
			break;
		}
	}
}
void DB::changeMark(std::wstring name, int mark, int t, int subject) {
	for (std::map<int, Child*>::iterator i = db->begin(); i != db->end(); ++i) {
		if ((*i).second->getName() == name) {
			(*i).second->changeMark(t, mark, subject);
			break;
		}
	}
}
void DB::medalStudents(std::multiset<Child*, CompSet>& all) {
	std::set<Child*, CompSet> temps, tempg;
	std::map<int, Child*> st = this->getStudentsFromClass(0, L"");
	for (std::map<int, Child*>::const_iterator i = st.begin(); i != st.end(); ++i) temps.insert((*i).second);
	std::map<int, Child*> gr = this->getGraduated();
	for (std::map<int, Child*>::const_iterator i = gr.begin(); i != gr.end(); ++i) tempg.insert((*i).second);
	auto ranges = std::equal_range(temps.begin(), temps.end(), (double)5, Comp{}), rangeg = std::equal_range(tempg.begin(), tempg.end(), (double)5, Comp{});
	std::set_union(ranges.first, ranges.second, rangeg.first, rangeg.second, std::inserter(all, all.begin()));

}
void DB::saveFiles() {
	std::wofstream file("subjects.txt", std::wofstream::trunc);
	file.imbue(loc);
	for (std::map<int, std::wstring>::iterator i = this->subject.begin(); i != this->subject.end() && file.is_open(); ++i) {
		file << (*i).first << " " << regex_replace((*i).second, std::wregex(L" "), L"_");
		file << std::endl;
	}
	file.close();
	file = std::wofstream("classes.txt", std::wofstream::trunc);
	file.imbue(loc);
	for (std::map<int, std::wstring>::iterator i = this->classes.begin(); i != this->classes.end() && file.is_open(); ++i) {
		file << (*i).first << " " << (*i).second;
		file << std::endl;
	}
	file.close();
	file = std::wofstream("students.txt", std::wofstream::trunc);
	file.imbue(loc);
	for (std::map<int, Child*>::iterator i = this->db->begin(); i != this->db->end() && file.is_open(); ++i) {
		if ((*i).second->getType() == 1) {
			file << (*i).first << " " << regex_replace((*i).second->getName(), std::wregex(L" "), L"_") << " " << (*i).second->getClass();
			file << std::endl;
		}
	}
	file.close();
	file = std::wofstream("graduated.txt", std::wofstream::trunc);
	file.imbue(loc);
	for (std::map<int, Child*>::iterator i = this->db->begin(); i != this->db->end() && file.is_open(); ++i) {
		if ((*i).second->getType() == 2) {
			file << (*i).first << " " << regex_replace((*i).second->getName(), std::wregex(L" "), L"_") << " " << (*i).second->getClass() << " " << (*i).second->getMark();
			file << std::endl;
		}
	}
	file.close();
	file = std::wofstream("marks.txt", std::wofstream::trunc);
	file.imbue(loc);
	for (std::map<int, Child*>::iterator i = this->db->begin(); i != this->db->end() && file.is_open(); ++i) {
		if ((*i).second->getType() == 1) {
			std::vector<Mark> temp = (*i).second->getMarks();
			for (int j = 0; j < temp.size(); ++j) {
				file << (*i).first << " " << temp[j].mark << " " << intDateToWstring(temp[j].time) << " " << temp[j].subject;
				file << std::endl;
			}
		}
	}
	file.close();
}

Gasket::Gasket() {
	db = new DB();
}

Gasket* Gasket::getInstance() {
	if (!instance)
		instance = new Gasket();
	return instance;
}
Gasket::~Gasket() {
	delete db;
};

Gasket* Gasket::instance = 0;

std::vector<std::wstring> Gasket::getClasses() {
	std::vector<std::wstring> a;
	for (std::map<int, std::wstring>::const_iterator i = db->classes.begin(); i != db->classes.end(); ++i) {
		a.push_back((*i).second);
	}
	return a;
}
void Gasket::getMassClasses(int& size, wchar_t**(&str)) {
	size = db->classes.size();
	str = new wchar_t*[size];
	int j = 0;
	for (std::map<int, std::wstring>::const_iterator i = db->classes.begin(); i != db->classes.end(); ++i) {
		str[j] = new wchar_t[1024];
		wcscpy_s(str[j], 1024, (*i).second.c_str());
		j++;
	}
}
std::vector<std::wstring> Gasket::getSubject() {
	std::vector<std::wstring> a;
	for (std::map<int, std::wstring>::const_iterator i = db->subject.begin(); i != db->subject.end(); ++i) {
		a.push_back((*i).second);
	}
	return a;
}
void Gasket::getMassSubject(int& size, wchar_t** (&str)) {
	size = db->classes.size();
	str = new wchar_t* [size];
	int j = 0;
	for (std::map<int, std::wstring>::const_iterator i = db->classes.begin(); i != db->classes.end(); ++i) {
		str[j] = new wchar_t[1024];
		wcscpy_s(str[j], 1024, (*i).second.c_str());
		j++;
	}
}
std::vector<Child*> Gasket::getGraduated() {
	std::map<int, Child*> a = db->getGraduated();
	std::vector<Child*> b;
	for (std::map<int, Child*>::const_iterator i = a.begin(); i != a.end(); ++i) {
		b.push_back((*i).second);
	}
	return b;
}
void Gasket::getMassGraduated(int& size, Child** (&mass)) {
	std::map<int, Child*> a = db->getGraduated();
	mass = new Child * [a.size()];
	int j = 0;
	for (std::map<int, Child*>::const_iterator i = a.begin(); i != a.end(); ++i) {
		mass[j] = (*i).second;
		j++;
	}
	size = a.size();
}
std::vector<Child*> Gasket::getStudentsFromClass(int cl, std::wstring finder) {
	std::map<int, Child*> a = db->getStudentsFromClass(cl, finder);
	std::vector<Child*> b;
	for (std::map<int, Child*>::const_iterator i = a.begin(); i != a.end(); ++i) {
		b.push_back((*i).second);
	}
	return b;
}
void Gasket::getStudentsFromClassToMass(int& size, Child**(&mass), int cl, std::wstring finder) {
	std::map<int, Child*> a = db->getStudentsFromClass(cl, finder);
	mass = new Child*[a.size()];
	int j = 0;
	for (std::map<int, Child*>::const_iterator i = a.begin(); i != a.end(); ++i) {
		mass[j] = (*i).second;
		j++;
	}
	size = a.size();
}
void Gasket::deleteMark(std::wstring name, int t, int subject) {
	db->deleteMark(name, t, subject);
}
void Gasket::changeMark(std::wstring name, int mark, int t, int subject) {
	db->changeMark(name, mark, t, subject);
}
void Gasket::medalStudents(std::multiset<Child*, CompSet>& all) {
	db->medalStudents(all);
}

void Gasket::medalMassStudents(int& size, Child** (&mass)) {
	std::multiset<Child*, CompSet> all;
	db->medalStudents(all);
	size = all.size();
	mass = new Child * [size];
	int j = 0;
	for (std::multiset<Child*, CompSet>::iterator i = all.begin(); i != all.end(); ++i) {
		mass[j] = (*i);
		j++;
	}
}
