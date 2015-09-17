//Check if BST is BST

boolean checkBST(binaryTree root, int min, int max){
	if(root == null){
		return true;
	}
	
	if((min != null && root.data <= min) || (max != null && root.data > max)){
		return false;
	}
	
	if(!checkBST(root.left, min, n.data) || !checkBST(root.right, n.data, max)) {
		return false;
	} 
	return true;
}