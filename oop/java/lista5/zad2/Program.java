import java.util.Hashtable;

public class Program
{
   public static void main(String[] args)
   {
      Hashtable<String, Integer> variables = new Hashtable<String, Integer>();

      variables.put("a", 100);
      variables.put("b", -20);
      variables.put("c", 15);
      variables.put("d", 50);

      Variable.values = variables; 
      Expression expr = new Add(new Const(4), new Variable("x"));
      Expression expr2 = new Add(new Const(5), new Variable("c"));
      Expression expr3 = new Add(new Const(42), new Const(0));
      Expression expr4 = new Subtract(new Variable("d"), new Const(20));
      Expression expr5 = new Add(expr, expr2);
      System.out.println(String.format("%s = %s", expr, expr.evaluate()));
      System.out.println(String.format("%s = %s", expr2, expr2.evaluate()));
      System.out.println(String.format("%s = %s", expr3, expr3.evaluate()));
      System.out.println(String.format("%s = %s", expr4, expr4.evaluate()));
      System.out.println(String.format("%s = %s", expr5, expr5.evaluate()));
   }
}