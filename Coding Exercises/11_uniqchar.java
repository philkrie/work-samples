//Determine if a string has all unique characters

import java.util.*;

class Solution {

    public static void main(String[] args){
        Scanner reader = new Scanner(System.in);
        String word = reader.nextLine();
        char[] array = new char[26];
        for(int i = 0; i<word.length(); i++){
            array[((int) word.charAt(i)) - 97]++;
            if(array[((int) word.charAt(i)) - 97] > 1){
                System.out.println("Not unique");
                break;
            }
            if(i == word.length() - 1)
                System.out.println("Unique");
        }
    }
}