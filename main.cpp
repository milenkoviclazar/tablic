#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// mala dvojka (nebitna)
// velika desetka (matematicki nebitna)

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
    if (__builtin_popcount(mask) == table.size()) {
        score.first++;
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

pair<int, int> backtrack(vector<int> &table, vector<int> &hand, vector<int> &other, vector<int> deck) {
    return make_pair(-1, -1);
}

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
    do_move(hand[best_idx], best_mask, hand, table);
    return best_score;
}

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
