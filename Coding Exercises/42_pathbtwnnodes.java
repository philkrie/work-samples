//Given a directed graph, see if there is a path between two nodes

class Solution{
	
	public enum State {
		Univisited, Visited, Visiting;
	}
	
	public static boolean findPath(Graph g, Node start, Node end){
		if (start == end) return true;
		
		LinkedList<Node> q = new LinkedList<Node>();
		
		for(Node n : g.getNodes()){
			n.state = State.Unvisited;
		}
		start.state = State.Visiting;
		q.enqueue(start);
		Node u;
		while(!q.isEmpty()){
			u = q.dequeue();
			if(u != null){
				for(Node v : u.adjacent()){
					if(v.state == State.Univisited){
						if(v == end){
							return true;
						} else {
							v.state = State.Visiting;
							q.enqueue(v);
						}
					}
				}
				u.state = State.Visited;
			}
			
		} return false;
	}
}