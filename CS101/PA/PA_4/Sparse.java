 /**
 * Created by John Allard on 2/5/2015.
 * ID : 1437547
 * CruzID : jhallard
 * CS101 PA #3
 * This is the implementation of the Sparse program. This program reads into two matrices from a given input file,
 * performs multiple mathematical operations on these two matrices, then writes the results to a given output
 * file for inspection by the user.
 */
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class Sparse {

    public static void main(String [] args) {

        if(args.length != 2) {
            System.err.println("Error : Must pass in input and output files for the program");
            return;
            // TODO print error message to stderr
        }

        int num_lines = 0;
        String in_fn = args[0];
        String out_fn = args[1];

        String[] in_lines = parseInputFile(in_fn);

        String[] tokens = in_lines[0].split(" ");

        if(tokens.length != 3) {
            System.out.println(tokens.length);
            throw new RuntimeException("Error : Invalid 1st line file format");
        }

        // get the first line (# entries, #nnz for a and b matrices)
        int size = Integer.parseInt(tokens[0]);
        int a = Integer.parseInt(tokens[1]);
        int b = Integer.parseInt(tokens[2]);

        Matrix mat_one = new Matrix(size);
        Matrix mat_two = new Matrix(size);

        // populate the first matrix
        for(int i = 2; i <= a+1; i++) {
            String[] parts = in_lines[i].split(" ");

            if(parts.length != 3) {
                System.out.println(in_lines[i]);
                throw new RuntimeException("Error : Invalid line entry format");
            }

            int row = Integer.parseInt(parts[0]);
            int col = Integer.parseInt(parts[1]);
            double val = Double.parseDouble(parts[2]);

            mat_one.changeEntry(row, col, val);
        }

                // populate the first matrix
        for(int i = a+3; i < in_lines.length; i++) {
            String[] parts = in_lines[i].split(" ");

            if(parts.length != 3) {
                throw new RuntimeException("Error : Invalid line entry format");
            }

            int row = Integer.parseInt(parts[0]);
            int col = Integer.parseInt(parts[1]);
            double val = Double.parseDouble(parts[2]);

            mat_two.changeEntry(row, col, val);
        }

        printToFile(out_fn, mat_one, "Matrix A : \n");
        printToFile(out_fn, mat_two, "Matrix B : \n");
        printToFile(out_fn, mat_one.scalarMult(1.5), "1.5*A : \n");
        Matrix m = mat_one.add(mat_two);
        printToFile(out_fn, m, "A+B : \n");
        printToFile(out_fn, mat_one.add(mat_one), "A+A : \n");
        m = mat_two.sub(mat_one);
        printToFile(out_fn, m, "B-A : \n");
        printToFile(out_fn, mat_one.sub(mat_one), "A-A : \n");
        printToFile(out_fn, mat_one.transpose(), "Atranspose : \n");
        printToFile(out_fn, mat_one.mult(mat_two), "A*B : \n");
        printToFile(out_fn, mat_two.mult(mat_two), "B*B : \n");



    }

    public static void printToFile(String out_fn, Matrix m, String desc) {
        try{
            PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(out_fn, true)));
            out.println(desc);
            out.println(m.toString());
            out.println("\n");
            out.close();
        }
        catch(Exception E) {
            System.out.println(E);//return;
            E.printStackTrace();
        }
    }


    public static String[] parseInputFile(String in_fn) {

        try {
            int num_lines = 0;
            Scanner in = new Scanner(new FileReader(in_fn));
            in.useDelimiter("\n");
            while(in.hasNext()) {
                // System.out.println(in.next());
                in.next();
                num_lines++;
            }

            String[] in_lines = new String[num_lines];
            int count = 0;
            in = new Scanner(new FileReader(in_fn));
            in.useDelimiter("\n");
            while(in.hasNext()) {
               in_lines[count++] = in.next();
            }
            return in_lines;
        }
        catch(Exception E) {
            return null;
        }

    }

}