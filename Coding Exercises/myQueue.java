//Queue class that utilizes two stacks
import java.util.Stack;

public class myQueue{
	Stack<Integer> inbox;
	Stack<Integer> outbox;
	
	public myQueue(){
		inbox = new Stack<Integer>();
		outbox = new Stack<Integer>();
	}
	
	public void enqueue(int data){
		inbox.push(data);
	}
	
	public int dequeue(int data){
		if(outbox.isEmpty()){
			for(int i = 0; i < inbox.size(); i++){
				int value = inbox.pop();
				outbox.push(value);
			}
		}
		return outbox.pop();
	}
}