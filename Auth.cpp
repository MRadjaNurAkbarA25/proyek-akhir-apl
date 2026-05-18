#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "auth.h"
#include "data.h"
#include "menuAdmin.h"
#include "menuPlayer.h"
#include <fstream>
#include <sstream>

extern vector<Card>  plantCards;
extern vector<Card>  zombieCards;
extern vector<Hero>  heroes;
extern vector<Deck>  decks;

vector<Akun> List_Akun;

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
            if (akun.Username == Input_Username && akun.Password == Input_Pw ) {
                Ketemu = true;
                cout << "\n Login Berhasil ! Role : " << akun.Role << endl;
                system("pause");

                if (akun.Role == "admin") {
                    pilihanAdmin();
                } else {
                    pilihanPlayer(decks, heroes, plantCards, zombieCards, akun.ID);
                }

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

void Simpan_Akun(const string& filename, const vector<Akun>& Regis_Akun) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "[!] Gagal membuka file ! " << filename << " untuk menyimpan.\n"; 
        return;
    }

    file << "id, username, password, role\n";

        for (int i = 0; i < (int)Regis_Akun.size(); i++) {
            const Akun& acc = Regis_Akun[i];

        file << acc.ID << ","
            << acc.Username << ","
            << acc.Password << ","
            << acc.Role << "\n";
        }

        cout << "Registrasi berhasil ! " << endl;

    file.close();
}

bool Is_Alpha_Numeric(string str) {
    for (char c : str) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

void Sign_In () {
    string New_User, New_Pw;
    bool Ada = false;
    
    system("cls");                         
    
    cout << "=================================== " << endl;
    cout << "         Menu Sign In " << endl;
    cout << "===================================  " << endl;
    cout << "Username Baru : " << endl;
    getline(cin, New_User);
    cout << "Password Baru : " << endl;
    getline(cin, New_Pw);

    if (!Is_Alpha_Numeric(New_User) || !Is_Alpha_Numeric(New_Pw)) {
        cout << "\n [!] Inputan tidak boleh simbol ! \n ";
        system("pause");
        return;
    }
    
    if (New_User.empty() || New_Pw.empty()) {
        cout << "\n [!] Inputan tidak boleh kosong ! \n ";
        system("pause");
        return;
    }


    for (const auto& akun : List_Akun) {
        if (akun.Username == New_User ) {
            Ada = true; 
            break;
        }
    }

    if (Ada) {
        cout << "\n [!] Username sudah ada !" << endl;
        system("pause");

    } else {
        Akun Baru;
        Baru.ID = List_Akun.size() + 1;
        Baru.Username = New_User;
        Baru.Password = New_Pw;
        Baru.Role = "player";

        List_Akun.push_back(Baru);
        Simpan_Akun("accounts.csv", List_Akun);
        system("pause");
    }
}



