#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "auth.h"
#include "data.h"
#include "menuAdmin.h"
#include "menuUser.h"
#include <fstream>
#include <sstream>

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
                    pilihanUser();
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
