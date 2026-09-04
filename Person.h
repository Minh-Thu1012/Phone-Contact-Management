/*
    Person class declaration.
    Defines common information and functions for a person,
    including name, phone number, name formatting, and phone validation.
*/

#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:

	string name;
	string phone;
public:

	Person(string name = "", string phone = "");
	virtual ~Person();
	virtual void display() const = 0;

	string getName() const;
	string getPhone() const;

	void setName(const string& name);
	void formatName(string& rawName);
	void setPhone(const string& phone);

	static bool isValidPhone(const string& phone);

};

