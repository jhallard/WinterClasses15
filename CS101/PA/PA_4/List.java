 /**
 * Created by John Allard on 2/5/2015.
 * ID : 1437547
 * CruzID : jhallard
 * CS101 PA #3
 * This is the definition of an extension of the List class that was implemented for PA #1.
 * This implementation allows the user to store generic objects inside of the list nodes, as opposed
 * to integer types which were stored in PA#1.
 */
 import java.lang.RuntimeException;

public class List {

    private int num_nodes;
    private Node front_node;
    private Node back_node;
    private Node cursor_node;
    private int cursor_index;

     // Constructor
    public List() { // Creates a new empty list
        front_node = null;
        back_node = null;
        cursor_node = null;
        cursor_index = -1;
        num_nodes =0;
    }

    // Access functions
        
    
    public int length() { // Returns number of elements in this list.
        return num_nodes;
    }
    public int getIndex() { // Returns the index of the cursor element in this list, or
                            // returns -1 if the cursor element is undefined.
       return cursor_index;

    }

    public Object front() { // Returns front element in this list. Pre: length()>0
        if(front_node == null || num_nodes == 0)
            throw new RuntimeException("Length = 0, no front item exists");
        return front_node.getData();
      
    }

    public Object back() {  // Returns back element in this List. Pre: length()>0
        if(back_node == null || num_nodes == 0)
            throw new RuntimeException("Length = 0, no back item exists.");
        return back_node.getData();
    }

    public Object getElement() { // Returns cursor element in this list.
                                 // Pre: length()>0, getIndex()>=0
        if(cursor_node != null)
            return cursor_node.getData();
        else
            throw new RuntimeException("Cursor node is null");
    }

    public boolean equals(Object x) { // Returns true if this List and L are the same integer
                                   // sequence. The cursor is ignored in both lists.
        List L = null;

        if(x != null && x instanceof List)
            L = (List)x;

        if(L == null)
            return false;

        int saved_index1 = L.getIndex();
        int saved_index2 = this.cursor_index;

        // two lists must be the same length to be the same
        if(this.num_nodes != L.length())
            return false;

        for(int i = 0; i < num_nodes; i++) {
            moveTo(i);
            L.moveTo(i);

            if(cursor_node == null || cursor_node.getData() != L.getElement())
                return false;
        }

        return true;
    }

        // Manipulation procedures

    public void clear() { // Re-sets this List to the empty state.
        front_node = null;
        back_node = null;
        cursor_node = null;
        cursor_index = -1;
        num_nodes = 0;
    }

    public boolean changeElement(Object x) {
      
      cursor_node.setData(x);
      return true;
    }

    public void  moveTo(int i) { // If 0<=i<=length()-1, moves the cursor to the element
     // at index i, otherwise the cursor becomes undefined.

        if(i < 0 || i >= num_nodes)  {// pre-condition assertion
            cursor_index = -1;
            cursor_node = null;
            throw new RuntimeException("Index out of bounds\n");
        }

        if(i == num_nodes-1) {
            cursor_node = back_node;
            cursor_index = num_nodes-1;
            return;
        }

        if(i == 0) {
            cursor_node = front_node;
            cursor_index = 0;
            return;
        }

        if(cursor_index == -1) {
            if(i < num_nodes/2) {
                cursor_index = 0;
                cursor_node = front_node;
            }
            else {
                cursor_index = num_nodes-1;
                cursor_node = back_node;
            }
        }

        int diff = i - cursor_index;

        if(diff == 0) {
            return;
        }
        else if(diff > 0) { // we need to move forward
            while(cursor_index != i && cursor_node != null) {
                cursor_node = cursor_node.getNext();
                cursor_index++;
            }
            return;
        }
        else {
            while(cursor_index != i && cursor_node != null) {
                cursor_node = cursor_node.getPrev();
                cursor_index--;
            }
            return;
        }
    }

    public void movePrev() {                    // If 0<getIndex()<=length()-1, moves the cursor one step toward the
                                                // front of the list. If getIndex()==0, cursor becomes undefined.
                                                // If getIndex()==-1, cursor remains undefined. This operation is
                                                // equivalent to moveTo(getIndex()-1).
        if(cursor_index < 1 || cursor_node == null) {
            cursor_index = -1;
            cursor_node = null;
            return;
            // throw new RuntimeException();
        }

        cursor_node = cursor_node.getPrev();
        cursor_index--;
        return;
    }

    public void moveNext() {                    // If 0<=getIndex()<length()-1, moves the cursor one step toward the
                                                // back of the list. If getIndex()==length()-1, cursor becomes
                                                // undefined. If getIndex()==-1, cursor remains undefined. This
                                                // operation is equivalent to moveTo(getIndex()+1).
        if(cursor_index >= num_nodes-1 || cursor_index == -1 || cursor_node == null) {
            cursor_index = -1;
            cursor_node = null;
            return;
        }

        cursor_node = cursor_node.getNext();
        cursor_index++;
        return;
    
    }

    public void prepend(Object data) {         // Inserts new element before front element in this List.
        Node new_node = new Node((Object)data);
        if(num_nodes == 0 || front_node == null) {
            front_node = new_node;
            back_node = new_node;
            num_nodes++;
            return;
        }
        front_node.setPrev(new_node);
        new_node.setNext(front_node);
        front_node = new_node;
        if(cursor_index != -1) {
            cursor_index++;
        }
        num_nodes++;
    }

    public void append(Object data) {          // Inserts new element after back element in this List.
        Node new_node = new Node((Object)data);
        if(num_nodes == 0 || back_node == null || front_node == null) {
            front_node = new_node;
            back_node = new_node;
            num_nodes++;
            return;
        }
        new_node.setPrev(back_node);
        back_node.setNext(new_node);
        back_node = new_node;
        num_nodes++;
    }

    public void insertBefore(Object data) {            // Inserts new element before cursor element in this
                                                    // List. Pre: length()>0, getIndex()>=0
        if(cursor_index < 0 || num_nodes < 1 ) {
            cursor_index = -1;
            cursor_node = null;
            throw new RuntimeException("Cannot insert before null cursor node");
        }

        Node new_node = new Node((Object)data);
        if(cursor_node.getPrev() != null) {
            cursor_node.getPrev().setNext(new_node);
        }
        new_node.setPrev(cursor_node.getPrev());
        cursor_node.setPrev(new_node);
        new_node.setNext(cursor_node);
        if(cursor_index != -1) {
            cursor_index++;
        }

        if(front_node == cursor_node) {
            front_node = cursor_node.getPrev();
        }
        num_nodes++;
    }

    public void insertAfter(Object data) {         // Inserts new element after cursor element in this
                                                // List. Pre: length()>0, getIndex()>=0
        if(cursor_index < 0 || num_nodes < 1 || cursor_node == null) {
            cursor_index = -1;
            cursor_node = null;
            throw new RuntimeException();
        }

        Node new_node = new Node((Object)data);
        if(cursor_node.getNext() != null) {
            cursor_node.getNext().setPrev(new_node);
        }
        new_node.setNext(cursor_node.getNext());
        cursor_node.setNext(new_node);
        new_node.setPrev(cursor_node);

        if(back_node == cursor_node) {
            back_node = cursor_node.getNext();
        }

        num_nodes++;
    }

    public void deleteFront() { // Deletes the front element in this List. Pre: length()>0
        
        if(num_nodes < 1 || front_node == null) {
            cursor_index = -1;
            cursor_node = null;
            throw new RuntimeException("Front node is null/ length = 0");
        }

        if(num_nodes == 1) {
            back_node = null;
        }

        front_node = front_node.getNext();

        if(front_node != null)
            front_node.setPrev(null);
        num_nodes--;
    }

    public void deleteBack() { // Deletes the back element in this List. Pre: length()>0
        if(num_nodes < 1 || back_node == null) {
            cursor_index = -1;
            cursor_node = null;
            throw new RuntimeException("Back node is null/length = 0");
        }

        back_node = back_node.getPrev();

        if(back_node != null)
            back_node.setNext(null);
        num_nodes--;
    }

    public void delete() {              // Deletes cursor element in this List. Cursor is undefined after this
                                        // operation. Pre: length()>0, getIndex()>=0
                                        // Other methods
        if(cursor_index < 0 || cursor_node == null || num_nodes == 0) {
            cursor_index = -1;
            cursor_node = null;
            throw new RuntimeException("Cannot delete null cursor");
        }

        if(cursor_node.getNext() != null)
            cursor_node.getNext().setPrev(cursor_node.getPrev());
        if(cursor_node.getPrev() != null)
            cursor_node.getPrev().setNext(cursor_node.getNext());

        cursor_node = null;
        cursor_index = -1;
        num_nodes--;
    
    }

    public String toString() {          // Overides Object's toString method. Creates a string
                                        // consisting of a space separated sequence of integers
                                        // with front on the left and back on the right. The
                                        // cursor is ignored.
        Node walker = front_node;
        String ret_string = "";

        while(walker != null) {
            Object x = walker.getData();
            ret_string += (x.toString()+" ");
            walker = walker.getNext();
        }
        return ret_string;
    
    }

    public List copy() {                // Returns a new list representing the same integer sequence as this
                                        // list. The cursor in the new list is undefined, regardless of the
                                        // state of the cursor in this List. This List is unchanged.
        Node walker = front_node;
        List ret_list = new List();
        while(walker != null) {
            ret_list.append(walker.getData());
            walker = walker.getNext();
        }
        return ret_list;
    }


    public class Node {
        private Object data;
        private Node next;
        private Node prev;

        public Node() {
            next = null;
            prev = null;
        }

        public Node(Object val) {
            data = val;
            next = null;
            prev = null;
        }

        public Node(Object val, Node nxt, Node prv) {
            data = val;
            next = nxt;
            prev = prv;
        }

        public Object getData() {
            return data;
        }

        public void setData(Object dat) {
            data = dat;
        }

        public void setNext(Node nxt) {
            next = nxt;
        }

        public void setPrev(Node prv) {
            prev = prv;
        }

        public Node getNext() {
            return next;
        }

        public Node getPrev() {
            return prev;
        }
    }

}
