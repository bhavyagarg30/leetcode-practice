
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {

        // Both trees are empty
        if (p == NULL && q == NULL)
            return true;

        // One tree is empty
        if (p == NULL || q == NULL)
            return false;

        // Check node values
        if (p->val != q->val)
            return false;

        // Compare left and right subtrees
        return isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};
