/*
    ContactManager class declaration.
    Manages the contact list and provides functions for
    loading, saving, adding, updating, deleting, searching,
    sorting, filtering, and statistics.
*/

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
    bool addContact(const Contact& c);
    bool updateByPhone(const string& phone, const string& newName, const string& newRel);
    
    int countName(const string& name) const;
    int deleteByName(const string& name);
    vector<Contact> searchByName(const string& keyword) const;
    vector<Contact> filterByRelationship(const string& relationship) const;

    void sortByName(bool ascending = true);
    void displayAll() const;
    
    map<string, int> statistics() const;
};