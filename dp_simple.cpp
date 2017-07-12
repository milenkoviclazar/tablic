#include <iostream>
#include <vector>

using namespace std;

int solve(vector<int> table, vector<int> first, vector<int> second, vector<int> deck) {

}

int main() {

    vector<int> deck;
    // zanemarićemo malu dvojku
    // zanemarićemo mogućnost nenošenja karte
    // zanemarićemo "tri na karte"
    for (int i = 2; i <= 14; i++) {
        for (int j = 0; j < 4; j++) {
            deck.push_back(i);
        }
    }
    random_shuffle(deck.begin(), deck.end());
    vector<int> table;
    vector<int> first;
    vector<int> second;

    for (int i = 0; i < 4; i++) {
        table.push_back(deck.back());
        deck.pop_back();
    }
    cout << solve(table, first, second, deck) << endl;
    return 0;
}