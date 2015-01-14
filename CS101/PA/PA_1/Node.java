
public class Node {
    int data;
    Node next;

    public Node() {
        next = null;
    }

    public Node(int val) {
        data = val;
        next = null;
    }

    public Node(int val, Node, nxt) {
        data = val;
        next = nxt;
    }

    public int getData() {
        return data;
    }

    public void setData(int dat) {
        data = dat;
    }

    public void setNext(Node nxt) {
        next = nxt;
    }

    public Node getNext() {
        return next;
    }
}