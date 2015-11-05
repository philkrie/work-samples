//See if binary tree is balanced

import java.util.*;

class Solution {
	
	public static int getHeight(binaryTree tree){
		if(tree == null) return 0;
		return Math.max(getHeight(tree.left),
						getHeight(tree.right)) + 1;
	}
	
	public static boolean checkBalance(binaryTree tree){
		if(tree == null) return true;
		
		int heightDiff = getHeight(tree.left) - getHeight(tree.right);
		if(Math.abs(heightDiff) > 1){
			return false;
		} else {
			return checkBalance(tree.left) && checkBalance(tree.right);
		}
	}
}