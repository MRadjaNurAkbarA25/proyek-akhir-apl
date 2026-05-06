#ifndef CRUDDECK_H
#define CRUDDECK_H

#include "data.h"
using namespace std;

void lihatDek(vector<Deck>& decks, vector<Hero>& heroes,
              vector<Card>& plants, vector<Card>& zombies,
              int ownerId);
void tambahDek(vector<Deck>& decks, vector<Hero>& heroes,
              vector<Card>& plants, vector<Card>& zombies,
              int ownerId);
void editDek(vector<Deck>& decks, vector<Hero>& heroes,
             vector<Card>& plants, vector<Card>& zombies,
             int ownerId);
void hapusDek(vector<Deck>& decks, int ownerId);
#endif
