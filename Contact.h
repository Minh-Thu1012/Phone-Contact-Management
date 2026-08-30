#pragma once
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
    void setRelationship(const string& rel);
    static int getCount();
    void display() const override;
    bool operator==(const Contact& o) const;
    bool operator<(const Contact& o) const;
    bool operator>(const Contact& o) const;
    friend istream& operator>>(istream& in, Contact& c);
    friend ostream& operator<<(ostream& out, const Contact& c);
};