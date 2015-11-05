import java.util.Stack;

public class minstack extends Stack<Integer>{
	Stack<Integer> s2;
	minstack() {
		s2 = new Stack<Integer>();
	}
	
	public void push(int data){
		if(data < min()){
			s2.push(data);
		}
		super.push(data);
	}
	
	public Integer pop(){
		int value = super.pop();
		if(value == min()){
			s2.pop();
		}
		return value;
	}
	int min(){
		if(s2.isEmpty()){
			return Integer.MAX_VALUE;
		} else {
			return s2.peek();
		}
	}
}