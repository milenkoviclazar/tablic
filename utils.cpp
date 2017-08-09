#include <vector>

using namespace std;

// special scoring of 2 of clubs and 10 of diamonds is ignored
pair<int, int> try_move(int card, int mask, int aces_mask, vector<int> &hand, vector<int> &table) {
    pair<int, int> score;
    int sum = 0;
    int ace_cnt = 0;
    for (int i = 0; i < table.size(); i++) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }
        int value = table[i];
        if (table[i] == 11) {
            if (aces_mask & (1 << ace_cnt)) {
                value = 1;
            }
            ace_cnt++;
        }
        if (value < card) {
            sum += value;
        }
        if (value > card) {
            return make_pair(-1, -1);
        }
    }
    if (sum != 0 && sum != card) {
        return make_pair(-1, -1);
    }
    score.first = 0;
    if (card == 1 || card >= 10) {
        score.first++;
    }
    // clearing the table yields an additional point
    if (__builtin_popcount(mask) == table.size()) {
        //score.first++;
    }
    for (int i = 0; i < table.size(); i++) {
        if ((mask & (1 << i)) && (table[i] >= 10)) {
            score.first++;
        }
    }
    if (mask != 0) {
        score.second = __builtin_popcount(mask) + 1;
    }
    return score;
}

void do_move(int card, int mask, vector<int> &hand, vector<int> &table) {
    hand.erase(find(hand.begin(), hand.end(), card));
    vector<int> new_table;
    for (int i = 0; i < table.size(); i++) {
        if ((mask & (1 << i)) == 0) {
            new_table.push_back(table[i]);
        }
    }
    if (mask == 0) {
        new_table.push_back(card);
    }
    table = new_table;
}
