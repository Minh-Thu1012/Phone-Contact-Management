#include "Person.h"
Person::Person(string name, string phone) 
{
    this->name = name;
    this->phone = phone;
}
Person::~Person() {}
string Person::getName() const { return name; }
string Person::getPhone() const { return phone; }
void Person::setName(const string& name) 
{
    this->name = name;
}
bool Person::setPhone(const string& phone) 
{    if (!isValidPhone(phone)) return false;
    this->phone = phone;
    return true;
}
bool Person::isValidPhone(const string& phone) 
{
    if (phone.length() < 9 || phone.length() > 11) return false;
    for (size_t i = 0; i < phone.length(); i++) 
    {
        if (phone[i] < '0' || phone[i] > '9') return false;
    }
    if (phone[0] != '0') return false;
    return true;
}