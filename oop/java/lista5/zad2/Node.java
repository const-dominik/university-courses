class Add extends Expression
{
    Expression left;
    Expression right;

    public Add(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;
    }

    public String toString()
    {
        return String.format("(%s + %s)", left.toString(), right.toString());
    }

    public int evaluate()
    {
        return left.evaluate() + right.evaluate();
    }
}

class Subtract extends Expression
{
    Expression left;
    Expression right;

    public Subtract(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;
    }

    public String toString()
    {
        return String.format("(%s - %s)", left.toString(), right.toString());
    }

    public int evaluate()
    {
        return left.evaluate() - right.evaluate();
    }
}