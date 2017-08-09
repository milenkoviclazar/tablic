#ifndef TABLIC_BACKTRACK_H
#define TABLIC_BACKTRACK_H

std::pair<int, int> backtrack_helper(std::vector<int> &table,
                                     std::vector<int> &hand,
                                     std::vector<int> &other,
                                     std::vector<int> &deck);
#endif //TABLIC_BACKTRACK_H
