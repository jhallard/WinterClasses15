import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.io.PrintWriter;

/**
 * Created by John Allard on 1/10/2015.
 * ID : 1437547
 * CruzID : jhallard
 * CS101 PA #1
**/

public class Lex {

    public Lex() {

    }

    private static List insertionSort(String[] lines) {

        List ret_list = new List();
        for(int i = 0; i < lines.length; i++) {
            ret_list.append(i);
        }

        for(int i = 1; i < ret_list.length(); i++) {

            ret_list.moveTo(i);
            String i_string = lines[ret_list.getElement()];

            // Go backwards along the list to find the correct insertion spot for the ith element
            for(ret_list.moveTo(i-1); ret_list.getIndex() >= 0 && i_string.compareTo(lines[ret_list.getElement()]) < 0; ret_list.movePrev()) {
            }

            if(ret_list.getIndex() == -1) {
                if(i_string.compareTo(lines[ret_list.front()]) <= 0) {
                    ret_list.prepend(i);
                    ret_list.moveTo(i+1);
                    ret_list.delete();
                }
            }
            else if(ret_list.getIndex() < i-1) {
                ret_list.insertAfter(i);
                ret_list.moveTo(i+1);
                ret_list.delete();
            }
        }

        return ret_list;

    }

    public static void main(String [] args) {

        if(args.length != 2) {
            return;
            // TODO print error message to stderr
        }

        int num_lines = 0;
        String in_fn = args[0];
        String out_fn = args[1];

        try {
            Scanner in = new Scanner(new FileReader(in_fn));
            while(in.hasNext()) {
                in.next();
                num_lines++;
            }

            String[] in_lines = new String[num_lines];
            int count = 0;
            in = new Scanner(new FileReader(in_fn));
            while(in.hasNext()) {
               in_lines[count++] = in.next();
            }

            List sorted = insertionSort(in_lines);

            PrintWriter writer = new PrintWriter(out_fn, "UTF-8");

            for(sorted.moveTo(0); sorted.getIndex() != -1; sorted.moveNext()) {
                writer.println(in_lines[sorted.getElement()]);
            }
            writer.close();
        }
        catch(IOException E) {

            return;
            // TODO add stderr output
        }
    }
}