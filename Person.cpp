#include "Person.h"

Person::Person(string name, string phone) {
    // this-> de phan biet BIEN THANH VIEN voi THAM SO trung ten (Chapter 2)
    this->name = name;
    this->phone = phone;
}

Person::~Person() {}

string Person::getName() const { return name; }
string Person::getPhone() const { return phone; }

void Person::setName(const string& name) { this->name = name; }

bool Person::setPhone(const string& phone) {
    if (!isValidPhone(phone)) return false;   // validate tai "cua ngo" duy nhat
    this->phone = phone;
    return true;
}

// Sdt hop le: chi gom chu so, dai 9-11 ky tu
bool Person::isValidPhone(const string& phone) {
    if (phone.length() < 9 || phone.length() > 11) return false;
    for (size_t i = 0; i < phone.length(); i++)
        if (phone[i] < '0' || phone[i] > '9') return false;
    return true;
}
