#include <iostream>
#include "crudCard2.h"
#include "utils.h"
#include "data.h"
using namespace std;

void pilihanUser() {
    while (true) {
        clear();
        string opsi[] = {"Lihat kartu","Buat kartu","Edit kartu",
                        "Hapus kartu","Cari kartu","Kembali"};
        int pilihan = tampilMenu("=== MENU User ===", opsi, 6);
        switch(pilihan) {
            case 1:                           break;
            case 2:                         break;
            case 3:                        break;
            case 4:                         break;
            case 5: /* menuCari()   - belum ada */        break;
            case 6: return;
        }
    }
}