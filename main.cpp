#include <iostream>
#include <vector>
#include <algorithm>

#include "utils.h"
#include "backtrack.h"
#include "greedy.h"

using namespace std;

pair<pair<int, int>, pair<int, int>> play_game(vector<int> deck) {
    vector<int> first;
    vector<int> second;
    vector<int> table;
    int curr_player = 0;
    pair<pair<int, int>, pair<int, int>> score = make_pair(make_pair(0, 0), make_pair(0, 0));
    for (int i = 0; i < 4; i++) {
        table.push_back(deck.back());
        deck.pop_back();
    }
    int last_player = 0;
    for (int move = 0; move < 48; move++) {
        for (int i = 0; i < table.size(); i++) {
            cout << table[i] << " ";
        } cout << endl;
        if (curr_player == 0 && first.empty()) {
            for (int i = 0; i < 6; i++) {
                first.push_back(deck.back());
                deck.pop_back();
                second.push_back(deck.back());
                deck.pop_back();
            }
        }
        pair<int, int> tmp_score;
        if (curr_player == 0) {
            tmp_score = greedy_simple(table, first);
            score.first.first += tmp_score.first;
            score.first.second += tmp_score.second;
            if (tmp_score > make_pair(0, 0)) {
                last_player = 0;
            }
        } else {
            tmp_score = greedy_simple(table, second);
            score.second.first += tmp_score.first;
            score.second.second += tmp_score.second;
            if (tmp_score > make_pair(0, 0)) {
                last_player = 1;
            }
        }
        curr_player ^= 1;

    }

    // zadnja karta
    int remaining_valuables = 0;
    for (int i = 0; i < table.size(); i++) {
        if (table[i] >= 10) {
            remaining_valuables++;
        }
    }
    if (last_player == 0) {
        score.first.first += remaining_valuables;
        score.first.second += table.size();
    } else {
        score.second.first += remaining_valuables;
        score.second.second += table.size();
    }
    return score;
}

int main() {
    vector<int> deck;
    for (int i = 2; i <= 14; i++) {
        for (int j = 0; j < 4; j++) {
            deck.push_back(i);
        }
    }
    random_shuffle(deck.begin(), deck.end());
    pair<pair<int, int>, pair<int, int>> score = play_game(deck);
    if (score.first > score.second) {
        cout << "First wins!" << endl;
    } else {
        cout << "Second wins!" << endl;
    }
    printf("(%d, %d) - (%d, %d)\n", score.first.first, score.first.second, score.second.first, score.second.second);
    return 0;
}
