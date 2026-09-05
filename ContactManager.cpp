#include "ContactManager.h"
#include <fstream>
#include <algorithm>
#include <functional>

// helper private: chuyen ve chu thuong de so sanh khong phan biet hoa/thuong
string ContactManager::toLower(const string& s) {
    string r = s;
    for (size_t i = 0; i < r.length(); i++)
        r[i] = tolower(r[i]);
    return r;
}

// ---------- File I/O ----------

bool ContactManager::loadFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) return false;

    Contact c;
    while (fin >> c) {                            // dung operator>> cua Contact
        if (!Person::isValidPhone(c.getPhone())) {
            cout << "[Bo qua] Sdt khong hop le: " << c << endl;
            continue;
        }
        if (hasPhone(c.getPhone())) {             // chan trung sdt ngay tu file
            cout << "[Bo qua] Trung sdt: " << c << endl;
            continue;
        }
        contacts.push_back(c);
    }
    return true;
}

bool ContactManager::saveToFile(const string& filename) const {
    ofstream fout(filename);
    if (!fout) return false;
    for (size_t i = 0; i < contacts.size(); i++)
        fout << contacts[i] << endl;              // dung operator<< -> doi xung voi load
    return true;
}

// ---------- Truy van ----------

void ContactManager::displayAll() const {
    if (contacts.empty()) {
        cout << "(danh ba rong)" << endl;
        return;
    }
    for (size_t i = 0; i < contacts.size(); i++) {
        // DA HINH (Chapter 5): goi qua THAM CHIEU lop cha ->
        // display() la virtual nen chay ban cua Contact (object that).
        const Person& p = contacts[i];
        cout << i + 1 << ". ";
        p.display();
    }
}

bool ContactManager::hasPhone(const string& phone) const {
    // find() cua STL dung operator== (so theo sdt) - Chapter 6
    Contact key("", phone);
    return find(contacts.begin(), contacts.end(), key) != contacts.end();
}

int ContactManager::countName(const string& name) const {
    int dem = 0;
    for (size_t i = 0; i < contacts.size(); i++)
        if (toLower(contacts[i].getName()) == toLower(name)) dem++;
    return dem;
}

vector<Contact> ContactManager::searchByName(const string& keyword) const {
    vector<Contact> result;
    string kw = toLower(keyword);
    for (size_t i = 0; i < contacts.size(); i++)
        if (toLower(contacts[i].getName()).find(kw) != string::npos)  // tim GAN DUNG
            result.push_back(contacts[i]);
    return result;
}

vector<Contact> ContactManager::filterByRelationship(const string& rel) const {
    vector<Contact> result;
    for (size_t i = 0; i < contacts.size(); i++)
        if (toLower(contacts[i].getRelationship()) == toLower(rel))
            result.push_back(contacts[i]);
    return result;
}

map<string, int> ContactManager::statistics() const {
    map<string, int> stat;                         // STL map (Chapter 6)
    for (size_t i = 0; i < contacts.size(); i++)
        stat[contacts[i].getRelationship()]++;     // key tu sap xep
    return stat;
}

// ---------- Thay doi du lieu ----------

bool ContactManager::addContact(const Contact& c) {
    if (!Person::isValidPhone(c.getPhone())) return false;
    if (hasPhone(c.getPhone())) return false;      // VALIDATE trung sdt
    contacts.push_back(c);
    return true;
}

bool ContactManager::updateByPhone(const string& phone,
                                   const string& newName, const string& newRel) {
    Contact key("", phone);
    vector<Contact>::iterator it = find(contacts.begin(), contacts.end(), key);
    if (it == contacts.end()) return false;
    if (!newName.empty()) it->setName(newName);    // bo trong = giu nguyen
    if (!newRel.empty())  it->setRelationship(newRel);
    return true;
}

int ContactManager::deleteByName(const string& name) {
    int truoc = (int)contacts.size();
    for (vector<Contact>::iterator it = contacts.begin(); it != contacts.end(); )
        if (toLower(it->getName()) == toLower(name))
            it = contacts.erase(it);               // erase tra iterator ke tiep
        else
            ++it;
    return truoc - (int)contacts.size();
}

void ContactManager::sortByName(bool ascending) {
    if (ascending)
        sort(contacts.begin(), contacts.end());                      // operator<
    else
        sort(contacts.begin(), contacts.end(), greater<Contact>());  // operator>
}

int ContactManager::size() const { return (int)contacts.size(); }
