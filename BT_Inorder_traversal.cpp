//binary tree inorder traversal(easy)
#include <iostream>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {} };
void inorderTraversalHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    inorderTraversalHelper(root->left, result);
    result.push_back(root->val);
    inorderTraversalHelper(root->right, result); }
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    inorderTraversalHelper(root, result);
    return result;}
void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " "; }
    cout << endl;}
  int main() {
    TreeNode* root1 = new TreeNode(1);
    root1->right = new TreeNode(2);
    root1->right->left = new TreeNode(3);
    vector<int> result1 = inorderTraversal(root1);
    cout << "Inorder Traversal Example 1: ";
    printVector(result1);
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2, new TreeNode(4), new TreeNode(5, new TreeNode(6), new TreeNode(7)));
    root2->right = new TreeNode(3, nullptr, new TreeNode(8, new TreeNode(9), nullptr));
    vector<int> result2 = inorderTraversal(root2);
    cout << "Inorder Traversal Example 2: ";
    printVector(result2);
    return 0;}
