//
// Created by root on 11/2/18.
//
#include "binarytree.h"

// https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Binary_tree.svg/192px-Binary_tree.svg.png

TreeNode *createTree1() {
    TreeNode *R = new TreeNode(2);
    R->left = new TreeNode(7);
    R->right = new TreeNode(5);
    R->right->right = new TreeNode(9);
    R->right->right->left = new TreeNode(4);

    R->left->left = new TreeNode(2);
    R->left->right = new TreeNode(6);
    R->left->right->left = new TreeNode(5);
    R->left->right->right = new TreeNode(11);
    return R;
}

// complete tree
TreeNode *createTree2(){
    /*0,1,2,3...  ==> left 2i, right 2i+1*/
    vector<int> v={INT_MAX,70, 77,60, 1,8,9,14, 3,4,5,6,2,7,15,13};
    int L=v.size();
    vector<TreeNode*> vn(L);
    for (int i=L-1; i>0; i--) {
        vn[i] = new TreeNode(v[i]);
        if(2*i < L){
            vn[i]->left = vn[2*i];
        }
        if(2*i+1 < L){
            vn[i]->right = vn[2*i+1];
        }
    }
    return vn[1];
};

TreeNode *createTree3(){
    /*0,1,2,3...  ==> left 2i, right 2i+1*/
    vector<int> v={INT_MAX,70, 77,60, 1,8,9,14, 3,4,5,6,2,7,15};
    int L=v.size();
    vector<TreeNode*> vn(L);
    for (int i=L-1; i>0; i--) {
        vn[i] = new TreeNode(v[i]);
        if(2*i < L){
            vn[i]->left = vn[2*i];
        }
        if(2*i+1 < L){
            vn[i]->right = vn[2*i+1];
        }
    }
    return vn[1];
};

TreeNode *createTree4(){
    /*0,1,2,3...  ==> left 2i, right 2i+1*/
    vector<int> v={INT_MAX,70, 77,60, 1,8,9,14, 3,4,5,6,2,7,15};
    int L=v.size();
    vector<TreeNode*> vn(L);
    for (int i=L-1; i>0; i--) {
        vn[i] = new TreeNode(v[i]);
        if(2*i < L){
            vn[i]->left = vn[2*i];
        }
        if(2*i+1 < L){
            vn[i]->right = vn[2*i+1];
        }
    }
    return vn[1];
};



// Segment Tree
/////////////////////////////////////////////////////////////////////////////////
// https://www.geeksforgeeks.org/segment-tree-efficient-implementation/
/*
```
       15
   10       5
 9   1   2   3
4 5
```
*/
TreeNode *build_segment_tree_algo1(const vector<int>& v){ // sum segment tree
    int L=v.size();
    vector<TreeNode*> vn(L*2);
    for(int i=0;i<L;i++){
        vn[i+L] = new TreeNode(v[i]);
    }
    for(int i=L-1;i>0;i--){
        int t=vn[2*i]->val + vn[2*i+1]->val;
        vn[i] = new TreeNode(t);
        vn[i]->left = vn[2*i];
        vn[i]->right = vn[2*i+1];
    }
    return vn[1];
};

void build_segment_tree_algo2_rec(const vector<int>& v,
                                  vector<TreeNode*>& tree, int tid, int h, int t) {
    if(h==t){
        tree[tid]=new TreeNode(v[h]);
        return;
    }
    int mid = h + (t - h) / 2;   // post order traversal
    build_segment_tree_algo2_rec(v, tree, 2 * tid + 1, h,     mid);
    build_segment_tree_algo2_rec(v, tree, 2 * tid + 2, mid + 1, t);

    // merge build results
    // tree[tid] = merge(tree[2 * tid + 1], tree[2 * tid + 2]);
    tree[tid] = new TreeNode(tree[2 * tid + 1]->val +
            tree[2 * tid + 2]->val);
    // for printing purpose
    tree[tid]->left = tree[2 * tid + 1];
    tree[tid]->right = tree[2 * tid + 2];
}

TreeNode* build_segment_tree_algo2(const vector<int>& v){ // sum segment tree
    vector<TreeNode*> tree(4*v.size());
    build_segment_tree_algo2_rec(v, tree, 0, 0, v.size()-1);
    return tree[0];
};



// Print Tree
/////////////////////////////////////////////////////////////////////////////////
int dep_by_node(TreeNode* n){
    return n==0?0:max(dep_by_node(n->left), dep_by_node(n->right))+1;
}

void print_binary_tree_horizontal_dfs(TreeNode* n, vector<vector<string>>& r, int i, int j, int c){
    if(!n) return;
    r[i][j] = to_string(n->val); // preorder traversal
    int distance = (c+1)/2;
    print_binary_tree_horizontal_dfs(n->left, r, i+1, j-distance, c/2);
    print_binary_tree_horizontal_dfs(n->right, r, i+1, j+distance, c/2);
}

void print_binary_tree_horizontal(TreeNode* root){
    cout << string(80,'*') << endl;
    int R=dep_by_node(root), C=(1<<R)-1;
    if(R==0) return;
    vector<vector<string>> res(R, vector<string>(C, "  "));
    print_binary_tree_horizontal_dfs(root,res,0,C/2,C/2);
    for(auto vs: res){
        for(string& s: vs)
            cout << s ;
        cout << endl;
    }
    cout << string(80,'*') << endl;
}

void print_binary_tree_horizontal2(TreeNode* root) {
    cout << string(80,'*') << endl;
    int R=dep_by_node(root), C=(1<<R)-1; // C=2^R-1
    if(R==0) return;
    vector<vector<string>> res(R, vector<string>(C, " "));
    print_binary_tree_horizontal_dfs(root,res,0,C/2,C/2);

    for(auto vs: res){
        for(string& s: vs)
            cout << s ;
        cout << endl;
    }
    cout << string(80,'*') << endl;
}



void print_binary_tree_vertical(TreeNode* root){

}



// reverse inorder traversal
////////////////////////////////////
// Function to print binary tree in 2D 
// It does reverse inorder traversal
const int SPACE_COUNT=6;
void print2DUtil(TreeNode *root, int space) {
    if (root == NULL)
        return;
    // Process right child first 
    print2DUtil(root->right, space+SPACE_COUNT); // Increase distance between levels
    // Print current node after space 
    cout << "\n" << string(space, ' ') << root->val << endl;
    // Process left child
    print2DUtil(root->left, space+SPACE_COUNT); // Increase distance between levels
}

// Wrapper over print2DUtil() 
void print2D(TreeNode *root){
    cout << string(80,'x') << endl;
    // Pass initial space count as 0 
    print2DUtil(root, 0);
    cout << string(80,'x') << endl;
}



void binarytree_test(){
    // https://www.geeksforgeeks.org/wp-content/uploads/segment-tree1.png
    vector<int> vi={1,3,5,7,9,11};
    TreeNode* r=build_segment_tree_algo2(vi);
    print_binary_tree_horizontal(r);

    // https://leetcode.com/media/original_images/segtree_example_1.png
    vi={18, 17, 13, 19, 15, 11, 20, 12, 33, 25};
    r=build_segment_tree_algo2(vi);
    print_binary_tree_horizontal(r);
    print2D(r);

    vi={4,5,6,7};
    r=build_segment_tree_algo2(vi);
    print2D(r);


    vi={1,2,3,4,5};
    r=build_segment_tree_algo1(vi);
    print_binary_tree_horizontal(r);

    r=build_segment_tree_algo2(vi);
    print_binary_tree_horizontal(r);
}