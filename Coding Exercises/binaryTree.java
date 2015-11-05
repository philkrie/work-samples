public class binaryTree{
	binaryTree left;
	binaryTree right;
	int value;
	
	public binaryTree(int root){
		this.value = root;
		this.left = null;
		this.right = null;
	}
	
	public void addLeft(binaryTree n){
		this.left = n;
	}
	
	public void addRight(binaryTree n){
		this.right = n;
	}
	
	public binaryTree getLeft(){
		return this.left;
	}
	
	public binaryTree getRight(){
		return this.right;
	}
	
	public void setValue(int value){
		this.value = value;
	}
	
	public int getValue(){
		return this.value;
	}
	
}

