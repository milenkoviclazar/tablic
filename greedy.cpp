#include <vector>
#include <iostream>

#include "utils.h"

using namespace std;

pair<int, int> greedy_simple(vector<int> &table, vector<int> &hand) {
    pair<int, int> best_score = make_pair(0, 0);
    int best_mask = 0, best_idx = 0;
    int aces = count(table.begin(), table.end(), 11);
    for (int i = 0; i < hand.size(); i++) {
        for (int aces_mask = 0; aces_mask < (1 << aces); aces_mask++) {
            // table size can grow big
            for (int mask = 0; mask < (1LL << table.size()); mask++) {
                int card = hand[i];
                pair<int, int> tmp_score = try_move(card, mask, aces_mask, hand, table);
                if (tmp_score > best_score) {
                    best_score = tmp_score;
                    best_idx = i;
                    best_mask = mask;
                }
            }
        }
    }
//    cout << "GRDY _OUT " << endl;

    do_move(hand[best_idx], best_mask, hand, table);
//    cout << "GRDY _OUT " << endl;
    return best_score;
}