#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "csv.h"
#include "utils.h"
#include "data.h"
#include <vector>
#include <string>
using namespace std;

void printSuperpowerDetail(Superpower& sp) {
    string clsStr;
    for (int j = 0; j < (int)sp.cls.size(); j++)
        clsStr += (j ? "|" : "") + sp.cls[j];

    vector<string> header = {"Field", "Value"};
    vector<vector<string>> rows = {
        {"ID",        to_string(sp.id)},
        {"Nama",      sp.name},
        {"Class",     clsStr},
        {"Category",  sp.category},
        {"Tribes",    sp.tribes},
        {"Cost",      (sp.cost     == -1 ? "-" : to_string(sp.cost))},
        {"Strength",  (sp.strength == -1 ? "-" : to_string(sp.strength))},
        {"Health",    (sp.health   == -1 ? "-" : to_string(sp.health))},
        {"Traits",    sp.traits},
        {"Effects",   sp.effects},
        {"Deskripsi", sp.desc},
        {"Signature", (sp.isSignature ? "Ya" : "Tidak")}
    };
    cout << "\n  DETAIL SUPERPOWER\n";
    printTable(header, rows);
}

void printCardDetail(Card& c) {
    string tribesStr, traitsStr, effectsStr;
    for (int j = 0; j < (int)c.tags.tribes.size(); j++)
        tribesStr += (j ? "|" : "") + c.tags.tribes[j];
    for (int j = 0; j < (int)c.tags.traits.size(); j++)
        traitsStr += (j ? "|" : "") + c.tags.traits[j];
    for (int j = 0; j < (int)c.tags.effects.size(); j++)
        effectsStr += (j ? "|" : "") + c.tags.effects[j];

    vector<string> header = {"Field", "Value"};
    vector<vector<string>> rows = {
        {"ID",        to_string(c.id)},
        {"Nama",      c.name},
        {"Team",      c.team},
        {"Class",     c.cardClass},
        {"Category",  c.category},
        {"Rarity",    c.rarity},
        {"Card Set",  c.cardSet},
        {"Cost",      (c.cost     == -1 ? "-" : to_string(c.cost))},
        {"Strength",  (c.strength == -1 ? "-" : to_string(c.strength))},
        {"Health",    (c.health   == -1 ? "-" : to_string(c.health))},
        {"Tribes",    (tribesStr.empty()  ? "-" : tribesStr)},
        {"Traits",    (traitsStr.empty()  ? "-" : traitsStr)},
        {"Effects",   (effectsStr.empty() ? "-" : effectsStr)},
        {"Deskripsi", (c.tags.desc.empty() ? "-" : c.tags.desc)}
    };
    cout << "\n  DETAIL KARTU\n";
    printTable(header, rows);
}

void allCardsReview() {
    vector<Card> plants  = loadCardCSV("plants.csv",  "plant");
    vector<Card> zombies = loadCardCSV("zombies.csv", "zombie");
    vector<Card> all = plants;
    all.insert(all.end(), zombies.begin(), zombies.end());

    if (all.empty()) {
        cout << "  Tidak ada kartu!\n";
        tungguEnter(); clear(); return;
    }

    while (true) {
        clear();
        cout << "  Daftar Kartu\n";
        vector<string> header = {"No", "Nama", "Team", "Class", "Cost", "Rarity"};
        vector<vector<string>> rows;
        for (auto& c : all)
            rows.push_back({
                to_string(c.id), c.name, c.team, c.cardClass,
                to_string(c.cost), c.rarity
            });
        printTable(header, rows);

        int pilih = readInt("  Pilih nomor untuk detail (0 = kembali): ");
        if (pilih == 0) return;

        bool ketemu = false;
        for (auto& c : all) {
            if (c.id == pilih) {
                clear();
                printCardDetail(c);
                tungguEnter();
                ketemu = true;
                break;
            }
        }
        if (!ketemu) cout << "  [!] Nomor tidak tersedia.\n";
    }
}

void superpowersReview() {
    vector<Superpower> sp = loadSuperpowerCSV("superpowers.csv");

    if (sp.empty()) {
        cout << "  Tidak ada superpower!\n";
        tungguEnter(); clear(); return;
    }

    while (true) {
        clear();
        cout << "  Daftar Superpower\n";
        vector<string> header = {"No", "Nama", "Class", "Category", "Cost", "Strength", "Health"};
        vector<vector<string>> rows;
        for (auto& s : sp) {
            string clsStr;
            for (int j = 0; j < (int)s.cls.size(); j++)
                clsStr += (j ? "|" : "") + s.cls[j];
            rows.push_back({
                to_string(s.id), s.name, clsStr, s.category,
                (s.cost     == -1 ? "-" : to_string(s.cost)),
                (s.strength == -1 ? "-" : to_string(s.strength)),
                (s.health   == -1 ? "-" : to_string(s.health))
            });
        }
        printTable(header, rows);

        int pilih = readInt("  Pilih nomor untuk detail (0 = kembali): ");
        if (pilih == 0) return;

        bool found = false;
        for (auto& s : sp) {
            if (s.id == pilih) {
                clear();
                printSuperpowerDetail(s);
                tungguEnter();
                found = true;
                break;
            }
        }
        if (!found) cout << "  [!] Nomor tidak tersedia.\n";
    }
}

void menuLihat() {
    while (true) {
        clear();
        string opsi[] = {"Non-superpower", "Superpower", "Kembali"};
        int pilihan = tampilMenu("Pilih jenis kartu:", opsi, 3);
        switch (pilihan) {
            case 1: allCardsReview();    break;
            case 2: superpowersReview(); break;
            case 3: return;
        }
    }
}

void menuTambah() {
    clear();
    string opsiTeam[] = {"Plant", "Zombie", "Kembali"};
    int pilihanTeam = tampilMenu("=== TAMBAH KARTU ===\nPilih tim:", opsiTeam, 3);
    if (pilihanTeam == 3) return;

    string filename = (pilihanTeam == 1) ? "plants.csv" : "zombies.csv";
    string team     = (pilihanTeam == 1) ? "plant"      : "zombie";

    vector<Card> cards = loadCardCSV(filename, team);

    Card c;
    c.id   = cards.empty() ? 1 : cards.back().id + 1;
    c.team = team;

    clear();
    cout << "=== TAMBAH KARTU " << (pilihanTeam == 1 ? "PLANT" : "ZOMBIE") << " ===\n";
    c.name = readString("  Nama: ");

    if (pilihanTeam == 1) {
        int pilihCls = tampilMenu("  Pilih Class:", PLANT_CLASS, 5);
        c.cardClass  = PLANT_CLASS[pilihCls - 1];
    } else {
        int pilihCls = tampilMenu("  Pilih Class:", ZOMBIE_CLASS, 5);
        c.cardClass  = ZOMBIE_CLASS[pilihCls - 1];
    }

    int pilihCat = tampilMenu("  Pilih Category:", CATEGORY, 3);
    c.category   = CATEGORY[pilihCat - 1];

    int pilihRar = tampilMenu("  Pilih Rarity:", RARITY, 6);
    c.rarity     = RARITY[pilihRar - 1];

    int pilihSet = tampilMenu("  Pilih Card Set:", CARD_SET, 5);
    c.cardSet    = CARD_SET[pilihSet - 1];

    c.cost     = readInt("  Cost     : ");
    c.strength = readInt("  Strength (-1 jika tidak ada): ");
    c.health   = readInt("  Health   (-1 jika tidak ada): ");

    if (pilihanTeam == 1)
        c.tags.tribes = tampilMenuMulti("  Pilih Tribes (0 = selesai):", PLANT_TRIBES, 20);
    else
        c.tags.tribes = tampilMenuMulti("  Pilih Tribes (0 = selesai):", ZOMBIE_TRIBES, 15);

    vector<string> traits;
    if (pilihanTeam == 1)
        traits = tampilMenuMulti("  Pilih Traits (0 = selesai):", PLANT_TRAITS, 2);
    else
        traits = tampilMenuMulti("  Pilih Traits (0 = selesai):", ZOMBIE_TRAITS, 4);
    vector<string> globalTraits = tampilMenuMulti("  Pilih Global Traits (0 = selesai):", GLOBAL_TRAITS, 8);
    traits.insert(traits.end(), globalTraits.begin(), globalTraits.end());
    c.tags.traits = traits;

    c.tags.effects = tampilMenuMulti("  Pilih Effects (0 = selesai):", EFFECTS, 15);

    c.tags.desc = readString("  Deskripsi (- jika tidak ada): ");
    if (c.tags.desc == "-") c.tags.desc = "";

    cards.push_back(c);
    saveCardCSV(filename, cards);

    clear();
    cout << "  [OK] Kartu berhasil ditambahkan!\n";
    tungguEnter();
}