
class Solution {
public:
    int maxDepth(TreeNode* root) {

        // If tree is empty
        if (root == NULL)
            return 0;

        // Find depth of left and right subtrees
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        // Return maximum depth + current node
        return 1 + max(left, right);
    }
};
