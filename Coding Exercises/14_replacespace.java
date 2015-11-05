//Change all spaces to %20

import java.util.*;

class Solution{

    public static void main(String[] args){
        Scanner reader =  new Scanner(System.in);
        String phrase = reader.nextLine();
        int length = reader.nextInt();
        char[] array = phrase.toCharArray();
        for(int i = 0; i < phrase.length(); i++){
            if(array[i] == ' '){
                for(int j = length - 1; j > i; j--){
                    array[j + 2] = array[j];
                }
                length += 2;
                array[i] = '%';
                array[i+1] = '2';
                array[i+2] = '0';
            }
        }
        phrase = new String(array);
        System.out.println(phrase);
    }
}