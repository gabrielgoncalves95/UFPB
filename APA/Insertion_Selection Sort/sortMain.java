import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Vector;

public class sortMain {
	
	//FUNCAO QUE SALVA O RESULTADO DOS SORTS EM ARQUIVOS *.TXT
	public static void writeFile(Vector<Long> saver, String operation) throws IOException {
		File fout = new File(operation + ".txt");
		FileOutputStream fos = new FileOutputStream(fout);
	 
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
	 
		for (int i = 0; i < saver.size(); i++) {
			bw.write(saver.get(i).toString());
			bw.newLine();
		}
	 
		bw.close();
	}
	
	//METODO PRINCIPAL QUE EFETUA A CHAMADA DE TODOS OS DEMAIS METODOS
	public static void main(String[] args) throws IOException {
		sortFunc sort = new sortFunc();
		long tempoInicial = System.currentTimeMillis();
		writeFile(sort.insertionSort(sort.FileLoader()), "insertion");
		System.out.println("Tempo do InsertionSort: " + ((Long)System.currentTimeMillis() - tempoInicial) + " milissegundos.");
		
		tempoInicial = System.currentTimeMillis();
		writeFile(sort.selectionSort(sort.FileLoader()), "selection");	
		System.out.println("Tempo do SelectionSort: " + ((Long)System.currentTimeMillis() - tempoInicial) + " milissegundos.");
	}
		
}


