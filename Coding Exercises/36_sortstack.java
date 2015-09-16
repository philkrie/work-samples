//Sort a stack in ascending order, at most one extra stack

import java.util.Stack;

class Solution{
	
	public static Stack<Integer> sort(Stack<Integer> s){
		Stack<Integer> r = new Stack<Integer>();
		while(!s.isEmpty()){
			int value = s.pop();
			while(!r.isEmpty() && value < r.peek()){
				s.push(r.pop());
			}
			r.push(value);
		}
		return r;
	}
	
	public static void main(String args[]){
		Stack<Integer> stack = new Stack<Integer>();
		stack.push(10);
		stack.push(9);
		stack.push(8);
		
		stack = sort(stack);
		
		for(int i = 0; i < 3; i++){
			System.out.println(stack.pop());
		}
	}
}