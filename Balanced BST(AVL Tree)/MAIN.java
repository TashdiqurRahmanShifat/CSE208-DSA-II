import java.io.*;

public class MAIN
{
    public static void main(String[] args) {
        try
        {
            BufferedReader br=new BufferedReader(new FileReader("in.txt"));
            BufferedWriter bw=new BufferedWriter(new FileWriter("out_avl.txt"));
            BufferedWriter report=new BufferedWriter(new FileWriter("report_avl.txt"));

            AVL_Tree avlTree=new AVL_Tree();
            String str= null;
            String []token;
            String function="";
            String data="";

            double insert_count=0;
            double insert_totaltime=0;
            double delete_count=0;
            double delete_totaltime=0;
            double search_count=0;
            double search_totaltime=0;
            double trav_count=0;
            double trav_totaltime=0;
            double insert_start=-1,insert_end=-2;
            double delete_start=-1,delete_end=-2;
            double search_start=-1,search_end=-2;
            double trav_start=-1,trav_end=-2;
            while((str=br.readLine())!=null)
            {

                token=str.split(" ");
                function=token[0];
                data=token[token.length-1];
                switch (function)
                {
                    case "I":
                        insert_count++;
                        insert_start=System.nanoTime();
                        avlTree.insert(Integer.valueOf(data));
                        insert_end=System.nanoTime();
                        insert_totaltime+=insert_end-insert_start;
                        bw.write((avlTree.currentstate()));
                        bw.write(System.lineSeparator());
                        break;
                    case "F":
                        search_count++;
                        search_start=System.nanoTime();
                        bw.write(avlTree.find(Integer.valueOf(data)));
                        search_end=System.nanoTime();
                        search_totaltime+=search_end-search_start;
                        bw.write(System.lineSeparator());
                        break;
                    case "T":
                        trav_count++;
                        trav_start=System.nanoTime();
                        bw.write(avlTree.inorder());
                        trav_end=System.nanoTime();
                        trav_totaltime+=trav_end-trav_start;
                        bw.write(System.lineSeparator());
                        break;
                    case "D":
                        delete_count++;
                        delete_start=System.nanoTime();
                        bw.write(avlTree.delete(Integer.valueOf(data)));
                        delete_end=System.nanoTime();
                        delete_totaltime+=delete_end-delete_start;
                        bw.write(System.lineSeparator());
                        break;
                }

            }

            report.write("operation time(ms)");
            report.write(System.lineSeparator());

            report.write("insert ");
            report.write(String.valueOf(String.format("%.8f",(insert_totaltime/1000000)/insert_count)));
            report.write(System.lineSeparator());

            report.write("delete ");
            report.write(String.valueOf(String.format("%.8f",(delete_totaltime/1000000)/delete_count)));
            report.write(System.lineSeparator());

            report.write("search ");
            report.write(String.valueOf(String.format("%.8f",(search_totaltime/1000000)/search_count)));
            report.write(System.lineSeparator());

            report.write("trav   ");
            report.write(String.valueOf(String.format("%.8f",(trav_totaltime/1000000)/trav_count)));
            report.write(System.lineSeparator());

            String total_time=String.valueOf(String.format("%.8f",(Double.valueOf(insert_totaltime/insert_count)+Double.valueOf(delete_totaltime/delete_count)+Double.valueOf(search_totaltime/search_count)+Double.valueOf(trav_totaltime/trav_count))/1000000));
            report.write("total  "+total_time);

            br.close();
            bw.close();
            report.close();

        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

    }
}
