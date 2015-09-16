//Find the kth to last element in a singly linked list

import java.util.*;

class Solution{
    
    public Node nthToLast(Node head, int k){
        if(k <= 0) return null;

        Node p1 = head;
        Node p2 = head;

        for(int i = 0; i < k -1; i++){
            if(p2 == null) return null;
            p2 = p2.next;            
        }
        if(p2 == null) return null;

        while(p2.next != null){
            p1 = p1.next;
            p2 = p2.next;
        }
        return p1;
    }

    public static void main(String args[]){
        Node head = new Node(1);
        head.appendToTail(2);
        head.appendToTail(3);
        head.appendToTail(4);
        head.appendToTail(5);

        Solution pls = new Solution();
        Scanner reader = new Scanner(System.in);
        int k = reader.nextInt();

        Node kthNode = pls.nthToLast(head, k);

        if(kthNode == null){
            System.out.println("Out of bounds");
        }

        else System.out.println(kthNode.data);
    }
}