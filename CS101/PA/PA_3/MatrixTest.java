/**
 * @author  - John Allard
 * @file    - MatrixTest.java 
 * @Project - CS101 Programming Assignment #3
 * @Date    - Feb. 5th 2015
 * @Info    - This file defines a testing suite for the Matrix ADT. This suite tests the basic features of the Matrix class individually
 *            in attempt of catching bugs before they show up in the actual implementation file.
 **/ 

public class MatrixTest {

    public static void main(String[] args) {
        boolean b;

        b = illegalBuildTest() &&
            emptyTest()        &&
            sizeTest()         &&
            simpleInsertDeleteTest() &&
            // simpleInsertTest(); &&
            // insertErrorTest(); &&
            // addErrorTest()     &&
            // subErrorTest()     &&
            multErrorTest();//    && 
            // simpleTransposeTest()  &&
            // simpleMultTest()    &&
            // simpleAddTest()    &&
            // addToZeroTest()    &&
            // multToZeroTest();

        if(b) {
            System.out.println("\n\n All tests passed for Matrix class");
        }
        else {
            System.out.println("\n\n One or more failed test for Matrix Class");
        }
    }

    // test that we can't build a matrix with negative/0 size
    public static boolean illegalBuildTest() {
        try{
            Matrix mat = new Matrix(0);
            Matrix mat1 = new Matrix(-10);
            return false;
        }catch(Exception E) {
            return true;
        }
    }

    // test that it knows when it is empty
    public static boolean emptyTest() {
        try{
            Matrix mat = new Matrix(10);
            return (0 == mat.getNNZ());
        }catch(Exception E) {
            return false;
        }
    }

    // test that it knows it's own size
    public static boolean sizeTest() {
        try{
            Matrix mat = new Matrix(1099);
            return (1099 == mat.getSize());
        }catch(Exception E) {
            return false;
        }
    }

    // insert a few elements
    public static boolean simpleInsertTest() {
        try{
            Matrix mat = new Matrix(100);

            mat.changeEntry(1, 1, 1);
            mat.changeEntry(1, 2, 1);
            mat.changeEntry(10, 9, 100);

            if(mat.getNNZ() != 3)
                return false;

            return true;

        }catch(Exception E) {
            return false;
        }
    }

    // should get an exception when insert into negative column
    public static boolean insertErrorTest() {
        try{
            Matrix mat = new Matrix(100);

            mat.changeEntry(1, -1, 1);
            return false;

        }catch(Exception E) {
            return true;
        }
    }

    // should get an exception when add a different size matrix
    public static boolean addErrorTest() {
        try{
            Matrix mat = new Matrix(100);
            Matrix mat1 = new Matrix(10);

            mat.add(mat1);
            return false;

        }catch(Exception E) {
            return true;
        }
    }

    // should get an exception when sub a different size matrix
    public static boolean subErrorTest() {
        try{
            Matrix mat = new Matrix(100);
            Matrix mat1 = new Matrix(10);

            mat.sub(mat1);
            return false;

        }catch(Exception E) {
            return true;
        }
    }

    // should get an exception when sub a different size matrix
    public static boolean multErrorTest() {
        try{
            Matrix mat = new Matrix(100);
            Matrix mat1 = new Matrix(10);

            mat.mult(mat1);
            return false;

        }catch(Exception E) {
            return true;
        }
    }

    // insert a few elements then delete thems
    public static boolean simpleInsertDeleteTest() {
        try{
            Matrix mat = new Matrix(100);

            mat.changeEntry(1, 1, 1);
            mat.changeEntry(1, 2, 1);
            mat.changeEntry(10, 9, 100);

            if(mat.getNNZ() != 3) {
                System.out.println("111");
                return false;
            }

            mat.changeEntry(1, 1, 0);

            if(mat.getNNZ() != 2) {
                System.out.println("222");
                return false;
            }

            mat.changeEntry(1, 2, 0);
            mat.changeEntry(10, 9, 0);

            if(mat.getNNZ() != 0) {
                System.out.println("333");
                return false;
            }

            return true;

        }catch(Exception E) {
            E.printStackTrace();
            System.out.println("333");
            return false;
        }
    }

    //     // insert a few elements then delete thems
    // public static boolean simpleTransposeTest() {
    //     try{
    //         Matrix mat = new Matrix(2);

    //         mat.changeEntry(1, 1, 1);
    //         mat.changeEntry(1, 2, 2);
    //         mat.changeEntry(2, 1, 3);
    //         mat.changeEntry(2, 2, 4);

    //         if(mat.getNNZ() != 4)
    //             return false;

    //         Matrix mat_new = mat.transpose();

    //         if(mat_new.getNNZ() != 4)
    //             return false;

    //         System.out.println(mat_new);

    //         return true;

    //     }catch(Exception E) {
    //         return false;
    //     }
    // }

    // // insert a few elements then delete thems
    // public static boolean simpleAddTest() {
    //     try{
    //         Matrix mat = new Matrix(2);

    //         mat.changeEntry(1, 1, 1);
    //         mat.changeEntry(1, 2, 2);
    //         mat.changeEntry(2, 1, 3);
    //         mat.changeEntry(2, 2, 4);

    //         Matrix mat2 = new Matrix(2);

    //         mat.changeEntry(1, 1, 5);
    //         mat.changeEntry(1, 2, 6);
    //         mat.changeEntry(2, 1, 7);
    //         mat.changeEntry(2, 2, 8);

    //         if(mat.getNNZ() != 4 || mat2.getNNZ() != 4)
    //             return false;

    //         Matrix mat_new = mat.add(mat2);

    //         if(mat_new.getNNZ() != 4)
    //             return false;

    //         System.out.println(mat_new);

    //         return true;
    //     }catch(Exception E) {
    //         return false;
    //     }
    // }

    // // insert a few elements then delete thems
    // public static boolean simpleMultTest() {
    //     try{
    //         Matrix mat = new Matrix(2);

    //         mat.changeEntry(1, 1, 1);
    //         mat.changeEntry(1, 2, 2);
    //         mat.changeEntry(2, 1, 3);
    //         mat.changeEntry(2, 2, 4);

    //         Matrix mat2 = new Matrix(2);

    //         mat.changeEntry(1, 1, 5);
    //         mat.changeEntry(1, 2, 6);
    //         mat.changeEntry(2, 1, 7);
    //         mat.changeEntry(2, 2, 8);

    //         if(mat.getNNZ() != 4 || mat2.getNNZ() != 4)
    //             return false;

    //         Matrix mat_new = mat.mult(mat2);

    //         if(mat_new.getNNZ() != 4)
    //             return false;

    //         System.out.println(mat_new);

    //         return true;
    //     }catch(Exception E) {
    //         return false;
    //     }
    // }

    // // insert a few elements then delete thems
    // public static boolean addToZeroTest() {
    //     try{
    //         Matrix mat = new Matrix(2);

    //         mat.changeEntry(1, 1, 1);
    //         mat.changeEntry(1, 2, 2);
    //         mat.changeEntry(2, 1, 3);
    //         mat.changeEntry(2, 2, 4);

    //         Matrix mat2 = new Matrix(2);

    //         mat.changeEntry(1, 1, -1);
    //         mat.changeEntry(1, 2, -2);
    //         mat.changeEntry(2, 1, -3);
    //         mat.changeEntry(2, 2, -4);

    //         if(mat.getNNZ() != 4 || mat2.getNNZ() != 4)
    //             return false;

    //         Matrix mat_new = mat.mult(mat2);

    //         if(mat_new.getNNZ() != 0)
    //             return false;

    //         System.out.println(mat_new);
    //         return true;
    //     }catch(Exception E) {
    //         return false;
    //     }
    // }

    // // insert a few elements then delete thems
    // public static boolean multToZeroTest() {
    //     try{
    //         Matrix mat = new Matrix(2);

    //         mat.changeEntry(1, 1, 1);
    //         mat.changeEntry(1, 2, 2);
    //         mat.changeEntry(2, 1, 3);
    //         mat.changeEntry(2, 2, 4);

    //         Matrix mat2 = new Matrix(2);

    //         mat.changeEntry(1, 1, 0);
    //         mat.changeEntry(1, 2, 0);
    //         mat.changeEntry(2, 1, 0);
    //         mat.changeEntry(2, 2, 0);

    //         if(mat.getNNZ() != 4 || mat2.getNNZ() != 4)
    //             return false;

    //         Matrix mat_new = mat.mult(mat2);

    //         if(mat_new.getNNZ() != 0)
    //             return false;

    //         System.out.println(mat_new);

    //         return true;
    //     }catch(Exception E) {
    //         return false;
    //     }
    // }
}

