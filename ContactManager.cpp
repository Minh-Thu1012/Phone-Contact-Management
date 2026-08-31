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