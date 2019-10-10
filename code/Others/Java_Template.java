import java.io.*;
import java.util.*;

public class Main {
	static InputReader in;
	static PrintWriter out;

	public static void main(String[] args) {
		in = new InputReader(); //use it for input
		out = new PrintWriter(System.out); //use it for output
		solve();
		out.close();
	}

	static void solve() {

	}
}

class InputReader {
	BufferedReader rd;
	StringTokenizer tk;
	
	InputReader() {
		rd = new BufferedReader(new InputStreamReader(System.in), 32768);
	}
	
	public String readLine() {
		try {
			return rd.readLine();
		}
		
		catch(IOException e) {
			throw new RuntimeException();
		}
	}
	
	public String read() {
		while(tk == null || !tk.hasMoreTokens()) {
			tk = new StringTokenizer(readLine());
		}
		
		return tk.nextToken();
	}
	
	public int nextInt() {
		return Integer.parseInt(read());
	}

	public long nextLong() {
		return Long.parseLong(read());
	}

	public double nextDouble() {
		return Double.parseDouble(read());
	}
}