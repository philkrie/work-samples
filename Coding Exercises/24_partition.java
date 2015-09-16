//Delete a node when you only have access directly to that node.

import java.util.*;

class Solution{

    public static Node partition(Node n, int x){
        Node tail = n;
        Node head = n;
        while(n != null){
            Node next = n.next;
            if(n.data < x){
                n.next = head;
                head = n;
            } else {
                tail.next = n;
                tail = n;
            }
            n = next;
        }
        tail.next = null;
        return head;
    }

    public static void main(String args[]){
        Node head = new Node(10);
        head.appendToTail(11);
        head.appendToTail(3);
        head.appendToTail(7);
        head.appendToTail(89);
        head.appendToTail(0);
        head.appendToTail(54);
        head.appendToTail(12);
        head.appendToTail(26);

        Scanner reader = new Scanner(System.in);
        int value = reader.nextInt();

        head = partition(head, value);

        while(head.next != null){
            System.out.println(head.data);
            head = head.next;
        }
        System.out.println(head.data);

    }
}