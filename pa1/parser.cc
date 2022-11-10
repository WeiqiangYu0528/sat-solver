#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm() {
  // your code starts here
  TreeNode * conjTerm = parseTerm();
  int pos = tknzr->getPos();
  if(tknzr->advanceToken() && tknzr->getToken().content == "*" && tknzr->advanceToken()){
      TreeNode * conjTerm2 = parseConjTerm();
      OperatorNode* multipleNode = new OperatorNode("*")  ;
      multipleNode->updateChildren(conjTerm,conjTerm2);
      return multipleNode;
  }else{
      tknzr->setPos(pos);
      return conjTerm;
  }
}

TreeNode *FormulaParser::parseTerm() {
  // your code starts here
  TreeNode* term;
  Token token = tknzr->getToken();
  if(token.type == "Constant"){
    ConstantNode* constNode = new ConstantNode( token.content);
    term = constNode;
  }else if(token.type == "VarName"){
    VariableNode* varNode = new VariableNode(token.content);
    term = varNode;
  }else if(token.content == "-"){
    OperatorNode* operNode = new OperatorNode("-");
    if(tknzr->advanceToken()){
      TreeNode* term2 = parseTerm();
      operNode->updateLeftChild(term2);
    }else{
      throw "Error: invalid input";
    }
    term = operNode;
  }else if(token.content == "("){
    if(!tknzr->advanceToken()){
      throw "Error: invalid input";
    }
    TreeNode* formula = parseFormula();
    if(!tknzr->advanceToken() || tknzr->getToken().content != ")") {
      throw "Error: invalid input";
    }
    term = formula;
  }else{
    throw "Error: invalid input";
  }
  return term;
}

TreeNode *FormulaParser::parseFormula() {
  // your code starts here
  TreeNode * formula = parseConjTerm();
  int pos = tknzr->getPos();
  if(tknzr->advanceToken() && tknzr->getToken().content == "+" && tknzr->advanceToken()){
    TreeNode * formula2 = parseFormula();
    OperatorNode* plusNode = new OperatorNode("+");
    plusNode->updateChildren(formula,formula2);
    return plusNode;
  }else{
    tknzr->setPos(pos);
    return formula;
  }
}

TreeNode * FormulaParser::getTreeRoot() {
  // your code starts here
  TreeNode * root = parseFormula();
  if(tknzr->advanceToken()){
    throw "Error: invalid input";
  }
  return root;
}

FormulaParser::~FormulaParser() {
  // your code starts here
  delete tknzr;
}

AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
  std::map<std::string, bool> results;
  // your code starts here
  while(tknzr->hasToken()){
    Token var = tknzr->getToken();
    bool value = false;
    if(var.type != "VarName" || !tknzr->advanceToken() ){
      throw "Error: invalid input";
    }
    Token semicolon = tknzr->getToken();
    if(semicolon.content != ":" || !tknzr->advanceToken() || tknzr->getToken().type != "Constant"){
      throw "Error: invalid input";
    }
    Token constant = tknzr->getToken();
    if(constant.content == "1") {
      value = true;
    }
    if(results.count(var.content) && results.at(var.content) != value){
      throw "Error: contradicting assignment";
    }
    results[var.content] = value;
    if(tknzr->advanceToken() && tknzr->getToken().content == ","){
      tknzr->advanceToken();
    }
  }
  return results;
}

AssignmentParser::~AssignmentParser() {
  // your code starts here
  delete tknzr;
}
