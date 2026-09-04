/*
    Implementation of the ContactManager class.
    Handles contact management operations including file I/O,
    searching, sorting, filtering, adding, updating, deleting,
    and relationship statistics.
*/

#include "ContactManager.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <functional>

string ContactManager::toLower(const string& s) 
{
    string res = s;
    for (size_t i = 0; i < res.length(); i++) 
    {
        res[i] = tolower(res[i]);
    }
    return res;
}

bool ContactManager::hasPhone(const string& p) const 
{
    Contact key("", p); 
    return find(contacts.begin(), contacts.end(), key) != contacts.end();
}

int ContactManager::countName(const string& name) const 
{
    int count = 0;
    string target = toLower(name);
    for (size_t i = 0; i < contacts.size(); i++) 
    {
        if (toLower(contacts[i].getName()) == target) 
        {
            count++;
        }
    }
    return count;
}

bool ContactManager::loadFromFile(const string& f) 
{
    ifstream fin(f);
    if (!fin) return false;

    Contact c;
    while (fin >> c) 
    { 
        if (!Person::isValidPhone(c.getPhone())) continue; 
        if (hasPhone(c.getPhone())) continue;              

        contacts.push_back(c);
    }
    return true;
}

bool ContactManager::saveToFile(const string& f) const 
{
    ofstream fout(f);
    if (!fout) return false;

    for (size_t i = 0; i < contacts.size(); i++) 
    {
        fout << contacts[i] << "\n";
    }
    return true;
}

bool ContactManager::addContact(const Contact& c) 
{
    if (!Person::isValidPhone(c.getPhone())) return false; 
    if (hasPhone(c.getPhone())) return false;              
    contacts.push_back(c);
    return true;
}

void ContactManager::displayAll() const 
{
    for (size_t i = 0; i < contacts.size(); i++) 
    {
        const Person& p = contacts[i];
        cout << i + 1 << ". ";
        p.display();
    }
}

bool ContactManager::updateByPhone(const string& phone, const string& newName, const string& newRel) 
{
    Contact key("", phone); 
    vector<Contact>::iterator it = find(contacts.begin(), contacts.end(), key);
    if (it == contacts.end()) return false;
    if (!newName.empty()) it->setName(newName); 
    if (!newRel.empty())  it->setRelationship(newRel);
    return true;
}

int ContactManager::deleteByName(const string& name) 
{
    int count = 0;
    for (auto it = contacts.begin(); it != contacts.end(); ) 
    {
        if (toLower(it->getName()) == toLower(name)) 
        {
            it = contacts.erase(it);
            count++;
        }
        else {
            ++it; 
        }
    }
    return count;
}

vector<Contact> ContactManager::searchByName(const string& keyword) const 
{
    vector<Contact> result;
    string kw = toLower(keyword);
    for (size_t i = 0; i < contacts.size(); i++) 
    {
        if (toLower(contacts[i].getName()).find(kw) != string::npos) 
        {
            result.push_back(contacts[i]);
        }
    }
    return result; 
}

void ContactManager::sortByName(bool ascending) 
{
    if (ascending)
        sort(contacts.begin(), contacts.end()); 
    else
        sort(contacts.begin(), contacts.end(), greater<Contact>());
}

map<string, int> ContactManager::statistics() const 
{
    map<string, int> stat;
    for (size_t i = 0; i < contacts.size(); i++) 
    {
        stat[contacts[i].getRelationship()]++;
    }
    return stat;
}

vector<Contact> ContactManager::filterByRelationship(const string& relationship) const
{
    vector<Contact> result;
    string target = toLower(relationship);

    for (size_t i = 0; i < contacts.size(); i++)
    {
        if (toLower(contacts[i].getRelationship()) == target)
        {
            result.push_back(contacts[i]);
        }
    }

    return result;
}