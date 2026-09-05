#include "Contact.h"
#include <sstream>

// Dinh nghia bien static DUNG MOT LAN ngoai lop (bat buoc - Chapter 2)
int Contact::count = 0;

Contact::Contact(string name, string phone, string relationship)
    : Person(name, phone) {          // goi constructor CHA truoc (Chapter 4)
    this->relationship = relationship;
    ++count;
}

// Copy constructor: khi vector<Contact> copy phan tu, object MOI duoc tao
// -> van phai ++count, neu khong count se sai khi vector gian no.
Contact::Contact(const Contact& other)
    : Person(other.name, other.phone) {
    this->relationship = other.relationship;
    ++count;
}

Contact::~Contact() { --count; }

string Contact::getRelationship() const { return relationship; }
void Contact::setRelationship(const string& relationship) {
    this->relationship = relationship;
}

int Contact::getCount() { return count; }

// override display() - dung truc tiep name/phone vi chung la protected o cha
void Contact::display() const {
    cout << name << " | " << phone << " | " << relationship << endl;
}

bool Contact::operator==(const Contact& other) const {
    return phone == other.phone;         // cung sdt = cung mot contact
}
bool Contact::operator<(const Contact& other) const {
    return name < other.name;
}
bool Contact::operator>(const Contact& other) const {
    return other < *this;                // dung lai < cho gon, khong lap logic
}

// Doc 1 dong dinh dang: ten,sdt,quanhe  (ten duoc phep co khoang trang)
istream& operator>>(istream& in, Contact& c) {
    string line;
    if (!getline(in, line)) return in;
    stringstream ss(line);
    getline(ss, c.name, ',');
    getline(ss, c.phone, ',');
    getline(ss, c.relationship);
    return in;
}

// Ghi dung dinh dang doc vao -> load/save doi xung nhau
ostream& operator<<(ostream& out, const Contact& c) {
    out << c.name << "," << c.phone << "," << c.relationship;
    return out;
}
