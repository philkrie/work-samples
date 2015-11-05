//Create a minimal BST using a sorted array

class Solution{
	public static minBinaryTree(int[] arr, int start, int end){
		if(end < start) return null;
		int mid = (start + end) / 2;
		binaryTree n = new binaryTree(arr[mid]);
		n.left = minBinaryTree(arr, start, mid - 1);
		n.right = minBinaryTree(arr, mid + 1, end);
		return n;
	}
}