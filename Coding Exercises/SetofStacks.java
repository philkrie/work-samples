import java.util.Stack;
import java.util.ArrayList;

class SetofStacks {
	ArrayList<Stack<Integer>> stacks = new ArrayList<Stack<Integer>>();
	public void push(int v){
		Stack<Integer> last = getLastStack();
		if(last != null && !isFull(last)){
			last.push(v);
		} else {
			Stack stack = new Stack<Integer>();
			stack.setSize(100);
			stack.push(v);
			stacks.add(stack);
		}
	}
	public Integer pop(){
		Stack<Integer> last = getLastStack();
		int v = last.pop();
		if(last.size() == 0) stacks.remove(stacks.size() - 1);
		return v;
	}
	
	Stack<Integer> getLastStack(){
		Stack<Integer> last = stacks.get(stacks.size() - 1);
		return last;
	}
	
	static boolean isFull(Stack<Integer> stack){
		if(stack.size() == 100){
			return true;
		} else {
			return false;
		}
	}
}

//poop