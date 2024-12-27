//Populating next right pointers in each node(Hard).
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
TreeNode* buildTreeHelper(const vector<int>& inorder, int inorderStart, int inorderEnd,
                          const vector<int>& postorder, int postorderStart, int postorderEnd,
                          unordered_map<int, int>& inorderIndexMap) {
    if (inorderStart > inorderEnd || postorderStart > postorderEnd) {
        return nullptr;
    }
    int rootVal = postorder[postorderEnd];
    TreeNode* root = new TreeNode(rootVal);
    int rootIndex = inorderIndexMap[rootVal];
    int leftSubtreeSize = rootIndex - inorderStart;
    root->left = buildTreeHelper(inorder, inorderStart, rootIndex - 1,
                                 postorder, postorderStart, postorderStart + leftSubtreeSize - 1, inorderIndexMap);
    root->right = buildTreeHelper(inorder, rootIndex + 1, inorderEnd,
                                  postorder, postorderStart + leftSubtreeSize, postorderEnd - 1, inorderIndexMap);
    return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> inorderIndexMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inorderIndexMap[inorder[i]] = i;
    }
    return buildTreeHelper(inorder, 0, inorder.size() - 1,
                           postorder, 0, postorder.size() - 1, inorderIndexMap);
}
void printLevelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node) {
            cout << node->val << " ";
            q.push(node->left);
            q.push(node->right);
        } else {
            cout << "null ";
        }
    }
    cout << endl;
}
int main() {
    vector<int> inorder1 = {9, 3, 15, 20, 7};
    vector<int> postorder1 = {9, 15, 7, 20, 3};
    TreeNode* root1 = buildTree(inorder1, postorder1);
    cout << "Tree for Example 1: ";
    printLevelOrder(root1);

    vector<int> inorder2 = {-1};
    vector<int> postorder2 = {-1};
    TreeNode* root2 = buildTree(inorder2, postorder2);
    cout << "Tree for Example 2: ";
    printLevelOrder(root2);
    return 0;
}
