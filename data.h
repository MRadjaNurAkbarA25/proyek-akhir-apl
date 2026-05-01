#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

struct Akun {
    int ID;
    string Username;
    string Password;
    string Role;
};

extern vector<Akun> List_Akun;
extern bool Menu_Login;
extern string Input_Username;
extern string Input_Pw;
extern int Pilihan_Login;

#endif