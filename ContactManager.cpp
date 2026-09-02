#include "ContactManager.h"
#include <fstream>
#include <algorithm>
#include <cctype>
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