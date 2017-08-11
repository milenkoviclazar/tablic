#ifndef TABLIC_BACKTRACK_H
#define TABLIC_BACKTRACK_H

std::pair<int, int> backtrack(std::vector<int> &table,
                              std::vector<int> &hand,
                              std::vector<int> &other,
                              std::vector<int> &deck,
                              bool i_am_the_first_player);

#endif //TABLIC_BACKTRACK_H
