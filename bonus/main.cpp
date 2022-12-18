//
// Created by Yu Weiqiang on 2022/12/14.
//
#include "tseitinTransformer.h"
#include "parser.h"
#include <iostream>
#include <vector>
#include "dpll.h"
#include "unordered_map"
#include "unordered_set"

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    // your code starts here
    try {
      getline(std::cin, line);
      if (std::cin.eof()) {
        break;
      }
      FormulaParser formula(line);
      TseitinTransformer transformer(formula.getTreeRoot());
      std::vector<std::vector<int>> cnf = transformer.transform();
//      std::cout << transformer.cnfString() << std::endl;
      DPLL dpll;
      std::unordered_set<int> variables;
      for(int i = 0; i < transformer.getVarNum(); i++){
        variables.insert(i+1);
      }
      std::unordered_map<int,bool> assignMap;
      if(dpll.solve(cnf,assignMap,variables)){
        std::cout << "sat" << std::endl;
      }else{
        std::cout << "unsat" << std::endl;
      }
    } catch(const char* msg){
      std::cout << msg << std::endl;
    }
  }
}
