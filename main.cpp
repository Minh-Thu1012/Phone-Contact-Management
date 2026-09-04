/*
    Main program for the Phone Contact Management Application.
    Provides the user menu and handles interaction with
    ContactManager to perform contact management operations.
*/

#include "ContactManager.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

static void clearInput() 
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() 
{
    cout << "\n=== QUAN LY DANH BA DIEN THOAI ===\n";
    cout << "1. Hien thi danh sach\n";
    cout << "2. Them lien he moi\n";
    cout << "3. Tim kiem theo ten\n";
    cout << "4. Cap nhat thong tin\n";
    cout << "5. Xoa lien he\n";
    cout << "6. Sap xep danh ba\n";
    cout << "7. Thong ke moi quan he\n";
    cout << "8. Loc theo moi quan he\n";
    cout << "0. Luu & Thoat\n";
    cout << "Chon chuc nang: ";
}

int main() 
{
    ContactManager mgr;
    const string FILE_NAME = "contacts.txt";
    if (mgr.loadFromFile(FILE_NAME)) {
        cout << "Da nap du lieu cu thanh cong.\n";
    }
    else 
    {
        cout << "Chua co file - bat dau danh ba rong.\n"; 
    }

    int choice;
    do 
    {
        printMenu();
        if (!(cin >> choice)) 
        {
            clearInput();
            cout << "Lua chon khong hop le! Vui long nhap so.\n";
            continue;
        }
        clearInput();
        switch (choice) 
        {
        case 1: 
        {
            cout << "\n--- DANH SACH LIEN HE ---\n";
            mgr.displayAll();
            break;
        }

        case 2: 
        {
            string name, phone, rel;
            cout << "Nhap ten: "; getline(cin, name);
            cout << "Nhap SDT: "; getline(cin, phone);
            if (!Person::isValidPhone(phone)) 
            {
                cout << "Loi: SDT phai tu 9-11 chu so!\n";
                break;
            }
            if (mgr.hasPhone(phone)) 
            {
                cout << "Loi: SDT nay da ton tai trong danh ba!\n";
                break;
            }
            if (mgr.countName(name) > 0) {
                cout << "Canh bao: Ten nay da ton tai. Van tiep tuc them? (y/n): ";
                char confirm;
                cin >> confirm;
                clearInput();
                if (confirm != 'y' && confirm != 'Y') 
                {
                    cout << "Da huy thao tac.\n";
                    break;
                }
            }
            cout << "Nhap moi quan he: "; getline(cin, rel);
            if (mgr.addContact(Contact(name, phone, rel))) {
                cout << "Them thanh cong!\n";
            }
            break;
        }

        case 3: 
        {
            string kw;
            cout << "Nhap ten can tim: "; getline(cin, kw);
            vector<Contact> res = mgr.searchByName(kw);
            cout << "\n--- KET QUA ---\n";
            printList(res);
            break;
        }

        case 4: 
        {
            string phone, newName, newRel;
            cout << "Nhap SDT cua lien he can sua: "; getline(cin, phone);
            if (!mgr.hasPhone(phone)) 
            {
                cout << "Khong tim thay SDT nay!\n";
                break;
            }
            cout << "Nhap ten moi (Nhan Enter de bo qua): "; getline(cin, newName);
            cout << "Nhap quan he moi (Nhan Enter de bo qua): "; getline(cin, newRel);
            if (mgr.updateByPhone(phone, newName, newRel)) cout << "Cap nhat thanh cong!\n";
            break;
        }

        case 5: 
        {
            string name;
            cout << "Nhap ten can xoa: "; getline(cin, name);
            int deleted = mgr.deleteByName(name);
            if (deleted > 0) cout << "Da xoa " << deleted << " lien he.\n";
            else cout << "Khong tim thay ten nay!\n";
            break;
        }

        case 6: 
        {
            cout << "Sap xep (1 = Tang dan theo ten, 2 = Giam dan): ";
            int sortType; cin >> sortType; clearInput();
            if (sortType == 1 || sortType == 2) 
            {
                mgr.sortByName(sortType == 1);
                cout << "Hoan tat sap xep. Nhan 1 de xem lai.\n";
            }
            else cout << "Lua chon khong hop le.\n";
            break;
        }

        case 7: 
        {
            cout << "\n--- THONG KE ---\n";
            map<string, int> stat = mgr.statistics();
            for (auto it = stat.begin(); it != stat.end(); ++it) 
            {
                cout << it->first << ": " << it->second << " nguoi\n";
            }
            break;
        }

        case 8:
        {
            string relationship;

            cout << "Nhap moi quan he can loc: ";
            getline(cin, relationship);

            vector<Contact> result = mgr.filterByRelationship(relationship);

            cout << "\n--- DANH SACH THEO MOI QUAN HE ---\n";
            printList(result);

            break;
        }

        case 0: 
        {
            mgr.saveToFile(FILE_NAME);
            cout << "Da luu " << FILE_NAME << ". Tam biet!\n";
            break;
        }
        default: cout << "Khong hop le!\n"; break;
        }
    }

    while (choice != 0);

    return 0;
}