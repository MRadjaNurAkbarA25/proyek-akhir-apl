#include <iostream>    
#include <fstream>     
#include <sstream>     
#include <string>      
#include <vector>      
#include <algorithm>   
#include <iomanip>     
#include <limits>      
#include <stdexcept>   
#include <string>
using namespace std;

#include "data.h"
#include "auth.h"
#include "csv.h"
#include "utils.h"

bool Menu_Login = false;
string Input_Username;
string Input_Pw;
string Program_Jalan = "y";
int Pilihan_Login;

vector<Card>  plantCards;
vector<Card>  zombieCards;
vector<Hero>  heroes;
vector<Deck>  decks;
vector<Superpower> superpowers;

int main () {
    int Jumlah = Muat_Akun();
    plantCards  = loadCardCSV("plants.csv", "plant");
    zombieCards = loadCardCSV("zombies.csv", "zombie");
    heroes      = loadHeroCSV("heroes.csv");
    superpowers = loadSuperpowerCSV("superpowers.csv");
    decks       = loadDeckCSV("deck.csv");
    loadDeckCardsCSV("deckCard.csv", decks);

    if (Jumlah == 0) {
        cout << "  [!] Tidak ada data akun yang di-load!\n";
        system("pause");
    }

    while (Program_Jalan == "y") {
        system("cls");

        const string opsi[] = {"Login", "Sign In", "Exit"};

        try {
            Pilihan_Login = tampilMenu("=== Plants vs Zombies Heroes — Deck Builder System ===", opsi, 3);

            switch (Pilihan_Login) {
                case 1:
                    Login();
                    break;

                case 2:
                    Sign_In();
                    break;

                case 3:
                    system("cls");
                    Program_Jalan = "n";
                    break;
            }

        } catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Error : " << e.what() << "\n";
            system("pause");

        } catch (const runtime_error& e) {
            cout << "  Error : " << e.what() << "\n";
            system("pause");
        }
    }

    return 0;
}