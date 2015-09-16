//Describes a matrix that describes adjacency
public class AdjacencyMatrix {
    int size;
    boolean[][] a;
    AdjacencyMatrix(int n0) {
        size = n0;
        a = new boolean[size][size];
    }
    
    void addEdge(int i, int j) {
        a[i-1][j-1] = true;
    }
    
    void removeEdge(int i, int j) {
        a[i-1][j-1] = false;
    }
    
    boolean hasEdge(int i, int j) {
        return a[i-1][j-1];
    }
}
