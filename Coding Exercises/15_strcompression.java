//Compress strings where multiple letters are.

import java.util.*;

class Solution{

    public static void main(String[] args){
        Scanner reader = new Scanner(System.in);
        String word = reader.nextLine();
        int newLength = 0;
        int currentCount = 0;
        for(int i = 0; i < word.length(); i++){
            if(i > 0){
               if(word.charAt(i-1) == word.charAt(i)){

               } else {
                newLength+=2;
               }
            } else {
                newLength+=2;
            }
        }
        System.out.println(newLength);
        if(newLength > word.length()){
            System.out.println(word);
        } else {
            char[] compress = new char[newLength];
            int j = 0;
            int count = 1;
            compress[j] = word.charAt(0);
            j++;
            for(int i = 1; i < word.length(); i++){
            
                    if(word.charAt(i-1) == word.charAt(i)){
                        count++;
                    } else {
                        compress[j] = Integer.toString(count).charAt(0);
                        count = 1;
                        compress[j+1] = word.charAt(i);
                        j+=2; 
                    }
            }
            compress[newLength - 2] = word.charAt(word.length() - 1);
            compress[newLength - 1] = Integer.toString(count).charAt(0);
            System.out.println(new String(compress));
        }
    }
}