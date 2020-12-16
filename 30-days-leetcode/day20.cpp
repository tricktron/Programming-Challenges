#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  TreeNode* bstFromPreorder(vector<int> &preorder) {
    TreeNode* node = new TreeNode(preorder[0]);
    TreeNode* root = node;
    TreeNode* parent;
    for (int i = 1; i < preorder.size(); i++) {
      node = root;
      int val = preorder[i];
      while (node != NULL) {
        parent = node;
        if (val < node->val) {
          node = node->left;
        } else {
          node = node->right;
        }
      }
      if (val < parent->val) {
        parent->left =  new TreeNode(val);
      } else
        parent->right = new TreeNode(val);
    }
    return root;
  }

  TreeNode* insertNode(TreeNode *root, int val) {
      if (root == NULL) root = new TreeNode(val);
      else if (val < root->val) root->left = insertNode(root->left, val);
      else root->right = insertNode(root->right, val);
      return root;
  }
};

/* class Solution {
public:
    TreeNode* constructBinTree(TreeNode *root, int &cval) {
        if(root==NULL) {
            root=new TreeNode(cval);
            
        } else if(cval < root->val) {
            root->left = constructBinTree(root->left, cval);
        } else if( cval> root->val) {
            root->right = constructBinTree(root->right, cval);
        }
        return root;
        
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode *root = constructBinTree(root,preorder[0]);;
        for(int i = 1; i<preorder.size() ;i++) {
            constructBinTree(root,preorder[i]);
        }
        return root;
    }
    
}; */

int main() {
    Solution s;
    vector<int> v = {8, 5, 1, 7, 10, 12};
    cout << s.bstFromPreorder(v) << endl;
    return 0;
}