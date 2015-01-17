import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Lex {

    public Lex() {

    }

    private static List listSwap(List list, int one, int two) {
        int temp1 = 0, temp2 = 0;

        if(one == two) {
            return list;
        }
        else if(one > two) {
            int temp = one;
            one = two;
            two = temp;
        }
        list.moveTo(one);
        temp1 = list.getElement();
        list.moveTo(two);
        temp2 = list.getElement();
        list.insertAfter(temp1);
        list.delete();

        list.moveTo(one);
        list.insertAfter(temp2);
        list.delete();
        return list;
    }
    private static List insertionSort(String[] lines) {

        List ret_list = new List();
        for(int i = 0; i < lines.length; i++) {
            ret_list.append(i);
        }

        for(int i = 1; i < ret_list.length(); i++) {
            boolean insert_spot_found = false;
            ret_list.moveTo(i);
            String i_string = lines[ret_list.getElement()];
            System.out.println(i_string + " : \n" );

            for(ret_list.moveTo(i-1); ret_list.getIndex() >= 0 && i_string.compareTo(lines[ret_list.getElement()]) < 0; ret_list.movePrev()) {
                System.out.println("    " +  lines[ret_list.getElement()]);
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

           // System.out.println(ret_list);
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

            System.out.println(sorted);

            for(sorted.moveTo(0); sorted.getIndex() >= 0; sorted.moveNext()) {
                System.out.println(in_lines[sorted.getElement()]+", ");
            } 
        }
        catch(IOException E) {

            return;
            // TODO add stderr output
        }
    }
}