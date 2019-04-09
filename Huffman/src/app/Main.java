package app;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.Comparator;
import java.util.PriorityQueue;

class Huffman{
	int freq;
	char val;
	Huffman left;
	Huffman right;
}
class Compare implements Comparator<Huffman> {
	 public int compare(Huffman x, Huffman y) 
	    { 
	        return x.freq - y.freq; 
	    } 
}
public class Main {
	  static int after = 0;
	  public static int numberOfBytes(int x) {
		  int counter = 0;
		  while (x!=0) {
			  x/=2;
			  counter ++;
		  }
		  return counter;
	  }
	  public static int beforeCompression(int charCounter, int newCounter) {
		  return numberOfBytes(newCounter) * charCounter;
	  }
	  public static void afterCompression(Huffman root, int counter) 
	    { 
	        if (root.left 
	                == null
	            && root.right 
	                   == null
	           ) { 
	        	after += counter * root.freq;
	            return ; 
	        } 
	        afterCompression(root.left, counter + 1); 
	        afterCompression(root.right, counter + 1); 
	    }
	  public static void compareLength(Huffman root, int counter, int charCounter, int newCounter) {
		  System.out.println("Przed kompresja: " + beforeCompression(charCounter,newCounter));
	        afterCompression(root,0);
	        System.out.println("Po kompresji: " + after);
	        System.out.println("Wartosc kompresji to " + (float)after/beforeCompression(charCounter,newCounter) *100 +"% " );
	  }
	  public static void printCode(Huffman root, String s) 
	    { 
	        if (root.left 
	                == null
	            && root.right 
	                   == null
	           ) { 
	            System.out.println(root.val + ":" + root.freq + ":" + s); 
	           
	            return; 
	        } 
	        printCode(root.left, s + "0"); 
	        printCode(root.right, s + "1"); 
	    }
	public static void main(String[] args) throws Exception {
		  int helpArray[] = new int [255];
		  int helpCounter = 0;
		  for (int i=0; i<255;i++) {
			  helpArray[i] = 0;
		  }
		  File file = new File("znaki.txt"); 
		  
		  BufferedReader reader = new BufferedReader(new FileReader(file)); 
		  int charCounter=0;
		  String st; 
		  while ((st = reader.readLine()) != null) { 
		    for (int i =0; i< st.length(); i++) {
		    	helpArray[(int)st.charAt(i)] ++ ;
		    	charCounter ++;
		    }
		  } 
		 //zliczamy wielkosc tablicy
		for (int i = 1; i< 255; i++) 
			if (helpArray[i] != 0 )
				helpCounter++;
        char[] charArray = new char [helpCounter]; 
        int[] charfreq = new int [helpCounter];
        //dodajemy do tablic
        int newCounter = 0;
        for (int i = 1; i< 255; i++) 
			if (helpArray[i] != 0 ) {
				charArray[newCounter] = (char)i;
				charfreq[newCounter] = helpArray[i];
				newCounter++;
			}
		 PriorityQueue<Huffman> queue = new PriorityQueue<Huffman>(newCounter, new Compare()); 
		 for (int i = 0; i < newCounter; i++) { 
			  
	            Huffman hn = new Huffman(); 
	  
	            hn.val = charArray[i]; 
	            hn.freq = charfreq[i]; 
	  
	            hn.left = null; 
	            hn.right = null; 
	            queue.add(hn); 
	        } 
	  
	        Huffman root = null; 
	 
	        while (queue.size() > 1) { 
	  
	            Huffman x = queue.peek(); 
	            queue.poll(); 
	            Huffman y = queue.peek(); 
	            queue.poll(); 
	            Huffman f = new Huffman(); 
	            f.freq = x.freq + y.freq; 
	            f.val = '-'; 
	            f.left = x; 
	            f.right = y; 
	            root = f; 
	            queue.add(f); 
	        } 
	        printCode(root, ""); 
	        compareLength( root,  0,  charCounter,  newCounter);
	    } 
	}

