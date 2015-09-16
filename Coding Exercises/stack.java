class Stack{
    Node top;

    Object pop(){
        if(top != null){
            int item = top.data;
            top = top.next;
            return item;
        }
        return null;
    }

    void push(int item){
        Node t = new Node(item);
        t.next = top;
        top = t;
    }

    int peek(){
        return top.data;
    }
}