#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "utils.h"
#include "backtrack6.h"
#include "backtrack.h"
#include "greedy.h"
#include "genetic.h"

using namespace std;

int first_timer, second_timer;

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
    int last_player_scored = 0;
    for (int move = 0; move < 48; move++) {
//        cout << first.size() << " " << second.size() << endl;
//        cout << "TABLE: ";
//        for (int i = 0; i < table.size(); i++) {
//            cout << table[i] << " ";
//        } cout << endl;
        if (curr_player == 0 && first.empty()) {
            deal(deck, first, second);
        }

        pair<int, int> tmp_score;

        if (curr_player == 0) {
            clock_t begin = clock();
            tmp_score = backtrack6(table, first, second);
            first_timer += clock() - begin;

            score.first.first += tmp_score.first;
            score.first.second += tmp_score.second;
            if (tmp_score > make_pair(0, 0)) {
                last_player_scored = 0;
            }
        } else {
            clock_t begin = clock();
            tmp_score = genetic(table, second, first, make_tuple(0.442331, 0.505713, 0.573743, 0.454097));
            second_timer += clock() - begin;
            score.second.first += tmp_score.first;
            score.second.second += tmp_score.second;
            if (tmp_score > make_pair(0, 0)) {
                last_player_scored = 1;
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
    if (last_player_scored == 0) {
        score.first.first += remaining_valuables;
        score.first.second += table.size();
    } else {
        score.second.first += remaining_valuables;
        score.second.second += table.size();
    }
    return score;
}

int main() {
    int games_played = 2;
    int first_wins = 0;
    int second_wins = 0;
    int draws = 0;
    for (int game = 0; game < games_played; game++) {
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
            first_wins++;
        } else if (score.second > score.first) {
            cout << "Second wins!" << endl;
            second_wins++;
        } else {
            cout << "Draw" << endl;
            draws++;
        }
        printf("(%d, %d) - (%d, %d)\n", score.first.first, score.first.second, score.second.first, score.second.second);
    }
    cout << "Score: " << first_wins << " - " << second_wins << endl;
    cout << (double) first_timer / games_played / CLOCKS_PER_SEC << " "
         << (double) second_timer / games_played / CLOCKS_PER_SEC << endl;
    return 0;
}
