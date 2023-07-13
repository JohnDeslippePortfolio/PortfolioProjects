using RPNCalculator.OperatorClasses;
using System.Text;

namespace RPNCalculator
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter an expresion: ");
            string userInput = Console.ReadLine() ?? ""; //prompt and read user input
            RPNBuilder builder = new RPNBuilder(userInput); //construct the builder object using the users input
            builder.BuildRPN(); //construct the RPN equation and solve it
            
         
            
        }
    }
}