#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  // your code starts here
  return content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  leftChild = lChild;
  rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if(getContent() == "+"){
    return getLeftChild()->evaluate(assignment) | getRightChild()->evaluate(assignment);
  }else if(getContent() == "*"){
    return getLeftChild()->evaluate(assignment) & getRightChild()->evaluate(assignment);
  }else{
    return !getLeftChild()->evaluate(assignment);
  }
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if(getContent() == "1"){
    return true;
  }else{
    return false;
  }
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if(!assignment.count(getContent())){
    throw "Error: incomplete assignment";
  }
  return assignment.at(getContent());
}

TreeNode::~TreeNode() {
  // your code starts here
  delete leftChild;
  delete rightChild;
}
