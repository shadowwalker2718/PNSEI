package practice.databricks;

import foundation.TreeHelper;
import foundation.TreeNodeWithParent;

import java.util.ArrayList;

// According to the relation of `currently traversing node root` and `previously traversed node`, there are three cases:
// 1. prev == root.parent
// 2. prev == root.left
// 3. prev == root.right
public class BinaryTreeO1Traverse {

    public ArrayList<TreeNodeWithParent> traverse_postorder(TreeNodeWithParent root){
        ArrayList<TreeNodeWithParent> res = new ArrayList<>();
        TreeNodeWithParent prev = null;
        while(root!=null){
            if (prev==root.parent){ // start..go to the left side
                if (root.left!=null){
                    prev = root;
                    root = root.left;
                } else {
                    prev = null;
                }
            }
            if(prev == root.left) { // left subtree is done, now start to traverse right subtree
                if (root.right != null){
                    prev = root;
                    root = root.right;
                } else { // right subtree is done
                    prev = null;
                }
            }
            if (prev == root.right) { // right subtree is done, track back upward
                res.add(root); /////////////
                prev = root;
                root = root.parent;
            }
        }
        return res;
    }

    public ArrayList<TreeNodeWithParent> traverse_preorder(TreeNodeWithParent root){
        ArrayList<TreeNodeWithParent> res = new ArrayList<>();
        TreeNodeWithParent prev = null;
        while(root!=null){
            if (prev==root.parent){ // start..go to the left subtree downwards
                res.add(root); /////////////
                if (root.left!=null){
                    prev = root;
                    root = root.left;
                } else {
                    prev = null;
                }
            }
            if(prev == root.left) { // left subtree is done, now start to traverse right subtree downwards
                if (root.right != null){
                    prev = root;
                    root = root.right;
                } else { // right subtree is done
                    prev = null;
                }
            }
            if (prev == root.right) { // right subtree is done, track back upwards
                prev = root;
                root = root.parent;
            }
        }
        return res;
    }

    public ArrayList<TreeNodeWithParent> traverse_inorder(TreeNodeWithParent root){
        ArrayList<TreeNodeWithParent> res = new ArrayList<>();
        TreeNodeWithParent prev = null;
        while(root!=null){
            if (prev==root.parent){ // start..go to the left subtree downwards
                if (root.left!=null){
                    prev = root;
                    root = root.left;
                } else {
                    prev = null;
                }
            }
            if(prev == root.left) { // left subtree is done, now start to traverse right subtree downwards
                res.add(root); /////////////
                if (root.right != null){
                    prev = root;
                    root = root.right;
                } else { // right subtree is done
                    prev = null;
                }
            }
            if (prev == root.right) { // right subtree is done, track back upwards
                prev = root;
                root = root.parent;
            }
        }
        return res;
    }

    // right down \, left <--
    public ArrayList<TreeNodeWithParent> traverse_reverse_postorder(TreeNodeWithParent root){
        ArrayList<TreeNodeWithParent> res = new ArrayList<>();
        TreeNodeWithParent prev = null;
        while(root!=null){
            if (prev==root.parent){ // start..go to the left side
                res.add(root); /////////////
                if (root.right!=null){
                    prev = root;
                    root = root.right;
                } else {
                    prev = null;
                }
            }
            if(prev == root.right) { // left subtree is done, now start to traverse right subtree
                if (root.left != null){
                    prev = root;
                    root = root.left;
                } else { // right subtree is done
                    prev = null;
                }
            }
            if (prev == root.left) { // right subtree is done, track back upward
                prev = root;
                root = root.parent;
            }
        }
        return res;
    }

    public static void main(String[] args){
        final TreeNodeWithParent root = TreeHelper.CreateTreeNodeWithParent1();
        BinaryTreeO1Traverse b = new BinaryTreeO1Traverse();
        ArrayList<TreeNodeWithParent> res = b.traverse_reverse_postorder(root);
        for (TreeNodeWithParent n: res) {
            System.out.println(n.val);
        }
    }


}
