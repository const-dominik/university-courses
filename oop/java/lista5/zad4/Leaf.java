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

    public int evaluate(int x)
    {
        return this.value;
    }

    public Expression derivate()
    {
        return new Const(0);
    }
}

class Variable extends Expression
{
    String name;

    public Variable(String name)
    {
        this.name = name;
    }

    public String toString()
    {
        return this.name;
    }

    public int evaluate(int x)
    {
        return x;
    }

    public Expression derivate()
    {
        return new Const(1);
    }
}