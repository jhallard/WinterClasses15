/**
 * @Author   - John Allard (cruzid : jhallard, id# : 1437547)
 * @File     - Matrix.java
 * @Projects - Programming Asssignment #3, CMPS 101
 * @info     - This file defines the matrx 
 *
 *
 **/
public class Matrix {
  // @func - Constructor
  // @args - #1 Number of rows/columns (must be the same)
  // @info - Initializes an empty matrix of size NxN
  Matrix(int n);

  // Access Functions
 
  // @func - getSize
  // @args - none
  // @ret  - Number of rows/columns in this square matrix
  int getSize();

  // @func - getNNZ
  // @args - none
  // @ret  - Number of non-zero entries in the matrix
  int getNNZ();

  // @func - equals
  // @args - #1 Object to be compared with
  // @ret  - boolean, true if they are equal
  // @info - Overwrite the equals operator
  public boolean equals(Object x);

  // Mainpulation Procedures

  // @func - makeZero
  // @args - none
  // @ret  - none
  // @info - sets/resets the matrix to the zero (initial, empty) state
  void makeZero();

  // @func - copy
  // @args - none
  // @ret  - Matrix having the same values/structure as this matrix
  Matrix copy();

  // @func - changeEntry
  // @args - #1 The row of the entry, #2 The column of the entry
  // @ret  - none
  // @info - Pre : 1<= k <=getSize() for k in {i, j}
  void changeEntry(int row, int column, double x);

  // @func - scalarMult
  // @args - #1 Double value to multiply the matrix by
  // @ret  - Returns a new matrix that is the sclar multiple of this one by the argument
  Matrix scalarMult(double x);
  
  // @func - add
  // @args - #1 Matrix to add to this one
  // @ret  - A new matrix that is the sum of this one and the argument matrix
  // @info - Pre : getSize() == m.getSize()
  Matrix add(Matrix m);
}
