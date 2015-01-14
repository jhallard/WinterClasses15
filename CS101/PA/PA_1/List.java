package com.tutr.libtutr.Model; /**
 * Created by HP on 1/9/2015.
 */

public class List {

    private int num_nodes;
    private Node root_node;
     // Constructor
    public List() { // Creates a new empty list
    }
                   // Access functions
    public int length() { // Returns number of elements in this list.
    }
    public int getIndex() { // Returns the index of the cursor element in this list, or
                           // returns -1 if the cursor element is undefined.
    }

    public int front() { // Returns front element in this list. Pre: length()>0
    }

    public int back() {  // Returns back element in this List. Pre: length()>0
    }

    public int getElement() { // Returns cursor element in this list.
                             // Pre: length()>0, getIndex()>=0
    }

    public boolean equals(List L) { // Returns true if this List and L are the same integer
                                   // sequence. The cursor is ignored in both lists.
    }

        // Manipulation procedures

    public void clear() { // Re-sets this List to the empty state.
    }

    public void  moveTo(int i) { // If 0<=i<=length()-1, moves the cursor to the element
     // at index i, otherwise the cursor becomes undefined.
    }

    public void movePrev() { // If 0<getIndex()<=length()-1, moves the cursor one step toward the
     // front of the list. If getIndex()==0, cursor becomes undefined.
     // If getIndex()==-1, cursor remains undefined. This operation is
     // equivalent to moveTo(getIndex()-1).
    
    }

    public void moveNext() { // If 0<=getIndex()<length()-1, moves the cursor one step toward the
     // back of the list. If getIndex()==length()-1, cursor becomes
     // undefined. If getIndex()==-1, cursor remains undefined. This
     // operation is equivalent to moveTo(getIndex()+1).
    
    }

    public void prepend(int data) { // Inserts new element before front element in this List.
    
    }

    public void append(int data) { // Inserts new element after back element in this List.
    
    }

    public void insertBefore(int data) { // Inserts new element before cursor element in this
     // List. Pre: length()>0, getIndex()>=0
    
    }

    public void insertAfter(int data) { // Inserts new element after cursor element in this
     // List. Pre: length()>0, getIndex()>=0
    
    }

    public void deleteFront() { // Deletes the front element in this List. Pre: length()>0
    
    }

    public void deleteBack() { // Deletes the back element in this List. Pre: length()>0
    
    }

    public void delete() { // Deletes cursor element in this List. Cursor is undefined after this
     // operation. Pre: length()>0, getIndex()>=0
    // Other methods
    
    }

    public String toString() { // Overides Object's toString method. Creates a string
     // consisting of a space separated sequence of integers
     // with front on the left and back on the right. The
    // cursor is ignored.
    
    }

    public List copy() { // Returns a new list representing the same integer sequence as this
     // list. The cursor in the new list is undefined, regardless of the
     // state of the cursor in this List. This List is unchanged.
    }

}
