import java.util.Scanner;
import java.io.IOException;


public class hw2 {
	
	public static void main(String[] args) throws IOException {
				
		Scanner stdin = new Scanner(System.in);
		int numGraphs;
		int numNodes;
		int numEdges;
		
		//First, we collect the information at the start for how many graphs there are
		numGraphs = stdin.nextInt();
		if (numGraphs == 0){
			System.exit(0);
		}
		
		//Then we enter the loop for each graph, gathering the number of nodes, edges, and each pair
		for (int i = 0; i < numGraphs; i++){
			System.out.println("graph number: " + (i+1));
			numNodes = stdin.nextInt();
			numEdges = stdin.nextInt();
			
			//Initialize adjacency matrix
			AdjacencyMatrix matrix = new AdjacencyMatrix(numNodes);
			
			//Initialize information array that holds shortest, longest, and # of paths
			int[][] information = new int[numNodes][3];
			information[0][0] = 0;
			information[0][1] = 0;
			information[0][2] = 1;
			
			//Set default values for the information array
			for (int j = 1; j < numNodes; j++){
				information[j][0] = numNodes;
				information[j][1] = -1;
				information[j][2] = 0;
			}
			
			//We parse through each of the graphs to create the matrix
			for (int j = 0; j < numEdges; j++){
				int node1 = stdin.nextInt();
				int node2 = stdin.nextInt();
					matrix.addEdge(node1, node2);
				}
			
			//iterate through the matrix in m*n time in order to determine shortest, longest, and # of paths
			for (int j = 1; j < numNodes + 1; j++) {
				for (int k = j+1; k < numNodes + 1; k++) {
					if (matrix.hasEdge(j, k)) {
						int min = information[j-1][0] + 1;
						int max = information[j-1][1] + 1;
						int num = information[j-1][2];
						
						//Compare longest and shortest paths and replace if necessary
						if (min < information[k-1][0]){
							information[k-1][0] = min;
						}
						
						if (max > information[k-1][1]){
							information[k-1][1] = max;
						}
						
						//Pass along path number to node
						information[k-1][2] += num;
					}
				}
			}
			System.out.println("Shortest path: " + information[numNodes-1][0]);
			System.out.println("Longest path: " + information[numNodes-1][1]);
			System.out.println("Number of paths: " + information[numNodes-1][2]);
			System.out.println("\n");

		}
	}
}
				
