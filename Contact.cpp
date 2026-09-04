/*
    Implementation of the Contact class.
    Handles contact information, relationship management,
    display, comparison, and input/output operations.
*/

#include<sstream>
#include"Contact.h"

int Contact::count = 0;

Contact::Contact(string name, string phone, string relationship)
    : Person(name, phone), relationship(relationship)
{
    ++count;
}

Contact::Contact(const Contact& other)
    : Person(other.name, other.phone) 
{
    this->relationship = other.relationship;
    ++count;
}

Contact::~Contact() 
{
    --count;
}

string Contact::getRelationship() const 
{
    return relationship;
}

void Contact::setRelationship(const string& rel) 
{
    relationship = rel;
}

int Contact::getCount() 
{
    return count;
}

void Contact::display() const 
{
    cout << name << " | " << phone << " | " << relationship << endl;
}

bool Contact::operator==(const Contact& o) const 
{
    return phone == o.phone;
}

bool Contact::operator<(const Contact& o) const 
{
    return name < o.name;
}

bool Contact::operator>(const Contact& o) const 
{
    return o < *this;
}

istream& operator>>(istream& in, Contact& c) 
{
    string line;
    if (!getline(in, line)) return in;
    stringstream ss(line);
    getline(ss, c.name, ',');
    getline(ss, c.phone, ',');
    getline(ss, c.relationship);
    return in;
}

ostream& operator<<(ostream& out, const Contact& c)
{
    out << c.name << "," << c.phone << "," << c.relationship;
    return out;
}