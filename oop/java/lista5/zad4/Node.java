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

    public int evaluate(int x)
    {
        return left.evaluate(x) + right.evaluate(x);
    }

    public Expression derivate()
    {
        return new Add(left.derivate(), right.derivate());
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

    public int evaluate(int x)
    {
        return left.evaluate(x) - right.evaluate(x);
    }

    public Expression derivate()
    {
        return new Subtract(left.derivate(), right.derivate());
    }
}

class Multiply extends Expression
{
    Expression left;
    Expression right;

    public Multiply(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;       
    }

    public String toString()
    {
        return String.format("(%s * %s)", left.toString(), right.toString());
    }

    public int evaluate(int x)
    {
        return left.evaluate(x) * right.evaluate(x);
    }

    public Expression derivate()
    {
        return new Add(new Multiply(left.derivate(), right), new Multiply(left, right.derivate()));
    }
}