abstract class Expression implements IExpression
{
    public abstract int evaluate(int x);
    public abstract String toString();
    public abstract Expression derivate();
}