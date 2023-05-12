#include "Functions.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    DB* db = new DB();
    //cout << db->getClasses().size() << " " << db->getDb().size() << " " << db->getSubject().size();
    map<int, Child*> temp = db->getDb();
    for (auto i : temp) {
        wcout << i.first << " " << i.second->getName() << endl;
        for (auto j : i.second->getMarks()) {
            wcout << j.first << " " << j.second << endl;
        }
    }
    delete db;
    return 0;
}
