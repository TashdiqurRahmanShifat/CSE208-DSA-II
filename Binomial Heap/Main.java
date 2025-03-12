import java.io.*;
import java.util.Vector;

public class Main
{
    public static void main(String[] args) {
        try
        {
            BufferedReader br=new BufferedReader(new FileReader("input.txt"));
            FileOutputStream fs = new FileOutputStream("output.txt");
            System.setOut(new PrintStream(fs));
            BinomialHeap binheap=new BinomialHeap();
            Vector<Integer>v=new Vector<Integer>();

            String str= null;
            String []token;
            String function="";
            String data="";

            while((str=br.readLine())!=null)
            {
                v=new Vector<Integer>();
                token=str.split(" ");
                function=token[0];
                data=token[token.length-1];
                if(token.length>=2)
                {
                    for(int i=1;i<token.length;i++)
                    v.add(Integer.valueOf(token[i]));
                }

                switch (function)
                {
                    case "I":
                        binheap.insert(Integer.valueOf(data));
                        break;
                    case "F":
                        System.out.print("Find-Min returned ");
                        System.out.println(binheap.find_min());
                        break;
                    case "E":
                        System.out.print("Extract-Min returned ");
                        System.out.println(binheap.extract_min());
                        break;
                    case "U":
                        binheap.union(v);
                        break;
                    case "P":
                        binheap.print();
                        break;
                }

            }
            br.close();
            fs.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

    }
}
