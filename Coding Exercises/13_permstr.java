//Are two string permutations?

import java.util.*;

class Solution{

    public static void main(String[] args){
        Scanner reader = new Scanner(System.in);
        String first = reader.nextLine();
        String second = reader.nextLine();
        if(first.length() != second.length()){
            System.out.println("NOT PERMUTATIONS");
        } else {
            int[] array1 = new int[128];
            int[] array2 = new int[128];
            int n = first.length();
            for(int i = 0; i<n; i++){
                array1[(int)first.charAt(i)]++;
                array2[(int)second.charAt(i)]++;
            }

            for(int i = 0; i<128; i++){
                if(array1[i] != array2[i]){
                    System.out.println("NOT PERMUTATION");
                    break;
                }
                if(i == 127){
                    System.out.println("PERMUTATION");
                } 
            }
        }
    }
}