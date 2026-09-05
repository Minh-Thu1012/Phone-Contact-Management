#pragma once
#include "Contact.h"
#include <vector>
#include <map>

// ============================================================
// Ham TEMPLATE (Chapter 6): in bat ky vector<T> nao,
// mien T co operator<<. Viet MOT lan, dung cho moi kieu.
// Dung ITERATOR de duyet (Chapter 6 - STL).
// ============================================================
template <typename T>
void printList(const vector<T>& v) {
    if (v.empty()) {
        cout << "(danh sach rong)" << endl;
        return;
    }
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << endl;
}

// ============================================================
// ContactManager - quan ly danh ba (Chapter 6: STL)
// Chi lo LOGIC du lieu. KHONG in menu, KHONG hoi nguoi dung
// -> viec do la cua main.cpp. Tach UI khoi logic de de test/de sua.
// ============================================================
class ContactManager {
private:
    // private: danh sach la "ruot" cua manager, ben ngoai KHONG duoc
    // tu y them/xoa ma phai qua cac ham co kiem tra trung lap ben duoi.
    vector<Contact> contacts;              // STL container chinh

    // private helper: chi dung noi bo, ben ngoai khong can biet
    static string toLower(const string& s);

public:
    // ----- File I/O -----
    bool loadFromFile(const string& filename);   // doc contacts.txt
    bool saveToFile(const string& filename) const;

    // ----- Truy van (const: chi doc, khong sua danh sach) -----
    void displayAll() const;                     // hien thi qua Person& -> DA HINH
    bool hasPhone(const string& phone) const;    // kiem tra trung sdt
    int  countName(const string& name) const;    // dem so contact trung ten
    vector<Contact> searchByName(const string& keyword) const;       // tim gan dung, khong phan biet hoa/thuong
    vector<Contact> filterByRelationship(const string& rel) const;   // loc theo quan he
    map<string, int> statistics() const;         // STL map: quan he -> so luong

    // ----- Thay doi du lieu -----
    bool addContact(const Contact& c);                // false neu sdt trung/khong hop le
    bool updateByPhone(const string& phone,
                       const string& newName, const string& newRel);
    int  deleteByName(const string& name);            // tra ve so contact da xoa
    void sortByName(bool ascending);                  // sort() + operator< / operator>

    int size() const;
};
