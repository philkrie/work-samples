public Node seekCorruption(Node head){
    Node slow = head;
    Node fast = head;

    do{
        slow = slow.next;
        fast = fast.next.next; 
    } while(slow != fast);
    
    fast = head;

    while(slow != fast){
        slow = slow.next;
        fast = fast.next;
    }

    return fast;
}