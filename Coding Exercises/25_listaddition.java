import java.util.*;

class Solution{

    public static Node add(Node x, Node y){
        Node answer = null;
        Node n = null;
        boolean carry = false;
        while(x != null && y != null){
            int value = carry ? x.data + y.data + 1:x.data + y.data;
            carry = false;
            if(value > 9){
                value = value%10;
                carry = true;
            }
            if(answer == null){
                answer = new Node(value);
                n = answer;
            } else {
                n.next = new Node(value);
                n = n.next;
            }
            x = x.next;
            y = y.next;
        }
        return answer;
    }

    public static void main(String args[]){
        Node x = new Node(7);
        x.appendToTail(1);
        x.appendToTail(6);
        Node y = new Node(5);
        y.appendToTail(9);
        y.appendToTail(2);

        Node answer = add(x, y);

        while(answer != null){
            System.out.println(answer.data);
            answer = answer.next;
        }
    }
}