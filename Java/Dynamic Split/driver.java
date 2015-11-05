import java.util.Scanner;
import java.io.IOException;


public class driver {
	
	public static void main(String[] args) throws IOException {
				
		//Initialize input scanner
		Scanner stdin = new Scanner(System.in);
		int numLines;
		String currentLine;
		dynamic engine = new dynamic();
		
		//First, we collect the information at the start for how many phrases there are
		numLines = stdin.nextInt();
		if (numLines == 0){
			System.exit(0);
		}
		
		//Iterate through each phrase, running iterative and memoized dynamic split tests on them
		for (int i = 0; i < numLines; i++){
			System.out.println();
			
			System.out.println("phrase number: " + (i+1));
			currentLine = stdin.next().trim().toLowerCase();
			System.out.println(currentLine);
			System.out.println();
			
			System.out.println("iterative attempt:");
			if (engine.iterative(currentLine)){
				System.out.println("YES, can be split");
				System.out.println(engine.restructure(currentLine));
			} else {
				System.out.println("NO, cannot be split");
			}
			System.out.println();

			System.out.println("memoized attempt:");
			if (engine.memoized(currentLine)){
				System.out.println("YES, can be split");
				System.out.println(engine.restructure(currentLine));
			} else {
				System.out.println("NO, cannot be split");
			}
			System.out.println();
		}	
	}
}