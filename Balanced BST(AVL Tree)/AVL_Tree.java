public class AVL_Tree {
    Node root;
    public class Node
    {
        Node leftsubtree;
        Node rightsubtree;
        int value;
        int height;
        Node(int value)
        {
            leftsubtree=null;
            rightsubtree=null;
            this.value=value;
            height=0;
        }

    }
    public AVL_Tree()
    {
        root=null;
    }
    public int height(Node root)
    {
        if(root==null)
            return -1;
        else return root.height;
    }

    public int updateheight(int leftheight,int rightheight)
    {
        if(leftheight==rightheight)
            return leftheight;
        else if(leftheight>rightheight)
            return leftheight;
        else return rightheight;
    }

    public Node rightrotation(Node root)
    {
        Node temp=root.leftsubtree;
        root.leftsubtree=temp.rightsubtree;
        temp.rightsubtree=root;
        root.height=updateheight(height(root.leftsubtree),height(root.rightsubtree))+1;
        temp.height=updateheight(height(temp.leftsubtree),root.height)+1;
        return temp;
    }
    public Node leftrotation(Node root)
    {
        Node temp=root.rightsubtree;
        root.rightsubtree=temp.leftsubtree;
        temp.leftsubtree=root;
        root.height=updateheight(height(root.leftsubtree),height(root.rightsubtree))+1;
        temp.height=updateheight(height(temp.rightsubtree),root.height)+1;
        return temp;
    }
    public Node left_right_rotation(Node root)
    {
        root.leftsubtree=leftrotation(root.leftsubtree);
        return rightrotation(root);
    }
    public Node right_left_rotation(Node root)
    {
        root.rightsubtree=rightrotation(root.rightsubtree);
        return leftrotation(root);
    }
    public int balance_factor(Node root)
    {
        if(root==null)
            return 0;
        return height(root.leftsubtree)-height(root.rightsubtree);
    }
    public Node insert(int val)
    {
        root=insertat(root,val);
        return root;
    }
    public Node insertat(Node root,int val)
    {
        if(root==null)
        {
            root=new Node(val);
            return root;
        }
        else if(root.value>val)
        {
            root.leftsubtree=insertat(root.leftsubtree,val);
            int leftBF=balance_factor(root);
            if(leftBF>1)
            {
                if(root.leftsubtree.value>val)
                {
                    root=rightrotation(root);
                }
                else
                {
                    root=left_right_rotation(root);
                }
            }

        }
        else if(root.value<val)
        {
            root.rightsubtree=insertat(root.rightsubtree,val);
            int rightBF=balance_factor(root);
            if(rightBF<-1)
            {
                if(root.rightsubtree.value<val)
                {
                    root=leftrotation(root);
                }
                else
                {
                    root=right_left_rotation(root);
                }
            }
        }
        root.height=updateheight(height(root.leftsubtree),height(root.rightsubtree))+1;
        return root;
    }
    public String find(int value)
    {
        String s="";
        Node x=search(root,value);
        if(x==null) s=s+"not found";
        else s=s+"found";
        return s;
    }
    public Node search(Node root,int val)
    {
        if(root==null)
            return null;
        if(root.value==val)
            return root;
        if(root.value>val)
            return search(root.leftsubtree,val);
        return search(root.rightsubtree,val);
    }
    public String inorder() {
        return in_order(root);
    }

    public String in_order(Node root) {

        if(root==null)
            return "";
        String left= in_order(root.leftsubtree);
        String right=in_order(root.rightsubtree);
        return left+root.value+" "+right;

    }

    public String delete(int val)
    {
        String s="";
        root=dlt(root,val);

        s=s+currentstate();
        return s;

    }
    public Node dlt(Node root, int val)
    {

        if(root==null)return null;
        if(root.value>val)
            root.leftsubtree=dlt(root.leftsubtree,val);
        else if (root.value<val)
        {
            root.rightsubtree=dlt(root.rightsubtree,val);
        }
        //root.value==val
        else
        {
            if(root.leftsubtree==null&&root.rightsubtree==null)
                return null;
            if(root.leftsubtree==null)
                return root.rightsubtree;
            else if(root.rightsubtree==null)
                return root.leftsubtree;
            Node IS=inorderSuccessor(root.rightsubtree);
            root.value= IS.value;
            root.rightsubtree=dlt(root.rightsubtree, IS.value);
        }

        root.height=updateheight(height(root.leftsubtree),height(root.rightsubtree))+1;
        int balancefactor=balance_factor(root);
        if(balancefactor>1&&balance_factor(root.leftsubtree)>=0)
            return rightrotation(root);
        if(balancefactor>1&&balance_factor(root.leftsubtree)<0)
            return left_right_rotation(root);
        if(balancefactor<-1&&balance_factor(root.rightsubtree)<=0)
            return leftrotation(root);
        if(balancefactor<-1&&balance_factor(root.rightsubtree)>0)
            return right_left_rotation(root);
        return root;
    }
    public Node inorderSuccessor(Node root)
    {
        while (root.leftsubtree!=null)
            root=root.leftsubtree;
        return root;
    }
    public String currentstate()
    {
        return currentState(root);
    }
    public String currentState(Node root)
    {
        if (root == null)
            return "";

        String left=currentState(root.leftsubtree);
        String right=currentState(root.rightsubtree);
        if(!(root.leftsubtree==null&&root.rightsubtree==null))
            left="("+left+",";
        if(root.leftsubtree!=null&&root.rightsubtree==null)
            right=")";

        if(root.rightsubtree!=null)
            right=right+")";

        return root.value+left+right;
    }
}
