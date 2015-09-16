import java.util.*;
class Solution{

    public static boolean isPalindrome(Node head){
        Node slow = head;
        Node fast = head;
        
        Stack<Integer> stack = new Stack<Integer>();

        while(fast.next != null && fast != null){
            stack.push(slow.data);
            slow = slow.next;
            fast = fast.next.next;
        }

        if(fast != null){
            slow = slow.next;
        }

        while(slow != null){
            int pls = stack.pop().intValue();

            if(pls != slow.data){
                return false;
            }
            slow = slow.next;
        }
        return true;
    }

    public static void main(String args[]){
        Node head = new Node(1);
        head.appendToTail(2);
        head.appendToTail(1);
        head.appendToTail(4);
        head.appendToTail(5);
        head.appendToTail(4);
        head.appendToTail(3);
        head.appendToTail(2);
        head.appendToTail(1);

        if(isPalindrome(head)){
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    }   
}