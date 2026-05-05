#include <iostream>
#include "crudCard2.h"
#include "utils.h"
using namespace std;

void pilihanAdmin() {
    while (true) {
        clear();
        string opsi[] = {"Lihat kartu","Buat kartu","Edit kartu",
                        "Hapus kartu","Cari kartu","Kembali"};
        int pilihan = tampilMenu("=== MENU ADMIN ===", opsi, 6);
        switch(pilihan) {
            case 1: menuLihat();                          break;
            case 2: menuTambah();                         break;
            case 3: menuUpdate();                         break;
            case 4: menuDelete();                         break;
            case 5: /* menuCari()   - belum ada */        break;
            case 6: return;
        }
    }
}