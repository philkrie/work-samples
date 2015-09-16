import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Collections;

public class dynamic {
	
	//Use ArrayList to store the dictionary
	ArrayList<String> dictionary = new ArrayList<String>();
	boolean[] split;
	int[] memsplit;
	int[] splitlocation;
	String phrase;
	int n;
	
	//Initialize object, which loads dictionary
    dynamic() throws FileNotFoundException {
    	Scanner dictin = new Scanner(new File("diction10k.txt"));
    	while (dictin.hasNextLine()){
    		dictionary.add(dictin.nextLine());
    	}
    }
    
    //Checks if a word is present in the dictionary (uses binary search from collections) 
    boolean returndict(String phrase){
    	int index = Collections.binarySearch(dictionary, phrase);
    	if (index >= 0){return true;}
    	else{return false;}
    }
    
    //Restructures the string based off of the location of the splits
    String restructure(String phrase){
    	String restructured = "";
    	int i = 0;
    	do{
    		restructured += phrase.substring(i, splitlocation[i]) + " ";
    		i = splitlocation[i];
    	}while (i != n);
    	return restructured;
    }
    
    //Iterative Split function
    boolean split(int i){
    	for (int j = n - 1; j >= 0; j--){
    		split[j] = false;
    		for (int k = j; k <= n; k++){
    			if (returndict(phrase.substring(j, k)) & split[k]){
    				split[j] = true;
    				splitlocation[j] = k;
    			}
    		}
    	}
    	return split[0];
    }
    
    //Iterative split driver, intializes tables and variables and such
    boolean iterative(String phrase) {
    	this.phrase = phrase;
    	this.n = phrase.length();
    	split = new boolean[n+1];
    	splitlocation = new int[n+1];
    	split[n] = true;
    	if (n == 0){ return false; };
    	if (split(n)){
    		return true;
    	} else {
    		return false;
    	}
    }
    
    //Memoized split function
    int memSplit(int i){
    	if (i == (n)){ return 1 ;};  
    	if (memsplit[i] == -1){
    		memsplit[i] = 0;
    		for (int j = i; j <= n; j++){
    			if (returndict(phrase.substring(i, j)) & memSplit(j) == 1){
    				memsplit[i] = 1;
    				splitlocation[i] = j;
    			}
    		}
    	}
    	return memsplit[i];
    }
      
    //Memoized split driver
    boolean memoized(String phrase) {
    	this.phrase = phrase;
    	this.n = phrase.length();
    	memsplit = new int[n+1];
    	splitlocation = new int[n+1];
    	memsplit[n] = 1;
    	for (int k = 0; k < n; k++){
    		memsplit[k] = -1;
    	}
    	if (n == 0){ return false; };
    	if (memSplit(0) == 1){
    		return true;	
    	} else  {
    		return false;
    	}
    }
}

