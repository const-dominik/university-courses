import java.util.Hashtable;
import java.io.*;

class Const extends Expression
{
    int value;

    public Const(int value)
    {
        this.value = value;
    }

    public String toString()
    {
        return String.valueOf(this.value);
    }

    public int evaluate()
    {
        return this.value;
    }   
}

class Variable extends Expression
{
    String name;
    static public Hashtable<String, Integer> values;

    public Variable(String name)
    {
        this.name = name;
    }

    private void checkKey(String key) throws IOException
    {
        if (!values.containsKey(this.name))
            throw new IOException("Key not found.");
    }

    public String toString()
    {
        return this.name;
    }

    public int evaluate()
    {
        try {
            this.checkKey(this.name);
            return values.get(this.name);
        } catch (IOException e) {
            String errorMessage = String.format("Brak klucza dla %s, traktuje %s jako 0", this.name, this.name);
            System.out.println(errorMessage);
            return 0;
        }
    }
}