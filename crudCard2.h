#ifndef CRUDCARD2_H
#define CRUDCARD2_H

#include "data.h"
#include "csv.h"
#include "utils.h"

void allCardsReview();
void superpowersReview();
void printSuperpowerDetail(Superpower& sp);
void printCardDetail(Card& c);
void menuLihat();
void menuTambah();
void menuUpdate();
void menuDelete();
int Cari_Nama_Linear(vector<Card>& Cards, int Panjang, string Target);
void Menu_Cari_Nama(vector<Card>& Cards, int Panjang);
void menuSearch();

#endif