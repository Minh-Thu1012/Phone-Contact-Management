/*
    Implementation of the Person class.
    Handles name formatting, phone number validation,
    getters, setters, and other Person-related functions.
*/

#include "Person.h"
#include <iostream>
#include <cctype>

Person::Person(string name, string phone)
{
    setName(name);
    this->phone = phone;
}

Person::~Person() {}

string Person::getName() const { return name; }

string Person::getPhone() const { return phone; }

void Person::setPhone(const string& phone) 
{
    if (isValidPhone(phone)) 
    {
        this->phone = phone;
    }
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

void Person::formatName(string& rawName) 
{
    string result = "";
    bool newWord = true;
    for (size_t i = 0; i < rawName.length(); i++) 
    {
        if (rawName[i] == ' ') 
        {
            if (result.length() > 0 && result.back() != ' ') 
            {
                result += ' '; 
            }
            newWord = true;
        }
        else {
            if (newWord) 
            {
                result += toupper(rawName[i]);
                newWord = false;
            }
            else 
            {
                result += tolower(rawName[i]);
            }
        }
    }
    if (!result.empty() && result.back() == ' ') result.pop_back();
    rawName = result;
}

void Person::setName(const string& name) 
{
    string formatted = name;
    formatName(formatted);
    this->name = formatted;
}