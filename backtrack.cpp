#include <vector>

using namespace std;

#include "greedy.h"
#include "utils.h"

// TODO: add memoization
pair<int, int> backtrack_helper(vector<int> &table, vector<int> &hand, vector<int> &other, vector<int> &deck) {
    if (hand.empty()) {
        return make_pair(0, 0);
    }
    pair<int, int> best_score = make_pair(0, 0);
    int best_mask = 0, best_idx = 0;
    int aces = count(table.begin(), table.end(), 11);
    for (int i = 0; i < hand.size(); i++) {
        for (int aces_mask = 0; aces_mask < (1 << aces); aces_mask++) {
            // table size can possibly grow big
            for (int mask = 0; mask < (1LL << table.size()); mask++) {
                int card = hand[i];
                pair<int, int> tmp_score = try_move(card, mask, aces_mask, hand, table);
                if (!other.empty()) {
                    greedy_simple(table, hand);
                }
                if (tmp_score > best_score) {
                    best_score = tmp_score;
                    best_idx = i;
                    best_mask = mask;
                }
            }
        }
    }
    do_move(hand[best_idx], best_mask, hand, table);
    return best_score;
}

pair<int, int> backtrack(vector<int> &table, vector<int> &hand, vector<int> &other, vector<int> &deck) {
    vector<int> tmp_table = table, tmp_hand = hand, tmp_other = other, tmp_deck = deck;
    return backtrack_helper(tmp_table, tmp_hand, tmp_other, tmp_deck);
}