#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "utils.h"
#include "greedy.h"
#include "genetic.h"

using namespace std;

int first_timer, second_timer;

int play_game(vector<int> deck, tuple<double, double, double, double> genome) {
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
        if (curr_player == 0 && first.empty()) {
            deal(deck, first, second);
        }

        pair<int, int> tmp_score;

        if (curr_player == 0) {
            clock_t begin = clock();
            tmp_score = greedy_simple(table, first);
            first_timer += clock() - begin;

            score.first.first += tmp_score.first;
            score.first.second += tmp_score.second;
            if (tmp_score > make_pair(0, 0)) {
                last_player_scored = 0;
            }
        } else {
            clock_t begin = clock();
            tmp_score = genetic(table, second, first, genome);
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
    int other = score.first.first;
    int my = score.second.first;
    if (score.first.second > score.second.second) {
        other++;
    } else if (score.second.second > score.first.second) {
        my++;
    }
    return my - other;
}

int tournament(tuple<double, double, double, double> genome) {
    int score = 0;
    for (int i = 0; i < 30; i++) {
        int tmp = play_game(generate_deck(), genome);
        if (tmp > 0) {
            score++;
        }
        if (tmp < 0) {
            score--;
        }
    }
    //cout << score << endl;
    return score;
}

void crossover(tuple<double, double, double, double> &a, tuple<double, double, double, double> &b) {
    get<0>(b) = (get<0>(a) + get<0>(b)) / 2;
    get<1>(b) = (get<1>(a) + get<1>(b)) / 2;
    get<2>(b) = (get<2>(a) + get<2>(b)) / 2;
    get<3>(b) = (get<3>(a) + get<3>(b)) / 2;
}

double rand01() {
    return (double) rand() / RAND_MAX;
}

int main() {
    vector<pair<int, tuple<double, double, double, double>>> population;
    int population_size = 50;
    for (int i = 0; i < population_size; i++) {
        auto tpl = make_tuple(rand01(), rand01(), rand01(), rand01());
        population.push_back(make_pair(0, tpl));
    }

    int iterations = 100;
    for (int _it = 0; _it < iterations; _it++) {
        for (int i = 0; i < population.size(); i++) {
            population[i].first = tournament(population[i].second);
        }
        sort(population.begin(), population.end());
        reverse(population.begin(), population.end());
        cout << "BEST SCORE: " << tournament(population[0].second) << endl;

        for (int i = population_size / 3; i < population.size(); i++) {
            if (rand01() < 0.05) {
                population[i] = make_pair(0, make_tuple(rand01(), rand01(), rand01(), rand01()));
            }
        }
        for (int i = 0; i < population.size(); i++) {
            for (int j = i + population_size / 3; j < population.size(); j++) {
                crossover(population[i].second, population[j].second);
            }
        }
        auto tpl = population[0].second;
        cout << get<0>(tpl) << " " << get<1>(tpl) << " " << get<2>(tpl) << " " << get<3>(tpl) << endl;
    }
    auto tpl = population[0].second;
    cout << get<0>(tpl) << " " << get<1>(tpl) << " " << get<2>(tpl) << " " << get<3>(tpl) << endl;
    return 0;
}
