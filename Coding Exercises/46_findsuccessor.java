//Find the "next" node (in order successor) of a node in a tree. Assume you have parent link

class Solution{
	
	public static binaryTree findNextNode(binaryTree root){
		if(root.right != null){
			root = root.right;
			while(root.left != null){
				root = root.left;
			}
			return root;
		} else {
			while(root == root.parent.right){
				root = root.parent;
			}
			return root.parent;
		}
	}
}