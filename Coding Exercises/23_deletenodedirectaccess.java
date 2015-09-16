//Delete a node when you only have access directly to that node.

import java.util.*;

class Solution{

    public static void deleteNode(Node node){
        node.data = node.next.data;
        node.next = node.next.next;
    }

    public static void main(String args[]){
        Node head = new Node(1);
        head.appendToTail(2);
        head.appendToTail(3);
        head.appendToTail(4);
        head.appendToTail(5);

        Node candidate = head.next.next.next;

        deleteNode(candidate);

        while(head.next != null){
            System.out.println(head.data);
            head = head.next;
        }
        System.out.println(head.data);

    }
}