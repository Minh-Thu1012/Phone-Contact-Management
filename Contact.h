#pragma once
#include "Person.h"

// ============================================================
// Contact - KE THUA public tu Person (Chapter 4)
// "Contact IS-A Person": danh ba luu nguoi + moi quan he.
// public inheritance: giu nguyen giao dien cua Person
// (getName/getPhone van public voi ben ngoai).
// ============================================================
class Contact : public Person {
private:
    // private (KHONG phai protected): hien tai KHONG co lop nao
    // ke thua Contact can dung truc tiep relationship.
    // Nguyen tac: dong nhat co the, chi mo (protected) khi that su can.
    string relationship;

    // static (Chapter 2): MOT bien duy nhat dem so Contact dang ton tai,
    // dung chung cho ca lop - khong cua rieng object nao.
    static int count;

public:
    Contact(string name = "", string phone = "", string relationship = "unknown");
    Contact(const Contact& other);   // copy constructor: vector copy phan tu -> phai ++count o day nua
    ~Contact();                      // --count khi object bi huy

    string getRelationship() const;
    void setRelationship(const string& relationship);

    // static function: goi khong can object -> Contact::getCount()
    static int getCount();

    // OVERRIDE ham pure virtual cua Person (Chapter 5).
    // override: nho compiler KIEM TRA chu ky khop voi lop cha.
    void display() const override;

    // ----- Operator overloading (Chapter 3) -----
    // == theo SDT: sdt la dinh danh duy nhat cua contact
    bool operator==(const Contact& other) const;
    // < va > theo TEN: phuc vu sort() tang/giam theo ten
    bool operator<(const Contact& other) const;
    bool operator>(const Contact& other) const;

    // << >> la FRIEND (non-member) vi ve trai la stream, khong phai Contact.
    // friend: cho phep 2 ham ngoai nay doc thanh vien private/protected.
    friend istream& operator>>(istream& in, Contact& c);          // doc 1 dong "ten,sdt,quanhe"
    friend ostream& operator<<(ostream& out, const Contact& c);   // ghi ra man hinh / file
};
