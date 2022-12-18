//
// Created by Yu Weiqiang on 2022/11/30.
//

#ifndef PA2_DPLL_H
#define PA2_DPLL_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_set>

class DPLL {
public:
    DPLL();
    bool solve(std::vector<std::vector<int>> cnf, std::unordered_map<int,bool> assignMap, std::unordered_set<int> variables);
    void bcp(std::vector<std::vector<int>>& cnf, std::unordered_map<int,bool>& assignMap, std::unordered_set<int>& variables);
    void plp(std::vector<std::vector<int>>& cnf, std::unordered_map<int,bool>& assignMap, std::unordered_set<int>& variables);
//    std::string cnfString(std::vector<std::vector<int>>& cnf) const;
//    template <typename u, typename v>
//    std::string mapString(std::unordered_map<u,v>& assignMap) const;
//    std::string clauseString(std::vector<int>& clause) const;
//    std::string setString(std::unordered_set<int>& variables) const;
    int choose_var(std::unordered_set<int>& variables);
    virtual ~DPLL();
};

#endif //PA2_DPLL_H
