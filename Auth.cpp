#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Auth.h"
#include <fstream>
#include <sstream>

string Trim(string s) {
    if (s.empty()) return s;
    s.erase(0, s.find_first_not_of(" "));
    s.erase(0, s.find_last_not_of(" ") + 1);
    return s;
}

int Muat_Akun() {
    ifstream file("accounts.csv");

    if (!file.is_open()) {
        cout << "  [!] File accounts.csv tidak ditemukan.\n";
        return 0;
        }

    string baris;
    getline(file, baris);
    int jumlah = 0;

    while (getline(file, baris) && jumlah < 300) {
        if (baris.empty())
            continue;
        if (!baris.empty() && baris.back() == '\r')
            baris.pop_back();

        stringstream parser(baris);
        string id, username, pw, role;
        getline(parser, id, ',');
        getline(parser, username, ',');
        getline(parser, pw, ',');
        getline(parser, role, ',');

        try {
            if (!id.empty()) {
                Akun acc_baru;
                acc_baru.ID = stoi(Trim(id));
                acc_baru.Username = Trim(username);
                acc_baru.Password  = Trim(pw);
                acc_baru.Role = Trim(role);

                List_Akun.push_back(acc_baru);
                jumlah++;
                }
            } catch (const exception& e) {
                continue;
            }
        }

    file.close();
    return jumlah;
}

void Login () {
    bool Ketemu = false;
    string Pilihan;

    system("cls");                         
    while (true) {
        cout << "=================================== " << endl;
        cout << "          Menu Login " << endl;
        cout << "===================================  " << endl;
        cout << "Username : " << endl;
        cin >> Input_Username;
        cout << "Password : " << endl;
        cin >> Input_Pw;


        for (const auto& akun : List_Akun) {
            if (akun.Username == Input_Username && akun.Password == Input_Pw ) {
                Ketemu = true;
                cout << "\n Login Berhasil ! Role : " << akun.Role << endl;
                system("pause");
                return;

            }
        }

        if (!Ketemu) {
            cout << "\n Username atau Password Salah !" << endl;
            cout << "Coba lagi ? (y/n) ";
            system("cls");  
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


        for (const auto& akun : List_Akun) {
            if (akun.Username == New_User ) {
                cout << "Username sudah ada !" << endl;
                Ada = true;
                system("pause");
                break;

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
        
    }  
