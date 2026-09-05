#pragma once
#include <iostream>
#include <string>
using namespace std;

// ============================================================
// Person - lop co so TRUU TUONG (Chapter 4 + 5)
// Dai dien cho "mot nguoi co ten va so dien thoai".
// Truu tuong vi: khong ai la "Person chung chung" - phai la
// mot loai cu the (Contact, sau nay co the la BlockedContact...)
// ============================================================
class Person {
protected:
    // protected (KHONG phai private): lop con (Contact) can doc/ghi
    // truc tiep name, phone khi hien thi & cap nhat.
    // KHONG de public: ben ngoai phai di qua setter de duoc VALIDATE.
    string name;
    string phone;

public:
    Person(string name = "", string phone = "");

    // Destructor VIRTUAL (Chapter 5): neu xoa Contact qua con tro Person*
    // thi destructor cua Contact van duoc goi -> khong ro ri tai nguyen.
    virtual ~Person();

    // Getter: public vi ben ngoai can DOC thong tin.
    // const: cam kem ham chi doc, khong sua object (Chapter 2).
    string getName() const;
    string getPhone() const;

    // Setter: public vi ben ngoai can SUA, nhung sua CO KIEM SOAT.
    void setName(const string& name);
    bool setPhone(const string& phone);   // tra false neu sdt khong hop le

    // static (Chapter 2): quy tac kiem tra sdt la cua CA LOP,
    // khong gan voi object nao -> goi duoc Person::isValidPhone(...)
    static bool isValidPhone(const string& phone);

    // PURE VIRTUAL (Chapter 5): moi loai nguoi tu quyet dinh cach hien thi.
    // "= 0" bien Person thanh lop truu tuong - khong tao object truc tiep.
    virtual void display() const = 0;
};
