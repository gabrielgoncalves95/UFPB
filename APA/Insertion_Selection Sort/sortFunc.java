import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Vector;


public class sortFunc {
	//METODO DO TIPO VECTOR QUE CARREGA UM ARQUIVO PARA O TESTE DO SORT
	Vector <Long> FileLoader (){
		
		Vector<Long> load = new Vector<Long>(1);
		String line;

		 try {
			BufferedReader bufferreader = new BufferedReader(new FileReader("num.10000.1.in"));
			line = bufferreader.readLine();

		   	 while (line != null) { 
		    	
		    	load.add(Long.parseLong(line));
		    	line = bufferreader.readLine();
		    
		    
		    }
		 }catch (FileNotFoundException ex) {
		    	
		    	ex.printStackTrace();
		    
		 } catch (IOException ex) {
		    	
		   	 ex.printStackTrace();
		    
		 }		
	return load;
	}
	
	
	//IMPLEMENTACAO INSERTIONSORT
	Vector <Long> insertionSort (Vector<Long> vec){		
		Integer len = vec.size();
		Long iterador;
		int j;
		
		for (int i = 1;i < len; i++) {
			iterador = vec.get(i);
			j = i-1;
				
			while(j >= 0 && vec.get(j) > iterador) {
				vec.setElementAt(vec.get(j), j+1);
				j--;
			}
			vec.setElementAt(iterador, j+1);
		}
	return vec;	
	}
	
	
	//IMPLEMENTACAO SELECTIONSORT
	Vector <Long> selectionSort (Vector<Long> vec){		
		Integer len = vec.size();
		int j, min;
		Long aux;
		
		for (int i = 0; i < len-1; i++) {
			min = i;
			
			for(j = i+1; j < len; j++) {
				if (vec.get(j) < vec.get(min)) {
					min = j;
				}
			}
			if (vec.get(i) != vec.get(min)) {					
				aux = vec.get(i);
				vec.setElementAt(vec.get(min), i);
				vec.setElementAt(aux, min);
			}
		}
	return vec;	
	}
	
}
	

