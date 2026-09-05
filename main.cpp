// ============================================================
// main.cpp - CHI lo giao dien menu (UI).
// Moi logic du lieu nam trong ContactManager -> tach bach ro rang.
// ============================================================
#include "ContactManager.h"
#include <limits>

// don sach bo dem sau khi cin >> so, truoc khi getline chuoi
static void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void menu() {
    cout << "\n===== QUAN LY DANH BA =====" << endl;
    cout << "1. Hien thi danh ba" << endl;
    cout << "2. Them lien he" << endl;
    cout << "3. Tim theo ten" << endl;
    cout << "4. Cap nhat theo sdt" << endl;
    cout << "5. Xoa theo ten" << endl;
    cout << "6. Loc theo quan he" << endl;
    cout << "7. Sap xep theo ten" << endl;
    cout << "8. Thong ke theo quan he" << endl;
    cout << "9. Luu ra file" << endl;
    cout << "0. Thoat" << endl;
    cout << "Chon: ";
}

int main() {
    ContactManager mgr;
    const string FILE_NAME = "contacts.txt";

    if (mgr.loadFromFile(FILE_NAME))
        cout << "Da nap " << mgr.size() << " lien he tu " << FILE_NAME << endl;
    else
        cout << "Chua co file " << FILE_NAME << " - bat dau danh ba rong." << endl;

    int choice;
    do {
        menu();
        cin >> choice;
        clearInput();

        switch (choice) {
        case 1:
            mgr.displayAll();
            cout << "Tong so (static count): " << Contact::getCount() << endl;
            break;

        case 2: {
            string name, phone, rel;
            cout << "Ten: ";        getline(cin, name);
            cout << "Sdt: ";        getline(cin, phone);
            cout << "Quan he: ";    getline(cin, rel);

            if (!Person::isValidPhone(phone)) {          // validate dau vao
                cout << "Sdt khong hop le (9-11 chu so)!" << endl;
                break;
            }
            if (mgr.hasPhone(phone)) {                   // chan TRUNG SDT
                cout << "Sdt da ton tai - khong them!" << endl;
                break;
            }
            int trung = mgr.countName(name);             // xu ly TRUNG TEN
            if (trung > 0) {
                cout << "Da co " << trung << " lien he ten nay. Van them? (y/n): ";
                char ok; cin >> ok; clearInput();
                if (ok != 'y' && ok != 'Y') break;
            }
            mgr.addContact(Contact(name, phone, rel));
            cout << "Da them." << endl;
            break;
        }

        case 3: {
            string kw;
            cout << "Nhap ten (gan dung): ";
            getline(cin, kw);
            printList(mgr.searchByName(kw));             // ham TEMPLATE
            break;
        }

        case 4: {
            string phone, name, rel;
            cout << "Sdt can cap nhat: "; getline(cin, phone);
            cout << "Ten moi (Enter = giu nguyen): ";     getline(cin, name);
            cout << "Quan he moi (Enter = giu nguyen): "; getline(cin, rel);
            cout << (mgr.updateByPhone(phone, name, rel)
                     ? "Da cap nhat." : "Khong tim thay sdt nay!") << endl;
            break;
        }

        case 5: {
            string name;
            cout << "Ten can xoa: ";
            getline(cin, name);
            int daXoa = mgr.deleteByName(name);
            cout << "Da xoa " << daXoa << " lien he." << endl;
            break;
        }

        case 6: {
            string rel;
            cout << "Quan he can loc (family/friend/teacher/colleague...): ";
            getline(cin, rel);
            printList(mgr.filterByRelationship(rel));
            break;
        }

        case 7: {
            char c;
            cout << "Tang dan (t) hay giam dan (g)? ";
            cin >> c; clearInput();
            mgr.sortByName(c == 't' || c == 'T');
            mgr.displayAll();
            break;
        }

        case 8: {
            map<string, int> stat = mgr.statistics();
            for (map<string, int>::iterator it = stat.begin(); it != stat.end(); ++it)
                cout << it->first << ": " << it->second << " lien he" << endl;
            break;
        }

        case 9:
            cout << (mgr.saveToFile(FILE_NAME)
                     ? "Da luu vao " + FILE_NAME : "Loi ghi file!") << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
