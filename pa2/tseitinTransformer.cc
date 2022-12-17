#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  if(subRoot == nullptr){
    return -1;
  }
  int curID =  varIdCounter++;
  int leftID = transSubformula(subRoot->getLeftChild());
  int rightID = transSubformula(subRoot->getRightChild());
  std::string content = subRoot->getContent();
  if( content == "+") {
    addOrEq(curID, leftID, rightID);
  }else if(content == "*"){
    addAndEq(curID, leftID, rightID);
  }else if(content == "-"){
    addNegEq(curID, leftID);
  }else{
    if(!varIdTable.count(content)){
      varIdTable[content] = curID;
    }else{
      curID = varIdTable.at(content);
      varIdCounter--;
    }
  }
  return curID;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  std::vector<int> clause1 = {-curID,-childID};
  std::vector<int> clause2 = {curID,childID};
  cnf.push_back(clause1);
  cnf.push_back(clause2);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> clause1 = {-curID,leftID,rightID};
  std::vector<int> clause2 = {curID,-leftID};
  std::vector<int> clause3 = {curID,-rightID};
  cnf.push_back(clause1);
  cnf.push_back(clause2);
  cnf.push_back(clause3);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> clause1 = {-curID, leftID};
  std::vector<int> clause2 = {-curID, rightID};
  std::vector<int> clause3 = {curID, -leftID, -rightID};
  cnf.push_back(clause1);
  cnf.push_back(clause2);
  cnf.push_back(clause3);
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  transSubformula(formulaRoot);
  cnf.push_back({1});
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  for(const std::vector<int>& vec: cnf){
    result += "[";
    for(auto it = vec.begin();it != vec.end(); ++it){
      if(it - vec.begin() > 0){
        result += ",";
      }
      result += std::to_string(*it);
    }
    result += "]";
  }
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return varIdCounter - 1;
}
