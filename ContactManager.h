#pragma once
#pragma once
#include "Contact.h"
#include <vector>
#include <map>
using namespace std;
template <typename T>
void printList(const vector<T>& v) 
{
    if (v.empty()) { cout << "(rong)\n"; return; }
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << endl;
}
class ContactManager {
private:
    vector<Contact> contacts;
    static string toLower(const string& s);
public:
    bool loadFromFile(const string& filename);
    bool saveToFile(const string& filename) const;
    bool hasPhone(const string& phone) const;
    int countName(const string& name) const;
    bool addContact(const Contact& c);
    bool updateByPhone(const string& phone, const string& newName, const string& newRel);
    int deleteByName(const string& name);
    vector<Contact> searchByName(const string& keyword) const;
    void sortByName(bool ascending = true);
    map<string, int> statistics() const;
    void displayAll() const;
};