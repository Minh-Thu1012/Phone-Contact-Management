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
	string getName() const;
	string getPhone() const;
	void setName(const string& name);
	void setPhone(const string& phone);
	static bool isValidPhone(const string& phone);
	virtual void display() const = 0;
};

