using System;

class Program
{
  private static Dictionary<string, Func<int, int, int>> operators = new () {
      { "+", (a, b) => a + b },
      { "-", (a, b) => b - a },
      { "*", (a, b) => a * b },
      { "/", (a, b) => b / a },   
    };

  public static int EvalRPN(string[] tokens)
  {
    Stack<int> data = new();

    foreach (string token in tokens)
      if (int.TryParse(token, out int value))
        data.Push(value);
      else
        data.Push(operators[token](data.Pop(), data.Pop()));

    return data.Pop();
  }

  public static TimeSpan TestTime(string[] tokens, int n)
    {
      DateTime start = DateTime.Now;
      for (int i = 0; i < n; i++)
      {
        EvalRPN(tokens);
      }
      DateTime end = DateTime.Now;
      TimeSpan duration = end - start;
      return duration;
    }
    
    public static void Main(string[] args)
    {
        string expression = "10 6 9 3 + -11 * / * 17 + 5 +";
        string[] tokens = expression.Split(' ');

        int result = EvalRPN(tokens);
        Console.WriteLine($"Result: {result}");

        TimeSpan duration = TestTime(tokens, 1000000);
        Console.WriteLine($"Duration: {duration}");
    }
}