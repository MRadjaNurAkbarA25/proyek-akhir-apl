#ifndef CSV_H
#define CSV_H

#include "data.h"
#include <string>
using namespace std;

// Utility csv
void trimStr(char* s);
int parseCSVLine(char* line, char fields[][256], int maxFields);
vector<string> splitPipe(const string& s);

// superpower 
vector<Superpower> loadSuperpowerCSV(const string& filename);

// card biasa
vector<Card> loadCardCSV(const string& filename, const string& team);
void saveCardCSV(const string& filename, const vector<Card>& cards);

int Muat_Akun();

#endif