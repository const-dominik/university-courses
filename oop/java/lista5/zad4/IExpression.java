public interface IExpression
{
    String toString();
    int evaluate(int x);
    Expression derivate();
}