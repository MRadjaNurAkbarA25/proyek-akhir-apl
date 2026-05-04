#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "clearscreen.h"

using namespace std;
const int MAX_CARDS = 200;
const int MAX_STR   = 100;
struct Superpower {
    int  id;
    char name[MAX_STR];
    char cls[MAX_STR];
    char category[MAX_STR];
    char tribes[MAX_STR];
    int  strength;
    int  health;
    char traits[MAX_STR];
    char effects[MAX_STR];
    char desc[MAX_STR];
    int  isSignature;
};

void trimStr(char* s) {
    int start = 0;
    while (s[start] == ' ' || s[start] == '\t') start++;
    if (start > 0) {
        int i = 0;
        while (s[start + i] != '\0') {
            s[i] = s[start + i];
            i++;
        }
        s[i] = '\0';
    }
    int end = strlen(s) - 1;
    while (end >= 0 && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n')) {
        s[end] = '\0';
        end--;
    }
}

int parseCSVLine(char* line, char fields[][MAX_STR], int maxFields) {
    int  fieldIdx = 0;
    int  charIdx  = 0;
    bool inQuotes = false;
    for (int i = 0; line[i] != '\0' && fieldIdx < maxFields; i++) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            fields[fieldIdx][charIdx] = '\0';
            trimStr(fields[fieldIdx]);
            fieldIdx++;
            charIdx = 0;
        } else {
            if (charIdx < MAX_STR - 1) {
                fields[fieldIdx][charIdx] = c;
                charIdx++;
            }
        }
    }
    fields[fieldIdx][charIdx] = '\0';
    trimStr(fields[fieldIdx]);
    fieldIdx++;
    return fieldIdx;
}

int loadCSV(const char* filename, Superpower cards[], int maxCards) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  [ERROR] Tidak bisa membuka file: " << filename << "\n";
        return 0;
    }
    char line[1024];
    file.getline(line, 1024);
    int count = 0;
    while (file.getline(line, 1024) && count < maxCards) {
        if (strlen(line) == 0) continue;
        char fields[11][MAX_STR];
        int n = parseCSVLine(line, fields, 11);
        if (n < 11) continue;
        cards[count].id          = atoi(fields[0]);
        strcpy(cards[count].name,     fields[1]);
        strcpy(cards[count].cls,      fields[2]);
        strcpy(cards[count].category, fields[3]);
        strcpy(cards[count].tribes,   fields[4]);
        cards[count].strength    = (strcmp(fields[5], "-") == 0 ? -1 : atoi(fields[5]));
        cards[count].health      = (strcmp(fields[6], "-") == 0 ? -1 : atoi(fields[6]));
        strcpy(cards[count].traits,   fields[7]);
        strcpy(cards[count].effects,  fields[8]);
        strcpy(cards[count].desc,     fields[9]);
        cards[count].isSignature = atoi(fields[10]);
        count++;
    }
    file.close();
    return count;
}

void saveCSV(const char* filename, Superpower cards[], int count) {
    ofstream file(filename);
    file << "id, name, class, category, tribes, strength, health, traits, effects, desc, isSignature\n";
    for (int i = 0; i < count; i++) {
        file << cards[i].id          << ", "
            << cards[i].name        << ", "
            << cards[i].cls         << ", "
            << cards[i].category    << ", "
            << cards[i].tribes      << ", "
            << (cards[i].strength == -1 ? "-" : to_string(cards[i].strength)) << ", "
            << (cards[i].health   == -1 ? "-" : to_string(cards[i].health))   << ", "
            << cards[i].traits      << ", "
            << cards[i].effects     << ", "
            << cards[i].desc        << ", "
            << cards[i].isSignature << "\n";
    }
    file.close();
}

void reassignIDs(Superpower cards[], int count) {
    for (int i = 0; i < count; i++)
        cards[i].id = i + 1;
}

int readInt(const char* prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(1000, '\n');
            return val;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  [!] Input harus berupa angka. Coba lagi.\n";
    }
}

void readString(const char* prompt, char* dest) {
    while (true) {
        cout << prompt;
        cin.getline(dest, MAX_STR);
        trimStr(dest);
        if (strlen(dest) > 0) return;
        cout << "  [!] Input tidak boleh kosong. Coba lagi.\n";
    }
}

int searchByID(Superpower cards[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (cards[i].id == id) return i;
    }
    return -1;
}

void printCardList(Superpower cards[], int count) {
    if (count == 0) {
        cout << "  (Tidak ada kartu)\n";
        return;
    }
    cout << "\n";
    cout << "  +-------+--------------------------------+\n";
    cout << "  | No.   | Nama Kartu                     |\n";
    cout << "  +-------+--------------------------------+\n";
    for (int i = 0; i < count; i++) {
        char noStr[10];
        sprintf(noStr, "%d", cards[i].id);
        cout << "  | " << noStr;
        for (int s = strlen(noStr); s < 6; s++) cout << " ";
        cout << "| " << cards[i].name;
        int nameLen = strlen(cards[i].name);
        for (int s = nameLen; s < 31; s++) cout << " ";
        cout << " |\n";
    }
    cout << "  +-------+--------------------------------+\n";
}

void printCardDetail(Superpower* sp) {
    cout << "\n";
    cout << "  ------------------------------------------\n";
    cout << "    DETAIL KARTU #" << sp->id << "\n";
    cout << "  ------------------------------------------\n";
    cout << "    Nama       : " << sp->name     << "\n";
    cout << "    Class      : " << sp->cls      << "\n";
    cout << "    Cost       : " << sp->cost     << "\n"; 
    cout << "    Category   : " << sp->category << "\n";
    cout << "    Tribes     : " << sp->tribes   << "\n";
    cout << "    Strength   : " << (sp->strength == -1 ? "-" : to_string(sp->strength)) << "\n";
    cout << "    Health     : " << (sp->health   == -1 ? "-" : to_string(sp->health))   << "\n";
    cout << "    Traits     : " << sp->traits   << "\n";
    cout << "    Effects    : " << sp->effects  << "\n";
    cout << "    Deskripsi  : " << sp->desc     << "\n";
    cout << "    Signature  : " << (sp->isSignature ? "Ya" : "Tidak") << "\n";
    cout << "  ------------------------------------------\n";
}

void menuLihat(Superpower cards[], int count) {
    clearScreen();
    cout << "\n  ------------------------------\n";
    cout << "        LIHAT KARTU\n";
    cout << "  ------------------------------\n";
    printCardList(cards, count);

    while (true) {
        int pilih = readInt("\n  Masukkan nomor kartu untuk melihat detail (0 = kembali): ");
        if (pilih == 0) return;

        int idx = searchByID(cards, count, pilih);
        if (idx == -1) {
            cout << "  [!] Nomor kartu tidak tersedia. Coba lagi.\n";
        } else {
            clearScreen();
            printCardDetail(&cards[idx]);
        }
    }
}

void menuTambah(Superpower cards[], int* count, const char* filename) {
    if (*count >= MAX_CARDS) {
        cout << "  [!] Data sudah penuh, tidak bisa menambah kartu.\n";
        return;
    }
    clearScreen();
    cout << "\n  ------------------------------\n";
    cout << "        TAMBAH KARTU\n";
    cout << "  ------------------------------\n";
    Superpower* sp = &cards[*count];
    sp->id = (*count == 0) ? 1 : cards[*count - 1].id + 1;
    readString("  Nama        : ", sp->name);
    readString("  Class       : ", sp->cls);
    readString("  Category    : ", sp->category);
    readString("  Tribes (- jika tidak ada): ", sp->tribes);
    sp->strength = readInt("  Strength (-1 jika tidak ada): ");
    sp->health   = readInt("  Health   (-1 jika tidak ada): ");
    readString("  Traits   (- jika tidak ada): ", sp->traits);
    readString("  Effects  (- jika tidak ada): ", sp->effects);
    readString("  Deskripsi   : ", sp->desc);
    sp->isSignature = 0;
    (*count)++;
    saveCSV(filename, cards, *count);
    clearScreen();
    cout << "\n  [OK] Kartu berhasil ditambahkan!\n";
    cout << "\n  ------------------------------\n";
    cout << "        DAFTAR KARTU TERBARU\n";
    cout << "  ------------------------------\n";
    printCardList(cards, *count);
    cout << "\n  Tekan Enter untuk kembali ke menu...";
    cin.get();
}

void menuUbah(Superpower cards[], int count, const char* filename) {
    clearScreen();
    cout << "\n  ------------------------------\n";
    cout << "        UBAH KARTU\n";
    cout << "  ------------------------------\n";
    printCardList(cards, count);
}
int main() {
    const char* filename = "superpowers.csv";
    Superpower cards[MAX_CARDS];
    int count = loadCSV(filename, cards, MAX_CARDS);
    if (count == 0) {
        cout << "\n  [!] Data tidak ditemukan atau file kosong.\n";
        cout << "  Pastikan '" << filename << "' ada di direktori yang sama.\n\n";
        return 1;
    }
    while (true) {
        clearScreen();
        cout << "\n";
        cout << "  +----------------------------------+\n";
        cout << "  |   MANAJEMEN KARTU SUPERPOWER     |\n";
        cout << "  +----------------------------------+\n";
        cout << "  |  1. Lihat Kartu                  |\n";
        cout << "  |  2. Tambah Kartu                 |\n";
        cout << "  |  3. Ubah Kartu                   |\n";
        cout << "  |  4. Hapus Kartu                  |\n";
        cout << "  |  5. Keluar                       |\n";
        cout << "  +----------------------------------+\n";
        int menu = readInt("\n  Pilih menu (1-5): ");
        switch (menu) {
            case 1: menuLihat(cards, count);               break;
            case 2: menuTambah(cards, &count, filename);   break;
            case 5:
                clearScreen();
                cout << "\n  Terima kasih. Program selesai.\n\n";
                return 0;
            default:
                cout << "\n  [!] Pilihan tidak tersedia. Masukkan angka 1-5.\n";
                cout << "  Tekan Enter untuk melanjutkan...";
                cin.get();
        }
    }
}