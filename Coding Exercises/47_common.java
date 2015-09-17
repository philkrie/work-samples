//Find common ancestor of two nodes

class Solution{
	
	public static boolean covers(binaryTree root, binaryTree p){
		if(root == null) return false;
		if(root == p) return true;
		return covers(root.left, p) || covers(root.right, p);
	}
	
	public static binaryTree findCommon(binaryTree root, binaryTree p, binaryTree q){
		if(root == null) return root;
		if(root == p || root == q) return root;
		
		boolean is_p_left = covers(root.left, p);
		boolean is_q_left = covers(root.left, q);
		
		if(is_p_left != is_q_left) return root;
		
		binaryTree child = is_p_left ? root.left : root.right;
		return findCommon(child, p, q);
	}
}