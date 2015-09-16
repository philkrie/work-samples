//Remove duplicates from an unsorted linked list

import java.util.*;

class Solution{

    public static void main(String[] args){
        Node head = new Node(1);
        head.appendToTail(1);
        head.appendToTail(0);
        head.appendToTail(0);
        head.appendToTail(1);

        Node n = head;
        Node prev = null;

        ArrayList<Integer> list = new ArrayList<Integer>();

        while(n != null){
            if(list.contains(n.data)){
                prev.next = n.next;
            } else {
                list.add(n.data);
                prev = n;
            }
            n = n.next;
        }


        while(head != null){
            System.out.println(head.data);
            head = head.next;
        }
    }
}