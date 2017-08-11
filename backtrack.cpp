#include <vector>
#include <iostream>
#include <map>
#include <cassert>

using namespace std;

#include "greedy.h"
#include "utils.h"

map<tuple<vector<int>, vector<int>, vector<int>, int>, tuple<int, int, pair<int, int>>> memo;

pair<int, int> backtrack_helper(vector<int> &table,
                                vector<int> &hand,
                                vector<int> &other,
                                vector<int> &deck,
                                bool i_am_the_first_player,
                                int depth = 0) {
//    cout << depth << endl;
    if (depth > 5) {
        return make_pair(0, 0);
    }
    if (hand.empty() && deck.empty()) {
        return make_pair(0, 0);
    }
    if (hand.empty()) {
        assert(depth != 0); // we need to ensure that we will not modify the existing table

        if (i_am_the_first_player) {
            deal(deck, hand, other);
        } else {
            deal(deck, other, hand);
        }
    }
    auto tpl = make_tuple(table, hand, other, deck.size());
    if (memo.find(tpl) != memo.end()) {
//        cout << deck.empty() << endl;
        auto best_move = memo[tpl];
        int idx = get<0>(best_move);
        int mask = get<1>(best_move);
        pair<int, int> score = get<2>(best_move);
//        cout << "DO MOVE " << idx << " " << mask << endl;
//        for (int i = 0; i < table.size(); i++) {
//            cout << table[i] << " ";
//        } cout << endl;
//        cout << idx << " " << hand.size() << endl;
        do_move(hand[idx], mask, hand, table);
//        cout << "DONE MOVE" << endl;
//        cout << deck.empty() << endl;
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
                vector<int> new_deck = deck;
                do_move(card, mask, new_hand, new_table);

                if (!new_other.empty()) {
                    greedy_simple(new_table, new_other);
                }

                pair<int, int> global_score = backtrack_helper(new_table, new_hand, new_other, new_deck, i_am_the_first_player, depth + 1);
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
//    cout << "DO MOVE" << endl;

    memo[tpl] = make_tuple(best_idx, best_mask, best_curr_score);
    do_move(hand[best_idx], best_mask, hand, table);
    return best_curr_score;
}

pair<int, int> backtrack(vector<int> &table,
                         vector<int> &hand,
                         vector<int> &other,
                         vector<int> &deck,
                         bool i_am_the_first_player) {

    pair<int, int> score = backtrack_helper(table, hand, other, deck, i_am_the_first_player);

//    cout << score.first << " " << score.second << endl;
    return score;
}