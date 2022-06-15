import java.io.*;

public class Program
{
    public static void main(String[] args)
    {
        LazyIntList list = new LazyIntList();
        System.out.println(String.format("element 40: %d", list.element(40)));

        try {
            FileOutputStream fileOut =
            new FileOutputStream("./list.ser");
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(list);
            out.close();
            fileOut.close();
            System.out.println("Serialized data is saved in ./list.ser");
        } catch (IOException i) {
            i.printStackTrace();
        }

        LazyIntList list2 = null;
        try {
            FileInputStream fileIn = new FileInputStream("./list.ser");
            ObjectInputStream in = new ObjectInputStream(fileIn);
            list2 = (LazyIntList)in.readObject();
            in.close();
            fileIn.close();
         } catch (IOException i) {
            i.printStackTrace();
            return;
         } catch (ClassNotFoundException c) {
            System.out.println("LazyIntList class not found");
            c.printStackTrace();
            return;
         }
        System.out.println(String.format("size list 2: %d", list2.size()));
        //size is 40, works :thumbsup:
    }
}