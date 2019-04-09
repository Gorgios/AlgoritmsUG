
import java.util.*;

public class main {

	public static void countingSort(String[] tab, int index) {
		  int charIndex;
		  int rozmiar = tab.length;
		  int[] zlicz = new int[76];
		  String[] out = new String[rozmiar];
		  for (int i =0; i < rozmiar; i++) {
			  zlicz[i]=0;
		  }
		  for (int i = 0; i < rozmiar; i++) {
		    if (tab[i].length() - 1 < index) {
		      charIndex = 0;
		    }
		    else {
		      charIndex = (tab[i].charAt(index) -47);// 48 to 0 w ASCII
		    }
		    zlicz[charIndex]++;
		  }
		  
		  for (int i = 1; i < zlicz.length; i++) {
		    zlicz[i] += zlicz[i - 1];
		  }
		  
		  for (int i = rozmiar - 1; i >= 0; i--) {
		    if (tab[i].length() - 1 < index) {
		      charIndex = 0;
		    }
		    else {
		      charIndex = (tab[i].charAt(index) -47);
		    }
		    out[zlicz[charIndex] - 1] = tab[i];
		    zlicz[charIndex]--;
		  }
		  
		  for (int i = 0; i < rozmiar; i++) {
		    tab[i] = out[i];
		  }
		}

		public static void radixSort(String[] tab) {
		  int max = 0;
		  for (int i = 0; i < tab.length; i++) {
		    if (tab[i].length()-1 > max) {
		      max = tab[i].length()-1;
		    }
		  }

		  for (int i = max; i >= 0; i--) {
		    countingSort(tab, i);
		  }
		}
		public static void goLower(String[] tab) {
			String temp;
			for (int i=0;i<tab.length;i++) {
					temp=tab[i];
					tab[i]=temp.toLowerCase();
			}
		}


public static void main(String[] args) {

String[] tab = {"abc","abcc","adcb","wwzzzzwwaaaaa","a1bc","a0bc","kilo","Manra","ABC","aa"};
goLower(tab);
radixSort(tab);
for (int i=0;i<tab.length;i++)
	System.out.println(tab[i]);
}
}