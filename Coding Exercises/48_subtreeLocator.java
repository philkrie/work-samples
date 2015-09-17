class Solution{
	public static boolean containsTree(binaryTree t1, binaryTree t2){
		if(t2 == null)
			return true;
		return subTree(t1, t2);
	}
	
	public static boolean subTree(binaryTree t1, binaryTree t2){
		if(t1 == null){
			return false;
		}
		
		if(t1.data == t2.data){
			if(matchTree(t1, t2)) return true;
		}
		return subTree(t1.left, t2) || subTree(t1.right, t2);
	}
	
	public static boolean matchTree(binaryTree t1, binaryTree t2){
		if(t1 == null && t2 == null) return true;
		if(t1 == null || t2 == null) return false;
		if(t1.data != t2.data) return false;
		return (matchTree(t1.left, t2.left) && matchTree(t1.right, t2.right));
	}
}