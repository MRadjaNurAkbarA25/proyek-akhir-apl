#include "csv.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
using namespace std;

// Utility

vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;
    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            // trim
            int start = field.find_first_not_of(" \t");
            int end   = field.find_last_not_of(" \t\r\n");
            fields.push_back(start == string::npos ? "" : field.substr(start, end - start + 1));
            field.clear();
        } else {
            field += c;
        }
    }
    // field terakhir
    int start = field.find_first_not_of(" \t");
    int end   = field.find_last_not_of(" \t\r\n");
    fields.push_back(start == string::npos ? "" : field.substr(start, end - start + 1));
    return fields;
}

vector<string> splitPipe(const string& s) {
    vector<string> result;
    if (s == "-") return result;
    stringstream ss(s);
    string token;
    while (getline(ss, token, '|')) {
        // trim spasi
        int start = token.find_first_not_of(" \t");
        int end   = token.find_last_not_of(" \t");
        if (start != string::npos)
            result.push_back(token.substr(start, end - start + 1));
    }
    return result;
}

// superpower
vector<Superpower> loadSuperpowerCSV(const string& filename) {
    vector<Superpower> cards;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  [ERROR] Tidak bisa membuka file: " << filename << "\n";
        return cards;
    }
    string lineStr;
    getline(file, lineStr); // skip header
    int autoID = 1;
    while (getline(file, lineStr)) {
        if (lineStr.empty()) continue;
        vector<string> f = parseCSVLine(lineStr);
        if (f.size() < 11) continue;

        Superpower sp;
        sp.id               = autoID++;
        sp.name             = f[1];     // kolom 1: name
        sp.cls              = splitPipe(f[2]);   // kolom 2: class
        sp.category         = f[3];     // kolom 3: category
        sp.tribes           = f[4];     // kolom 4: tribes
        sp.strength         = (f[5] == "-" ? -1 : stoi(f[5]));  // kolom 5: strength
        sp.health           = (f[6] == "-" ? -1 : stoi(f[6]));  // kolom 6: health
        sp.traits           = f[7];     // kolom 7: traits
        sp.effects          = f[8];     // kolom 8: effects
        sp.desc             = f[9];     // kolom 9: desc
        sp.isSignature      = (f[10] == "-" ? 0 : stoi(f[10]));  // kolom 10: isSignature
        sp.cost             = -1;       // superpower tidak ada cost
        cards.push_back(sp);
    }
    file.close();
    return cards;
}

// card biasa
vector<Card> loadCardCSV(const string& filename, const string& team) {
    vector<Card> cards;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  [ERROR] Tidak bisa membuka file: " << filename << "\n";
        return cards;
    }
    string lineStr;
    getline(file, lineStr); // skip header
    int autoID = 1;
    while (getline(file, lineStr)) {
        if (lineStr.empty()) continue;
        vector<string> f = parseCSVLine(lineStr);
        if ((int)f.size() < 13) continue;

        Card c;
        c.id        = autoID++;
        c.name      = toLower(f[1]);
        c.rarity    = f[2];
        c.cardSet   = f[3];
        c.cost      = (f[4] == "-" ? -1 : stoi(f[4]));
        c.cardClass = f[5];
        c.category  = f[6];
        c.team      = team;
        c.strength  = (f[8] == "-" ? -1 : stoi(f[8]));
        c.health    = (f[9] == "-" ? -1 : stoi(f[9]));

        c.tags.tribes  = splitPipe(f[7]);
        c.tags.traits  = splitPipe(f[10]);
        c.tags.effects = splitPipe(f[11]);
        c.tags.desc    = (f[12] == "-" ? "" : f[12]);

        cards.push_back(c);
    }
    file.close();
    return cards;
}

void saveCardCSV(const string& filename, const vector<Card>& cards) {
    ofstream file(filename);
    file << "id,name,rarity,cardSet,cost,class,category,tribes,strength,health,traits,effects,desc\n";
    for (int i = 0; i < (int)cards.size(); i++) {
        const Card& c = cards[i];

        // Gabung vector jadi string dengan "|"
        string tribes, traits, effects;
        for (int j = 0; j < (int)c.tags.tribes.size(); j++)
            tribes += (j ? "|" : "") + c.tags.tribes[j];
        for (int j = 0; j < (int)c.tags.traits.size(); j++)
            traits += (j ? "|" : "") + c.tags.traits[j];
        for (int j = 0; j < (int)c.tags.effects.size(); j++)
            effects += (j ? "|" : "") + c.tags.effects[j];

        file << c.id                                          << ","
            << c.name                                        << ","
            << c.rarity                                      << ","
            << c.cardSet                                     << ","
            << (c.cost == -1 ? "-" : to_string(c.cost))     << ","
            << c.cardClass                                   << ","
            << c.category                                    << ","
            << (tribes.empty()  ? "-" : tribes)              << ","
            << (c.strength == -1 ? "-" : to_string(c.strength)) << ","
            << "-"                                           << ","
            << (traits.empty()  ? "-" : traits)              << ","
            << (effects.empty() ? "-" : effects)             << ","
            << (c.tags.desc.empty() ? "-" : c.tags.desc)    << "\n";
    }
    file.close();
}

string Trim(string s) {
    if (s.empty()) return s;
    size_t first = s.find_first_not_of(" \t\r\n");

    if (first == string :: npos) return "";

    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, (last - first + 1));
}

int Muat_Akun() {
    ifstream file("accounts.csv");

    if (!file.is_open()) {
        cout << "  [!] File accounts.csv tidak ditemukan.\n";
        system("pause");
        return 0;
        }

    string baris;
    getline(file, baris);
    List_Akun.clear();

    while (getline(file, baris)) {
        if (baris.empty()) continue;

        stringstream parser(baris);
        string id, username, pw, role;
        getline(parser, id, ',');
        getline(parser, username, ',');
        getline(parser, pw, ',');
        getline(parser, role, ',');

        if (!id.empty()) {
            try {
                Akun acc_baru;
                acc_baru.ID = stoi(Trim(id));
                acc_baru.Username = Trim(username);
                acc_baru.Password  = Trim(pw);
                acc_baru.Role = Trim(role);
                List_Akun.push_back(acc_baru);

                } catch (const exception& e) {
                continue;
            } 
            }
        }

    file.close();
    return List_Akun.size();
}

vector<Deck> loadDeckCSV(const string& filename) {
    vector<Deck> result;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  [ERROR] Tidak bisa membuka file: " << filename << "\n";
        return result;
    }

    string lineStr;
    getline(file, lineStr); // skip header

    while (getline(file, lineStr)) {
        if (lineStr.empty()) continue;
        vector<string> f = parseCSVLine(lineStr);
        if ((int)f.size() < 6) continue;

        Deck d;
        d.id          = stoi(f[0]);
        d.ownerId     = stoi(f[1]);
        d.deckName    = f[2];
        d.isPlant = (f[3] == "1");
        d.heroId      = stoi(f[4]);
        d.status      = f[5];

        result.push_back(d);
    }

    file.close();
    return result;
}

void loadDeckCardsCSV(const string& filename, vector<Deck>& decks) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  [ERROR] Tidak bisa membuka file: " << filename << "\n";
        return;
    }

    string lineStr;
    getline(file, lineStr); // skip header

    while (getline(file, lineStr)) {
        if (lineStr.empty()) continue;
        vector<string> f = parseCSVLine(lineStr);
        if ((int)f.size() < 3) continue;

        int deckId  = stoi(f[0]);
        DeckCard dc;
        dc.cardId   = stoi(f[1]);
        dc.qty = stoi(f[2]);

        // Cari deck yang sesuai
        for (auto& d : decks) {
            if (d.id == deckId) {
                d.cards.push_back(dc);
                break;
            }
        }
    }

    file.close();
}

void saveDeckCSV(const string& filename, const vector<Deck>& decks) {
    ofstream file(filename);
    file << "id, ownerId, deckName, isPlantDeck, heroId, status\n";
    for (auto& d : decks) {
        file << d.id          << ","
            << d.ownerId     << ","
            << d.deckName    << ","
            << (d.isPlant ? "1" : "0") << ","
            << d.heroId      << ","
            << d.status      << "\n";
    }
    file.close();
}

void saveDeckCardsCSV(const string& filename, const vector<Deck>& decks) {
    ofstream file(filename);
    file << "deckId, cardId, quantity\n";
    for (auto& d : decks) {
        for (auto& dc : d.cards) {
            file << d.id      << ","
                << dc.cardId << ","
                << dc.qty << "\n";
        }
    }
    file.close();
}

vector<Hero> loadHeroCSV(const string& filename) {
    vector<Hero> result;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  [ERROR] Tidak bisa membuka file: " << filename << "\n";
        return result;
    }

    string lineStr;
    getline(file, lineStr); // skip header

    while (getline(file, lineStr)) {
        if (lineStr.empty()) continue;
        vector<string> f = parseCSVLine(lineStr);
        if ((int)f.size() < 8) continue;

        Hero h;
        h.id      = stoi(f[0]);
        h.name    = f[1];
        h.isPlant = (f[2] == "1");
        h.classes = f[3];          // "mega-grow|smarty"
        h.superpowerIds[0] = stoi(f[4]);
        h.superpowerIds[1] = stoi(f[5]);
        h.superpowerIds[2] = stoi(f[6]);
        h.superpowerIds[3] = stoi(f[7]);

        result.push_back(h);
    }

    file.close();
    return result;
}