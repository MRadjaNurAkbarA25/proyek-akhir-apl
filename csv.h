#ifndef CSV_H
#define CSV_H

#include "data.h"
#include <string>
using namespace std;

// Utility csv
vector<string> parseCSVLine(const string& line);
vector<string> splitPipe(const string& s);

// Hero
vector<Hero> loadHeroCSV(const string& filename);

// superpower 
vector<Superpower> loadSuperpowerCSV(const string& filename);

// card biasa
vector<Card> loadCardCSV(const string& filename, const string& team);
void saveCardCSV(const string& filename, const vector<Card>& cards);

// Akun
int Muat_Akun();

// Deck
vector<Deck> loadDeckCSV(const string& filename);
void loadDeckCardsCSV(const string& filename, vector<Deck>& decks);
void saveDeckCSV(const string& filename, const vector<Deck>& decks);
void saveDeckCardsCSV(const string& filename, const vector<Deck>& decks);

#endif