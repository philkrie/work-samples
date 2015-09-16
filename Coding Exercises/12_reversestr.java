//Reverse a string

import java.util.*;
import java.lang.*;

class Solution{

    public static void main(String[] args){
        String word = args[0];
        char[] array = new char[word.length()];
        for(int i = 0; i < word.length()/2; i++){
            array[i] = word.charAt(word.length()-1 - i);
            array[word.length() - 1 - i] = word.charAt(i);
        } 
        String answer = new String(array);
        System.out.println(answer);

    }
}