#ifndef TABLIC_UTILS_H
#define TABLIC_UTILS_H

void do_move(int card, int mask, std::vector<int> &hand, std::vector<int> &table);

std::pair<int, int> try_move(int card, int mask, int aces_mask, std::vector<int> &hand, std::vector<int> &table);

void deal(std::vector<int> &deck, std::vector<int> &first, std::vector<int> &second);

std::vector<int> generate_deck();

#endif //TABLIC_UTILS_H
