/*
    Contact class declaration.
    Inherits from Person and adds relationship information,
    comparison operators, and input/output operators.
*/

#pragma once
#include "Person.h"

class Contact : public Person 
{

private:

    string relationship;
    static int count;

public:

    Contact(string name = "", string phone = "", string relationship = "unknown");
    Contact(const Contact& other);
    ~Contact();

    string getRelationship() const;

    static int getCount();

    void setRelationship(const string& rel);
    void display() const override;

    bool operator==(const Contact& o) const;
    bool operator<(const Contact& o) const;
    bool operator>(const Contact& o) const;

    friend istream& operator>>(istream& in, Contact& c);
    friend ostream& operator<<(ostream& out, const Contact& c);

};