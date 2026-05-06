#include <iostream>
#include "crudDeck.h"
#include "utils.h"
#include "data.h"
#include "crudCard2.h"
using namespace std;

void pilihanPlayer(vector<Deck>& decks, vector<Hero>& heroes,
                 vector<Card>& plants, vector<Card>& zombies,
                 int ownerId) {
    while (true) {
        clear();
        string opsi[] = {
            "Lihat dek",
            "Buat dek",
            "Edit dek",
            "Hapus dek",
            "Lihat kartu",
            "Kembali"
        };
        int pilihan = tampilMenu("=== MENU PLAYER ===", opsi, 6);
        switch (pilihan) {
            case 1: lihatDek(decks, heroes, plants, zombies, ownerId); break;
            case 2: tambahDek(decks, heroes, plants, zombies, ownerId); break;
            case 3: {
                cout << "jalan\n";
                editDek(decks, heroes, plants, zombies, ownerId);
                decks = loadDeckCSV("deck.csv");
                loadDeckCardsCSV("deckCard.csv", decks);
                tungguEnter();
                break;
            }
            case 4: {
                cout << "jalan\n";
                hapusDek(decks, ownerId);
                decks = loadDeckCSV("deck.csv");
                loadDeckCardsCSV("deckCard.csv", decks);
                tungguEnter();
                break;
            }
            case 5: menuLihat(); break;
            case 6: return;
        }
    }
}