#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "clearscreen.h"

using namespace std;

const int MAX_CARDS = 200;
const int MAX_STR   = 150;

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
    int  cost;
};

// ─── Utility ─────────────────────────────────────────────────────────────────

void trimStr(char* s) {
    int start = 0;
    while (s[start] == ' ' || s[start] == '\t') start++;
    if (start > 0) {
        int i = 0;
        while (s[start + i] != '\0') { s[i] = s[start + i]; i++; }
        s[i] = '\0';
    }
    int end = (int)strlen(s) - 1;
    while (end >= 0 && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n')) {
        s[end] = '\0'; end--;
    }
}

int parseCSVLine(char* line, char fields[][MAX_STR], int maxFields) {
    int  fieldIdx = 0, charIdx = 0;
    bool inQuotes = false;
    for (int i = 0; line[i] != '\0' && fieldIdx < maxFields; i++) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            fields[fieldIdx][charIdx] = '\0';
            trimStr(fields[fieldIdx]);
            fieldIdx++; charIdx = 0;
        } else {
            if (charIdx < MAX_STR - 1) fields[fieldIdx][charIdx++] = c;
        }
    }
    fields[fieldIdx][charIdx] = '\0';
    trimStr(fields[fieldIdx]);
    return fieldIdx + 1;
}

int readInt(const char* prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) { cin.ignore(1000, '\n'); return val; }
        cin.clear(); cin.ignore(1000, '\n');
        cout << "  [!] Input harus berupa angka. Coba lagi.\n";
    }
}

// ─── CSV Load ────────────────────────────────────────────────────────────────

// Expected header: name, class, category, tribes, strength, health, traits, effects, desc, isSignature, cost
int loadCSV(const char* filename, Superpower cards[], int maxCards) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  [ERROR] Tidak bisa membuka file: " << filename << "\n";
        return 0;
    }
    char line[2048];
    file.getline(line, 2048); // skip header
    int count = 0;
    while (file.getline(line, 2048) && count < maxCards) {
        if (strlen(line) == 0) continue;
        char fields[12][MAX_STR];
        int n = parseCSVLine(line, fields, 12);
        if (n < 11) continue;
        cards[count].id          = count + 1;          // auto-assign sequential ID
        strcpy(cards[count].name,     fields[0]);
        strcpy(cards[count].cls,      fields[1]);
        strcpy(cards[count].category, fields[2]);
        strcpy(cards[count].tribes,   fields[3]);
        cards[count].strength = (strcmp(fields[4], "-") == 0 ? -1 : atoi(fields[4]));
        cards[count].health   = (strcmp(fields[5], "-") == 0 ? -1 : atoi(fields[5]));
        strcpy(cards[count].traits,   fields[6]);
        strcpy(cards[count].effects,  fields[7]);
        strcpy(cards[count].desc,     fields[8]);
        cards[count].isSignature = atoi(fields[9]);
        cards[count].cost     = (n > 10 && strcmp(fields[10], "-") != 0 ? atoi(fields[10]) : -1);
        count++;
    }
    file.close();
    return count;
}

// ─── Display ─────────────────────────────────────────────────────────────────

void printCardList(Superpower cards[], int count) {
    if (count == 0) { cout << "  (Tidak ada kartu)\n"; return; }
    cout << "\n";
    cout << "  +-------+--------------------------------+-------------------+\n";
    cout << "  | No.   | Nama Kartu                     | Class             |\n";
    cout << "  +-------+--------------------------------+-------------------+\n";
    for (int i = 0; i < count; i++) {
        char noStr[10]; sprintf(noStr, "%d", cards[i].id);
        cout << "  | " << noStr;
        for (int s = strlen(noStr); s < 6; s++) cout << " ";
        cout << "| " << cards[i].name;
        int nl = strlen(cards[i].name);
        for (int s = nl; s < 31; s++) cout << " ";
        cout << " | " << cards[i].cls;
        int cl = strlen(cards[i].cls);
        for (int s = cl; s < 18; s++) cout << " ";
        cout << "|\n";
    }
    cout << "  +-------+--------------------------------+-------------------+\n";
}

void printCardDetail(Superpower* sp) {
    cout << "\n";
    cout << "  ============================================\n";
    cout << "    DETAIL SUPERPOWER #" << sp->id << "\n";
    cout << "  ============================================\n";
    cout << "    Nama       : " << sp->name     << "\n";
    cout << "    Class      : " << sp->cls      << "\n";
    cout << "    Cost       : " << (sp->cost == -1 ? "-" : to_string(sp->cost)) << "\n";
    cout << "    Category   : " << sp->category << "\n";
    cout << "    Tribes     : " << sp->tribes   << "\n";
    cout << "    Strength   : " << (sp->strength == -1 ? "-" : to_string(sp->strength)) << "\n";
    cout << "    Health     : " << (sp->health   == -1 ? "-" : to_string(sp->health))   << "\n";
    cout << "    Traits     : " << sp->traits   << "\n";
    cout << "    Effects    : " << sp->effects  << "\n";
    cout << "    Deskripsi  : " << sp->desc     << "\n";
    cout << "    Signature  : " << (sp->isSignature ? "Ya" : "Tidak") << "\n";
    cout << "  ============================================\n";
}

int searchByID(Superpower cards[], int count, int id) {
    for (int i = 0; i < count; i++)
        if (cards[i].id == id) return i;
    return -1;
}

// ─── Menu ─────────────────────────────────────────────────────────────────────

void menuLihatSP(Superpower cards[], int count) {
    clearScreen();
    cout << "\n  ==============================\n";
    cout << "       DAFTAR SUPERPOWER\n";
    cout << "  ==============================\n";
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

// ─── Main ─────────────────────────────────────────────────────────────────────

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
        cout << "  |     KATALOG KARTU SUPERPOWER     |\n";
        cout << "  +----------------------------------+\n";
        cout << "  |  1. Lihat Daftar Superpower      |\n";
        cout << "  |  2. Keluar                       |\n";
        cout << "  +----------------------------------+\n";
        int menu = readInt("\n  Pilih menu (1-2): ");

        switch (menu) {
            case 1: menuLihatSP(cards, count); break;
            case 2:
                clearScreen();
                cout << "\n  Terima kasih. Program selesai.\n\n";
                return 0;
            default:
                cout << "\n  [!] Pilihan tidak tersedia. Masukkan angka 1-2.\n";
                cout << "  Tekan Enter untuk melanjutkan..."; cin.get();
        }
    }
}