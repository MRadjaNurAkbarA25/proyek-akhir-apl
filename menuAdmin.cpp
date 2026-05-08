#include <iostream>
#include "crudCard2.h"
#include "utils.h"
#include "data.h"
using namespace std;

void pilihanAdmin() {
    while (true) {
        clear();
        string opsi[] = {"Lihat kartu","Buat kartu","Edit kartu",
                        "Hapus kartu","Cari kartu","Log-out"};
        int pilihan = tampilMenu("=== MENU ADMIN ===", opsi, 6);
        switch(pilihan) {
            case 1: menuLihat();                          break;
            case 2: menuTambah();                         break;
            case 3: menuUpdate();                         break;
            case 4: menuDelete();                         break;
            case 5: menuSearch();                         break;
            case 6: return;
        }
    }
}