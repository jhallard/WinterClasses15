/**
 * @Author   - John Allard (cruzid : jhallard, id# : 1437547)
 * @File     - Matrix.java
 * @Projects - Programming Asssignment #3, CMPS 101
 * @info     - This file defines the matrx class. This class is used to represent a sparse
 *             matrix using an adjacency-list-like implementation. This class relies heavily on the List class 
 *             that was implemented previously for another assignment.
 *
 *
 **/
  import java.lang.RuntimeException;

 
public class Matrix {

  private int size;
  private int nnz;
  private List[] mat;

  // @func - Constructor
  // @args - #1 Number of rows/columns (must be the same)
  // @info - Initializes an empty matrix of size NxN
  public Matrix(int n) {
    if(n <= 0) {
      return;
      //TODO add in exception
    }
   
    size = n;
    nnz = 0;
    mat = new List[n];
    return;
  }

  // Access Functions
 
  // @func - getSize
  // @args - none
  // @ret  - Number of rows/columns in this square matrix
  public int getSize() {
    return size; 
  }

  // @func - getNNZ
  // @args - none
  // @ret  - Number of non-zero entries in the matrix
  public int getNNZ() {
    return nnz;
  }

  // @func - equals
  // @args - #1 Object to be compared with
  // @ret  - boolean, true if they are equal
  // @info - Overwrite the equals operator
  public boolean equals(Object x) {
    // @TODO @TODO @TODO @TODO @TODO @TODO @TODO //
    return true;
  }


  // Mainpulation Procedures

  // @func - makeZero
  // @args - none
  // @ret  - none
  // @info - sets/resets the matrix to the zero (initial, empty) state
  public void makeZero() {    
  
    for(int i = 0; i < mat.length; i++) {
        mat[i].clear();
    }
    nnz = 0;
  }

  // @func - copy
  // @args - none
  // @ret  - Matrix having the same values/structure as this matrix
  public Matrix copy() {
    Matrix ret = new Matrix(size);

    for(int i = 0; i < mat.length; i++) {
        int j = 0; 
        for(mat[i].moveTo(0); mat[i].getIndex() >= 0; mat[i].moveNext()) {
          Entry temp = (Entry)mat[i].getElement();
          ret.changeEntry(i+1, j+1, temp.getValue());
          j++;
        }
    }

    return ret;
  }

  // @func - changeEntry
  // @args - #1 The row of the entry, #2 The column of the entry
  // @ret  - none
  // @info - Pre : 1<= k <=getSize() for k in {i, j}
  public void changeEntry(int row, int column, double x) {
     if(row >= size || column >= size) {
        throw new RuntimeException("Invalid row or column entry");
     }
     if(row <= 0 || column <= 0) {
        throw new RuntimeException("Error : Row & Column Entry must be Positive");
     }
     // normalize the entries, for the user the matrix starts at index 1 but for us it starts at index 0
     row--;
     column--;

     List list_row = mat[row];

     int index = findIndex(row, column);
     
     // if the entry is already empty and we are trying to empty it..
     if(index == -1 && x == 0) {
        return;
     }
     // if the entry is zero and we need to set it
     else if(index == -1 && x != 0) {
        // @TODO insert new element then sort the list
        Entry temp = new Entry(column, x);
        list_row.prepend(temp);
        insertionSort(row);
        nnz++; // incrmement the number of nonzero entries
        return;
     }
     // the entry is non-zero and it needs to be zero'd
     else if(index != -1 && x == 0) {
        list_row.moveTo(index);
        list_row.delete();
        nnz--; // decrement the number of non zero entries
        return;
     }
     // if the entry is non zero and needs to be a diff. non zero
     else {
        list_row.moveTo(index);
        list_row.insertBefore(new Entry(column, x));
        list_row.delete();
        return;
     }
  }




  // @func - scalarMult
  // @args - #1 Double value to multiply the matrix by
  // @ret  - Returns a new matrix that is the sclar multiple of this one by the argument
  public Matrix scalarMult(double x) {
    
    if(x == 0) {
     return new Matrix(size);
    }
    Matrix ret_mat = new Matrix(size);

    for(int i = 0; i < size; i++) {

      for(mat[i].moveTo(0); mat[i].getIndex() >= 0; mat[i].moveNext()) {
         Entry temp = (Entry)mat[i].getElement();
         ret_mat.changeEntry(i+1, (int)temp.getColumn()+1, x*temp.getValue());
      }
    }

    return ret_mat;
    
  }
  
  // @func - add
  // @args - #1 Matrix to add to this one
  // @ret  - A new matrix that is the sum of this one and the argument matrix
  // @info - Pre : getSize() == m.getSize()
  public Matrix add(Matrix m)  {

    // precondition assertion
    if(m.getSize() != size) {
      throw new RuntimeException("Error : Can only add matrices of same dimension");
    }
    
    Matrix ret_mat = new Matrix(size);
    
    // outer loop, goes through each row in the matrix
    for(int i = 0; i < size; i++) {
      List other_list = m.getRow(i+1);
      List our_list = mat[i];

      other_list.moveTo(0);
      our_list.moveTo(0);
      
      // inner loop, walks along both lists and inserts into the new matrix
      while(our_list.getIndex() >= 0 && other_list.getIndex() >= 0) {
        Entry our_entry = (Entry)our_list.getElement();
        Entry other_entry = (Entry)other_list.getElement();
        
        // if this is true we only insert the entry from our matrix
        if(our_entry.getColumn() > other_entry.getColumn()) {
          ret_mat.changeEntry(i+1, (int)our_entry.getColumn()+1, our_entry.getValue());
          our_list.moveNext();
        }
        // if the other column comes first then we insert that entry first
        else if(our_entry.getColumn() < other_entry.getColumn()) {
          ret_mat.changeEntry(i+1, (int)other_entry.getColumn()+1, other_entry.getValue());
          other_list.moveNext();
        }
        // else the two numbers are in the same column and must be added together then inserted
        else {
          ret_mat.changeEntry(i+1, (int)other_entry.getColumn()+1, our_entry.getValue()+other_entry.getValue());
          other_list.moveNext();
          our_list.moveNext();
        }

      }// end inner while-loop

    } // end outer for-loop

    return ret_mat;
  }

  // @func - sub
  // @args - #1 Matrix to subtract from this one
  // @ret  - A new matrix that is the difference of this matrix and the argument matrix
  // @info - Pre : getSize() == m.getSize()
  public Matrix sub(Matrix m) {
    return this;
  }

  // @func - transpose
  // @args - none
  // @ret  - A new matrix that is the transpose of this one
  public Matrix transpose(Matrix m) {
    return this;
  }

  //@func  - mult
  //@args  - #1 the matrix to multiply this one by
  //@ret   - A new matrix that is the matrix multiple of the given argument
  public Matrix mult(Matrix m) {
    return this;
  }

  //@func - getRow
  //@args - which row in the matrix to get
  //@ret  - A list object which is a copy of the requested row
  public List getRow(int row) {
    if(row < 1 || row > size)
      return null;

   return mat[--row].copy();
  }

  // =============================================== //
  // ========== PRIVATE FUNCTIONS/CLASSES ========== //
  // ================================================//
  
  private boolean set(List[] new_mat) {
    mat = new_mat;
    return true;
  }
  //@func - dot
  //@args - #1 row in the this matrix, #2 row in the other matrix. Will dot product these two rows
  //@ret  - A double value that is the dot product of the two arguments
  private double dot(List x, List y) {
    return 0.0; //@TODO @TODO @TODO @TODO Implement dot product
  } 

  //@func - find
  //@args - #1 row in the matrix to search in, #2 column to search for
  //@ret  - Entry object that was searched for, null if not found
  private Entry find(int row, int col) {

    Entry item = null;
          
    if(row < 0 || row >= size) {
        return item;
     }

    List temp = mat[row];

    for(temp.moveTo(0); temp.getIndex() >= 0; temp.moveNext()) {
       item = (Entry) temp.getElement();
        if(item.getColumn() == col) {
          return item;
        }
    }
    return item;
  }

  
  //@func - findIndex
  //@args - #1 row in the matrix to search in, #2 column to search for
  //@ret  - index in the list where the entry is stored, -1 if not found
  private int findIndex(int row, int col) {

    Entry item = null;
          
    if(row < 0 || row >= size) {
        return -1;
     }

    List temp = mat[row];

    for(temp.moveTo(0); temp.getIndex() >= 0; temp.moveNext()) {
       item = (Entry) temp.getElement();
        if(item.getColumn() == col) {
          return temp.getIndex();
        }
    }
    return -1;
  }

  //@func - insertionSort
  //@args - #1 row number to sort in the matrix
  private boolean insertionSort(int row) {

    if(row < 0 || row >= size) {
        return false;
    }
    List list = mat[row];

    for(int i = 1; i < list.length(); i++) {

      list.moveTo(i);
      Entry entry = (Entry) list.getElement();

      // Go backwards along the list to find the correct insertion spot for the ith element
      for(list.moveTo(i-1); list.getIndex() >= 0 && entry.getColumn() < ((Entry)list.getElement()).getColumn(); list.movePrev()) {
      }

      if(list.getIndex() == -1) {
        if(entry.getColumn() <= ((Entry)list.front()).getColumn()) {
          list.prepend(i);
          list.moveTo(i+1);
          list.delete();
        }
      }
      else if(list.getIndex() < i-1) {
         list.insertAfter(i);
         list.moveTo(i+1);
         list.delete();
      }
    }

    return true;

  }
  
  // @class - Entry
  // @info  - This class encapsulates a pair of values, an int and a double, which correspond to a single entry in the matrix. The int corresponds to the column value, 
  // and double correspondign to the actual numerical value stored at that position in the matrix.
  private class Entry {
    private int column;
    private double value;
    
    // @func - Constructor
    // @args - #1 column value (>=0), #2 number stored at that position in matrix
    public Entry(int col, double val) {
        column = col;
        value = val;
    }

    //@func - setColumn
    //@args - #1 column value Pre : col >= 0
    //@ret  - boolean confirming if the column was changed or not
    public boolean setColumn(int col) {
        if(col < 0) {
          return false;
        }
        column = col;
        return true;
    }

    //@func - setValue
    //@args - #1 numerical value to be stored in the matrix
    //@ret  - boolean indicating success 
    public boolean setValue(double val) {
      value = val;
      return true;
    }

    public double getValue() {
      return value;
    }

    public double getColumn() {
      return column;
    }

    // @TODO @TODO @TODO @TODO @TODO @TODO @TODO //
    //  implement equals and toString function   //
    // @TODO @TODO @TODO @TODO @TODO @TODO @TODO //

    //@func - toString
    //@args - None
    //@ret  - String describing this entry pair
    public String toString() {
        return ""; //@TODO @TODO @TODO //
    }

    //@func - equals
    //@args - #1 another Entry object for comparison
    //@ret  - boolean indicating success or not
    public boolean equals(Object x) {
      return false;
    }
    

  }


}
