//MxN matrix. If element is 0, its entire row and column are zero.

import java.util.*;

class Solution{

    public static void main(String[] args){
        Scanner reader = new Scanner(System.in);
        int M = reader.nextInt();
        int N = reader.nextInt();
        int[][] array = new int[M][N];
        boolean rowZero = false;
        boolean colZero = false;
        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                array[i][j] = reader.nextInt();
            }
        }
        for(int i = 0; i < M; i++){
            if(array[i][0] == 0)
                colZero = true;
        }

        for(int j = 0; j < N; j++){
            if(array[0][j] == 0)
                rowZero = true;
        }

        for(int i = 1; i < M; i++){
            for(int j = 0; j < N; j++){
                if(array[i][j] == 0){
                    array[i][0] = 0;
                    array[0][j] = 0;
                }
            }
        }

        for(int i = 1; i < M; i++){
            if(array[i][0] == 0){
                for(int j = 0; j < N; j++){
                    array[i][j] = 0;
                }
            }
        }

        for(int j = 1; j < N; j++){
            if(array[0][j] == 0){
                for(int i = 0; i < M; i++){
                    array[i][j] = 0;
                }
            }
        }
        
        if(rowZero){
            for(int j = 0; j < N; j++){
                array[0][j] =0;
            }
        }

        if(colZero){
            for(int i = 0; i < M; i++){
                array[i][0] = 0;
            }
        }


        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                System.out.print(array[i][j]);
                }
                System.out.println();
            }
        }

    }
