 //Merge M and N within a certain range i and j in N
 
 class Solution{
	int updateBits(int n, int m, int i, int j){
		int allOnes = ~0;
		
		int left = allOnes << (j+1);
		
		int right = ((1 << i) - 1);
		
		int mask = left | right;
		
		int result = mask & N;
		
		m = m << i;
		
		result = result | m;
	}
 }