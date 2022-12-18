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

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

TreeNode::~TreeNode() {
  // your code starts here
  delete leftChild;
  delete rightChild;
}
