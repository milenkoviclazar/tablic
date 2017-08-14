#include <iostream>
#include <vector>

#include "utils.h"
#include "greedy.h"

using namespace std;

pair<int, int> genetic(vector<int> &table,
                       vector<int> &hand,
                       vector<int> &other,
                       tuple<double, double, double, double> genome) {
    double best_fit = -1e12;
    pair<int, int> best_score = make_pair(0, 0);
    int best_mask = 0, best_idx = 0;
    int aces = count(table.begin(), table.end(), 11);
    for (int i = 0; i < hand.size(); i++) {
        for (int aces_mask = 0; aces_mask < (1 << aces); aces_mask++) {
            // table size can grow big
            for (int mask = 0; mask < (1LL << table.size()); mask++) {
                int card = hand[i];
                pair<int, int> my_score = try_move(card, mask, aces_mask, hand, table);
                pair<int, int> other_score = make_pair(0, 0);
                vector<int> newtable = table;
                vector<int> newother = other;
                if (!other.empty()) {
                    other_score = greedy_simple(newtable, newother);
                }
                double curr_fit = 0.0;
                curr_fit += get<0>(genome) * my_score.first;
                curr_fit += get<1>(genome) * my_score.second;
                curr_fit -= get<2>(genome) * other_score.first;
                curr_fit -= get<3>(genome) * other_score.second;
                if (curr_fit > best_fit) {
                    best_score = my_score;
                    best_fit = curr_fit;
                    best_idx = i;
                    best_mask = mask;
                }
            }
        }
    }

    do_move(hand[best_idx], best_mask, hand, table);
    return best_score;
};