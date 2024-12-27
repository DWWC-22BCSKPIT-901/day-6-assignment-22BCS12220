//Construct binary tree form preorder and inorder traversal(medium.) 
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
TreeNode* buildTreeHelper(const vector<int>& preorder, int preorderStart, int preorderEnd,
                          const vector<int>& inorder, int inorderStart, int inorderEnd,
                          unordered_map<int, int>& inorderIndexMap) {
    if (preorderStart > preorderEnd || inorderStart > inorderEnd) {
        return nullptr;
    }
    int rootVal = preorder[preorderStart];
    TreeNode* root = new TreeNode(rootVal);
    int rootIndex = inorderIndexMap[rootVal];
    int leftSubtreeSize = rootIndex - inorderStart;
    root->left = buildTreeHelper(preorder, preorderStart + 1, preorderStart + leftSubtreeSize,
                                 inorder, inorderStart, rootIndex - 1, inorderIndexMap);
    root->right = buildTreeHelper(preorder, preorderStart + leftSubtreeSize + 1, preorderEnd,
                                  inorder, rootIndex + 1, inorderEnd, inorderIndexMap);
    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> inorderIndexMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inorderIndexMap[inorder[i]] = i;
    }

    return buildTreeHelper(preorder, 0, preorder.size() - 1,
                           inorder, 0, inorder.size() - 1, inorderIndexMap);
}
void printLevelOrder(TreeNode* root) {
    if (!root) return;
    vector<TreeNode*> currentLevel{root};
    while (!currentLevel.empty()) {
        vector<TreeNode*> nextLevel;
        for (TreeNode* node : currentLevel) {
            if (node) {
                cout << node->val << " ";
                nextLevel.push_back(node->left);
                nextLevel.push_back(node->right);
            } else {
                cout << "null ";
            }
        }
        currentLevel = nextLevel;
    }
    cout << endl;
}

int main() {
    vector<int> preorder1 = {3, 9, 20, 15, 7};
    vector<int> inorder1 = {9, 3, 15, 20, 7};
    TreeNode* root1 = buildTree(preorder1, inorder1);
    cout << "Tree for Example 1: ";
    printLevelOrder(root1);

    vector<int> preorder2 = {-1};
    vector<int> inorder2 = {-1};
    TreeNode* root2 = buildTree(preorder2, inorder2);
    cout << "Tree for Example 2: ";
    printLevelOrder(root2);

    return 0;
}
