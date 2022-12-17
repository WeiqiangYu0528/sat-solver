#include "tseitinTransformer.h"
#include "satSolver.h"
#include "parser.h"
#include <iostream>
#include <vector>
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
      if(satCallingMiniSat(transformer.getVarNum(),cnf)){
        std::cout << "sat" << std::endl;
      }else{
        std::cout << "unsat" << std::endl;
      }
    } catch(const char* msg){
      std::cout << msg << std::endl;
    }
  }
}
