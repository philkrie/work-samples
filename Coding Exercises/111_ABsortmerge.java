//Merge two sorted arrays A and B, where A has large enough buffer to take B.

class Solution{
	public static int[] mergeSortedArrays(int[] A, int[] B){
		//A and B are already sorted, A is large enough to contain itself and B.
		
		int[] helper = new int[A.length];
		int A_index = 0;
		int B_index = 0;
		
		for(int i = 0; i < helper.length; i++){
			while(B_index < B.length){
				if(A[A_index] >= B[B_index]){
					helper[i] = B[B_index];
					B_index++;
				} else {
					helper[i] = A[A_index];
					A_index++;
				}
			}
			
		}
		return helper;
	}
}