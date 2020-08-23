package foundation;

public class TreeHelper {
    // This is to construct a complete tree from an array
    public static TreeNodeWithParent CreateTreeNodeWithParent1(){
        final int[] array = {Integer.MAX_VALUE, 70, 77, 60, 1, 8, 9, 14, 3, 4, 5, 6, 2, 7, 15};
        final TreeNodeWithParent[] vn = new TreeNodeWithParent[array.length];
        for (int i = array.length-1; i>0; i--) {
            vn[i] = new TreeNodeWithParent(array[i]);
            if (2*i < array.length){
                vn[i].left = vn[2*i];
                vn[2*i].parent = vn[i];
            }
            if (2*i+1 < array.length){
                vn[i].right = vn[2*i+1];
                vn[2*i+1].parent = vn[i];
            }
        }
        return vn[1];
    }

    public static void main(String[] args){
        TreeNodeWithParent node = CreateTreeNodeWithParent1();
    }
}
