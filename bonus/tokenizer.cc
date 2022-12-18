#include "tokenizer.h"


Tokenizer::Tokenizer(std::string ln) {
  // complete the constructor
  next = 0;
  size_t first_pos = ln.find_first_not_of(' ');
  ln.erase(0, first_pos);
  size_t last_pos = ln.find_last_not_of(' ');
  if(last_pos != std::string::npos && last_pos < ln.size() - 1){
    ln.erase(last_pos+ 1, std::string::npos);
  }
  input = ln;
  length = ln.size();
}

bool Tokenizer::advanceToken() {
  // your code starts here
  next++;
  if(hasToken()){
    return true;
  }else{
    return false;
  }
}

void Tokenizer::setPos(int pos) {
  next = pos;
}

bool Tokenizer::hasToken() const {
  // your code starts here
  if(next >= length){
    return false;
  }else{
    return true;
  }
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  Token resultToken;
  // your code starts there
  if(input[next] == ' '){
    advanceToken();
    return getToken();
  }else if(isalpha(input[next])){
    int start_pos = next;
    while(advanceToken() && isalnum(input[next])) {
      if (next - start_pos >= 10) {
        throw "Error: invalid input";
      }
    }
    resultToken.content = input.substr(start_pos, next - start_pos);
    resultToken.type = "VarName";
    next--;
  }else if(input[next]  == '+' || input[next] == '-' || input[next] == '*'){
    resultToken.content = input[next];
    resultToken.type = "Operator";
  }else if(input[next]  == '(' || input[next]  == ')' ){
    resultToken.content = input[next];
    resultToken.type = "Parenthesis";
  }else{
    throw "Error: invalid input";
  }
  return resultToken;
}

int Tokenizer::getPos() {
  return next;
}
