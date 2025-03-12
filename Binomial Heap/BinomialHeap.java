import java.util.LinkedList;
import java.util.Queue;
import java.util.Vector;

public class BinomialHeap
{
    BinomialNode Node;
    int heap_size;
    public class BinomialNode
    {
        BinomialNode parent;
        int key,degree;
        BinomialNode child;
        BinomialNode sibling;
        public BinomialNode(int value)
        {
            key=value;
            parent=null;
            child=null;
            degree=0;
            sibling=null;
        }
        public int nodeHeight()
        {
            int child_size=-1;
            int sibling_size=-1;
            if(child==null)
                child_size=0;
            else child_size=child.nodeHeight();
            if(sibling==null)
                sibling_size=0;
            else sibling_size=sibling.nodeHeight();
            return 1+child_size+sibling_size;

        }
        public BinomialNode find_minNode()
        {
            BinomialNode min_Node=this,current_Node=this;
            int minimum_key=current_Node.key;
            while(current_Node!=null)
            {
                if(current_Node.key<minimum_key)
                {
                    min_Node=current_Node;
                    minimum_key=current_Node.key;
                }
                current_Node=current_Node.sibling;
            }
            return min_Node;
        }
        public BinomialNode reverse(BinomialNode node)
        {
            BinomialNode leftmostNode;
            if(sibling!=null)
            {
                leftmostNode=sibling.reverse(this);
            }
            else leftmostNode=this;
            sibling=node;
            return leftmostNode;
        }

    }
    public BinomialHeap()
    {
        Node=null;
        heap_size=0;
    }
    public void merge(BinomialNode heap_node)
    {
        BinomialNode first_node=Node,second_node=heap_node;
        while((first_node!=null)&&(second_node!=null))
        {
            if(first_node.degree==second_node.degree)
            {
                BinomialNode temp=second_node;
                second_node=second_node.sibling;
                temp.sibling=first_node.sibling;
                first_node.sibling=temp;
                first_node=temp.sibling;
            }
            else
            {
                if (first_node.degree<second_node.degree)
                {
                    if((first_node.sibling==null)||(first_node.sibling.degree>second_node.degree))
                    {
                        BinomialNode temp=second_node;
                        second_node=second_node.sibling;
                        temp.sibling=first_node.sibling;
                        first_node.sibling=temp;
                        first_node=temp.sibling;
                    }
                    else
                    {
                        first_node=first_node.sibling;
                    }
                }
                else
                {
                    BinomialNode temp=first_node;
                    first_node=second_node;
                    second_node=second_node.sibling;
                    first_node.sibling=temp;
                    if(temp==Node) {
                        Node = first_node;
                    }
                }
            }
        }
        if(first_node==null)
        {
            first_node=Node;
            while (first_node.sibling!=null)
            {
                first_node=first_node.sibling;
            }
            first_node.sibling=second_node;
        }

    }



    public void union_of_Nodes(BinomialNode node)
    {
        merge(node);
        BinomialNode prev=null;
        BinomialNode temp=Node,next=Node.sibling;
        while (next!=null)
        {
            if((temp.degree!=next.degree)||((next.sibling!=null)&&(next.sibling.degree==temp.degree)))
            {
                prev=temp;
                temp=next;
            }
            else
            {
                if(temp.key<=next.key)
                {
                    temp.sibling=next.sibling;
                    next.parent=temp;
                    next.sibling=temp.child;
                    temp.child=next;
                    temp.degree++;
                }
                else
                {
                    if(prev==null)
                    {
                        Node=next;
                    }
                    else
                    {
                        prev.sibling=next;
                    }
                    temp.parent=next;
                    temp.sibling=next.child;
                    next.child=temp;
                    next.degree++;
                    temp=next;
                }
            }
            next=temp.sibling;
        }


    }
    public void insert(int val)
    {
        BinomialNode temp = new BinomialNode(val);
        if (Node == null) {
            Node = temp;
            heap_size = 1;
        } else
        {
            union_of_Nodes(temp);
            heap_size++;
        }

    }
    public int find_min()
    {
        return Node.find_minNode().key;
    }
    public void union(Vector<Integer>v1)
    {
        for(int i=0;i<v1.size();i++)
        {
            insert(v1.get(i));
        }
    }

    public int extract_min()
    {
        if(Node==null)
            return -1;
        BinomialNode temp=Node,prev=null;
        BinomialNode minimum_Node=Node.find_minNode();
        while(temp.key!=minimum_Node.key)
        {
            prev=temp;
            temp=temp.sibling;
        }
        if(prev==null)
        {
            Node=temp.sibling;
        }
        else
        {
            prev.sibling=temp.sibling;
        }
        temp=temp.child;
        BinomialNode temp1=temp;
        while (temp!=null)
        {
            temp.parent=null;
            temp=temp.sibling;
        }
        if(this.Node==null&&temp1==null)
        {
            heap_size=0;
        }
        else
        {
            if(this.Node==null&&temp1!=null)
            {
                Node=temp1.reverse(null);
                heap_size=Node.nodeHeight();
            }
            else
            {
                if(this.Node!=null&&temp1==null)
                {
                    heap_size=Node.nodeHeight();
                }
                else
                {
                    union_of_Nodes(temp1.reverse(null));
                    heap_size=Node.nodeHeight();
                }
            }
        }
        return minimum_Node.key;

    }
    public void print()
    {
        System.out.println("Printing Binomial Heap...");

        BinomialNode current =Node;
        while (current != null) {
            System.out.print("Binomial Tree, B" + current.degree + "\n");
            display(current);
            current = current.sibling;
        }
    }
    public void display(BinomialNode node)
    {
        if (node == null) {
            System.out.println();
            return;
        }
        int i = 0;
        Queue<BinomialNode> levelOrder = new LinkedList<>();
        levelOrder.add(node);
        Queue<BinomialNode> nextLevel = new LinkedList<>();
        System.out.print("Level " + i + " :");
        while (!levelOrder.isEmpty()) {
            BinomialNode currNode = levelOrder.poll();
            System.out.print(" " + currNode.key);
            if (currNode.child != null)
            {
                BinomialNode children = currNode.child;
                while (children != null)
                {
                    nextLevel.add(children);
                    children = children.sibling;
                }
            }
            if (levelOrder.isEmpty())
            {
                levelOrder = nextLevel;
                nextLevel = new LinkedList<>();
                System.out.println();
                i++;
                if (!levelOrder.isEmpty())
                    System.out.print("Level " + i + " :");
            }
        }
    }
}
