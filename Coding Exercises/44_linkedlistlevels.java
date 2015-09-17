//Given binary tree design algorithm to return a linked list of each level

class Solution{
	static void createLevelLinkedLists(binaryTree root, ArrayList<LinkedList<binaryTree>> lists, int level) {
		if(root = null) return;
		
		LinkedList<binaryTree> list = null;
		if(lists.size() == level){
			list = new LinkedList<binaryTree>();
			lists.add(list);
		} else {
			list = lists.get(level);
		}
		list.add(root);
		createLevelLinkedLists(root.left, lists, level + 1);
		createLevelLinkedLists(root.right, lists, level + 1);
	}
}