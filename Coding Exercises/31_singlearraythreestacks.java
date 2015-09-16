//Use one array to implement 3 stacks

class Solution{

    int stackSize = 100;
    int[] buffer = new int[stackSize * 3];
    int[] stackPointer = {-1,-1,-1};

    void push(int stackNum, int value) throws Exception {
        if(stackPointer[stackNum] + 1 >= stackSize]){
            throw new FullStackException();
        }
        stackPointer[stackNum]++;
        buffer[absTopOfStack(stackNum)] = value;
    }

    int pop(int stackNum) throws Exception {
        if(isEmpty(stackNum)) {
            throw new EmptyStackException();
        }
        int value = buffer[absTopOfStack(stackNum)];
        buffer[absTopOfStack(stackNum)] = 0;
        stackPointer[stackNum]--;
        return value;
    }

    int peek(int stackNum){
        if(isEmpty stackNum){
            throw new EmptyStackException();
        }
        int index = absTopOfStack(stackNum);
        return buffer[index];
    }
}