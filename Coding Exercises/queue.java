class Queue{
    Node first, last;

    void enqueue(int item){
        if(first == null){
            last = new Node(item);
            first = last;
        } else {
            last.next = new Node(item);
            last = last.next;
        }
    }

    int dequeue(){
        if(first != null){
            int item = first.data;
            first = first.next;
            if(first == null) last = null;
            return item;
        }
        return -1;
    }
}