#ifndef TABLIC_UTILS_H
#define TABLIC_UTILS_H

void do_move(int card, int mask, std::vector<int> &hand, std::vector<int> &table);
std::pair<int, int> try_move(int card, int mask, int aces_mask, std::vector<int> &hand, std::vector<int> &table);

#endif //TABLIC_UTILS_H
