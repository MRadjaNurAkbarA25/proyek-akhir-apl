#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Auth.h"
#include "data.h"
#include <fstream>
#include <sstream>

string Trim(string s) {
    if (s.empty()) return s;
    size_t first = s.find_first_not_of(" \t\r\n");

    if (first == string :: npos) return "";

    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, (last - first + 1));
}

int Muat_Akun() {
    ifstream file("accounts.csv");

    if (!file.is_open()) {
        cout << "  [!] File accounts.csv tidak ditemukan.\n";
        system("pause");
        return 0;
        }

    string baris;
    getline(file, baris);
    List_Akun.clear();

    while (getline(file, baris)) {
        if (baris.empty()) continue;

        stringstream parser(baris);
        string id, username, pw, role;
        getline(parser, id, ',');
        getline(parser, username, ',');
        getline(parser, pw, ',');
        getline(parser, role, ',');

        if (!id.empty()) {
            try {
                Akun acc_baru;
                acc_baru.ID = stoi(Trim(id));
                acc_baru.Username = Trim(username);
                acc_baru.Password  = Trim(pw);
                acc_baru.Role = Trim(role);
                List_Akun.push_back(acc_baru);

                } catch (const exception& e) {
                continue;
            } 
            }
        }

    file.close();
    return List_Akun.size();
}

void Login () {
    string Pilihan;

    while (true) {
        bool Ketemu = false;
        system("cls");  
        cout << "=================================== " << endl;
        cout << "          Menu Login " << endl;
        cout << "===================================  " << endl;
        cout << "Username : " << endl;
        cin >> Input_Username;
        cout << "Password : " << endl;
        cin >> Input_Pw;
        cin.ignore(1000, '\n');


        for (const auto& akun : List_Akun) {
            if (akun.Username == Trim(Input_Username) && akun.Password == Trim(Input_Pw) ) {
                Ketemu = true;
                cout << "\n Login Berhasil ! Role : " << akun.Role << endl;
                system("pause");
                return;

            }
        }

        if (!Ketemu) {
            system("cls");  
            cout << "\n Username atau Password Salah !" << endl;
            cout << "Coba lagi ? (y/n) ";
            cin >> Pilihan;

            if (Pilihan != "y") break;

        }
        
    }  
}

void Sign_In () {
    string New_User, New_Pw;
    bool Ada = false;
    
    system("cls");                         
    
        cout << "=================================== " << endl;
        cout << "         Menu Sign In " << endl;
        cout << "===================================  " << endl;
        cout << "Username Baru : " << endl;
        cin >> New_User;
        cout << "Password Baru : " << endl;
        cin >> New_Pw;
        cin.ignore(1000, '\n');


        for (const auto& akun : List_Akun) {
            if (akun.Username == New_User ) {
                Ada = true; 
                break;
            }
        }

            if (Ada) {
                cout << "Username sudah ada !" << endl;
                system("pause");

            } else {
                Akun Baru;
                Baru.ID = List_Akun.size() + 1;
                Baru.Username = New_User;
                Baru.Password = New_Pw;
                Baru.Role = "player";

                List_Akun.push_back(Baru);
                cout << "Registrasi Berhasil !" << endl;
                system("pause");
            }

            
        }
