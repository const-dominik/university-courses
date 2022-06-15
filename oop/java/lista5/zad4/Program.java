public class Program
{
   public static void main(String[] args)
   {
      Expression expr1 = new Add(new Const(4), new Variable("x"));
      Expression expr2 = new Add(new Const(5), new Variable("x"));
      Expression expr3 = new Subtract(new Variable("x"), new Const(20));
      Expression expr4 = new Multiply(expr1, expr3);
      System.out.println(String.format("%s' = %s", expr1, expr1.derivate()));
      System.out.println(String.format("%s' = %s", expr2, expr2.derivate()));
      System.out.println(String.format("%s' = %s", expr3, expr3.derivate()));
      System.out.println(String.format("%s' = %s", expr4, expr4.derivate()));
   }
}