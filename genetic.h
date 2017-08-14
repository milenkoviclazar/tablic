#ifndef TABLIC_GENETIC_H
#define TABLIC_GENETIC_H

std::pair<int, int> genetic(std::vector<int> &table,
                            std::vector<int> &hand,
                            std::vector<int> &other,
                            std::tuple<double, double, double, double> genome);

#endif //TABLIC_GENETIC_H
