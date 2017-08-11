#include <vector>
#include <iostream>
#include <map>

using namespace std;

#include "greedy.h"
#include "utils.h"

map<tuple<vector<int>, vector<int>, vector<int>>, tuple<int, int, pair<int, int>>> memo6;

pair<int, int> backtrack6_helper(vector<int> &table,
                                 vector<int> &hand,
                                 vector<int> &other,
                                 int depth = 0) {
    if (hand.empty()) {
        return make_pair(0, 0);
    }
    auto tpl = make_tuple(table, hand, other);
    if (memo6.find(tpl) != memo6.end()) {
        auto best_move = memo6[tpl];
        int idx = get<0>(best_move);
        int mask = get<1>(best_move);
        pair<int, int> score = get<2>(best_move);
        do_move(hand[idx], mask, hand, table);
        return score;
    }

    pair<int, int> best_score = make_pair(0, 0);
    pair<int, int> best_curr_score = make_pair(0, 0);
    int best_mask = 0, best_idx = 0;
    int aces = count(table.begin(), table.end(), 11);
    for (int i = 0; i < hand.size(); i++) {
        for (int aces_mask = 0; aces_mask < (1 << aces); aces_mask++) {
            // table size can possibly grow big
            for (int mask = 0; mask < (1LL << table.size()); mask++) {
                int card = hand[i];
                pair<int, int> tmp_score = try_move(card, mask, aces_mask, hand, table);

                vector<int> new_table = table;
                vector<int> new_hand = hand;
                vector<int> new_other = other;
                do_move(card, mask, new_hand, new_table);

                if (!new_other.empty()) {
                    greedy_simple(new_table, new_other);
                }

                pair<int, int> global_score = backtrack6_helper(new_table, new_hand, new_other, depth + 1);
                global_score.first += tmp_score.first;
                global_score.second += tmp_score.second;
                if (global_score > best_score) {
                    best_score = global_score;
                    best_curr_score = tmp_score;
                    best_idx = i;
                    best_mask = mask;
                }
            }
        }
    }

    do_move(hand[best_idx], best_mask, hand, table);
    memo6[tpl] = make_tuple(best_idx, best_mask, best_curr_score);
    return best_curr_score;
}

pair<int, int> backtrack6(vector<int> &table,
                          vector<int> &hand,
                          vector<int> &other) {

    pair<int, int> score = backtrack6_helper(table, hand, other);
//    cout << score.first << " " << score.second << endl;
    return score;
}