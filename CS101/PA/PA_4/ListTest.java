
/**
 * @author  - John Allard
 * @file    - ListTest.java 
 * @Project - CS101 Programming Assignment #3
 * @Date    - Feb. 5th 2015
 * @Info    - This file defines a testing suite for the List ADT. This suite tests the basic features of the List class individually
 *            in attempt of catching bugs before they show up in the actual implementation file.
 **/ 

public class ListTest {

    public static void main(String[] args) {

        boolean b = false;

        b = emptyTest() &&
            simpleInsertTest() &&
            // appendTest() &&
            // prependTest() &&
            deleteTest();

        if(b) {
            System.out.println("List : All unit tests passed");
        }
        else {
            System.out.println("List : Some unit tests failed");
        }
    }

    public static boolean emptyTest() {
        List l = new List();

        try {
            
            if(l.length() != 0)
                return false;

            return true;
        }catch(Exception E) {
            return false;
        }
    }

    public static boolean simpleInsertTest() {
        List l = new List();

        try{
            l.prepend(new Object());

            if(l.length() != 1)
                return false;

            l.append(new Object());

            if(l.length() != 2)
                return false;
            return true;
        }catch(Exception E) {
            return false;
        }
    }

    public static boolean prependTest() {
        List l = new List();

        try{

            for(int i = 0; i < 10000; i++)
                l.prepend(new Object());

            if(l.length() != 10000)
                return false;
            return true;
        }catch(Exception E) {
            return false;
        }
    }

    public static boolean appendTest() {
        List l = new List();

        try{

            for(int i = 0; i < 10000; i++)
                l.append(new Object());

            if(l.length() != 10000)
                return false;
            return true;
        }catch(Exception E) {
            return false;
        }
    }

    public static boolean deleteTest() {
        List l = new List();

        try{

            for(int i = 0; i < 10000; i++)
                l.prepend(new Integer(i));

            if(l.length() != 10000) {
                System.out.println("length : " + l.length());
                return false;
            }


            int count = 10000;
            while(l.length() > 0) {
                l.deleteFront();
                count--;
            }

            if(count != 0) {
                return false;
            }

            return true;
        }catch(Exception E) {
            E.printStackTrace();
            return false;
        }
    }

}
