//
// Created by Yu Weiqiang on 2022/11/30.
//
#include "dpll.h"

DPLL::DPLL() = default;

bool DPLL::solve(std::vector<std::vector<int>> cnf, std::unordered_map<int,bool> assignMap, std::unordered_set<int> variables) {
  bcp(cnf, assignMap, variables);
  plp(cnf,assignMap,variables);
  if(cnf.empty()){
    return true;
  }
  for(std::vector<int>& clause: cnf){
    if(clause.empty()){
      return false;
    }
  }
  int p = choose_var(variables);
  assignMap[p] = true;
  variables.erase(p);
  if(solve(cnf, assignMap, variables)){
    return true;
  }else{
    assignMap[p] = false;
    return solve(cnf, assignMap, variables);
  }
}

void DPLL::bcp(std::vector<std::vector<int>>& cnf, std::unordered_map<int,bool>& assignMap, std::unordered_set<int>& variables) {
  for (auto cnf_ptr = cnf.begin(); cnf_ptr != cnf.end(); ++cnf_ptr) {
    std::vector<int> &clause = *cnf_ptr;
    bool crop = false;
//    std::cout << clauseString(clause) << std::endl;
    for (auto lit_ptr = clause.begin(); lit_ptr != clause.end(); lit_ptr++) {
      int literal = *lit_ptr;
      int key = (literal > 0) ? literal : -literal;
      if (assignMap.count(key)) {
        if ((assignMap[key] && literal > 0) || (!assignMap[key] && literal < 0)) {
          cnf.erase(cnf_ptr--);
          crop = true;
          break;
        } else {
          clause.erase(lit_ptr--);
        }
        if (clause.empty()) {
          return;
        }
      }
    }
//    std::cout << clauseString(clause) << std::endl;
    if (!crop && clause.size() == 1) {
      int val = clause[0];
      if (val > 0) {
        assignMap[val] = true;
        variables.erase(val);
      } else {
        assignMap[-val] = false;
        variables.erase(-val);
      }
      cnf.erase(cnf_ptr);
      cnf_ptr = cnf.begin() - 1;
    }
  }
}

void DPLL::plp(std::vector<std::vector<int>>& cnf, std::unordered_map<int,bool>& assignMap, std::unordered_set<int>& variables) {
  std::unordered_map<int,int> variable_counter;
  for (auto cnf_ptr = cnf.begin(); cnf_ptr != cnf.end(); ++cnf_ptr) {
    std::vector<int> &clause = *cnf_ptr;
    for (auto lit_ptr = clause.begin(); lit_ptr != clause.end(); lit_ptr++) {
      variable_counter[*lit_ptr]++;
    }
  }

  while(true) {
    bool plp = false;
    for (auto it = variable_counter.begin(); it != variable_counter.end();) {
      int key = it->first;
      if (!variable_counter.count(-key)) {
        plp = true;
        if (key > 0) {
          assignMap[key] = true;
          variables.erase(key);
          it = variable_counter.erase(it);
        } else {
          assignMap[-key] = false;
          variables.erase(-key);
          it = variable_counter.erase(it);
        }
      }else{
        ++it;
      }
    }
    if(!plp){
      break;
    }
    for (auto cnf_ptr = cnf.begin(); cnf_ptr != cnf.end(); ++cnf_ptr) {
      std::vector<int> &clause = *cnf_ptr;
      bool crop = false;
      for (auto lit_ptr = clause.begin(); lit_ptr != clause.end(); lit_ptr++) {
        int literal = *lit_ptr;
        int key = (literal > 0) ? literal : -literal;
        if (crop) {
          variable_counter[literal]--;
          if (variable_counter[literal] == 0) {
            variable_counter.erase(literal);
          }
        } else if (assignMap.count(key)) {
            crop = true;
            lit_ptr = clause.begin() - 1;
        }
      }
      if (crop) {
        cnf.erase(cnf_ptr--);
      }
    }
  }
}


int DPLL::choose_var(std::unordered_set<int>& variables) {
  return *variables.begin();
}


//std::string DPLL::cnfString(std::vector<std::vector<int>>& cnf) const {
//  std::string result;
//  // your code starts here
//  for(const std::vector<int>& vec: cnf){
//    result += "[";
//    for(auto it = vec.begin();it != vec.end(); ++it){
//      if(it - vec.begin() > 0){
//        result += ",";
//      }
//      result += std::to_string(*it);
//    }
//    result += "]";
//  }
//  return result;
//}

//std::string DPLL::clauseString(std::vector<int>& vec) const {
//  std::string result;
//  // your code starts here
//  result += "[";
//  for(auto it = vec.begin();it != vec.end(); ++it){
//    if(it - vec.begin() > 0){
//      result += ",";
//    }
//    result += std::to_string(*it);
//  }
//  result += "]";
//
//  return result;
//}

//template <typename u, typename v>
//std::string DPLL::mapString(std::unordered_map<u,v>& assignMap) const {
//  std::string result;
//  // your code starts here
//  for(auto& [key,val]: assignMap){
//    result += "[" + std::to_string(key) + " " + std::to_string(val) + "]";
//  }
//  return result;
//}


//std::string DPLL::setString(std::unordered_set<int>& variables) const {
//  std::string result;
//  for(int e: variables){
//    result +=  std::to_string(e) + " ";
//  }
//  return result;
//}

DPLL::~DPLL() = default;





