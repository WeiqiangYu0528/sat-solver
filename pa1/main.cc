#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  // your code starts here
    char delimiter = ';';
    int semicolon_inx = line.find(delimiter);
    if (semicolon_inx == std::string::npos){
        throw "Error: invalid input";
    }
    formulaStr = line.substr(0,semicolon_inx);
    assignmentStr = line.substr(semicolon_inx+1);
    FormulaParser formula(formulaStr);
    AssignmentParser assignment(assignmentStr);
    TreeNode * root = formula.getTreeRoot();
    bool ans = root->evaluate(assignment.parseAssignment());
    if(ans){
        std::cout << '1' << std::endl;
    }else{
        std::cout << '0' << std::endl;
    }
    delete root;
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
    try {
        getline(std::cin, line);
        if (std::cin.eof()) {
            break;
        }
        parseLine(line, formulaStr, assignmentStr);
      } catch(const char* msg){
        std::cout << msg << std::endl;
      }
  }
}
