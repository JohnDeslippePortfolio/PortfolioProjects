using RPNCalculator.OperatorClasses;
using RPNCalculator.Parenthesis;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
 * Name: RPNBuilder
 * Purpose: handles the actual creation of an rpn statement construction from user input and abstract it for the end console client
 *          Note that the algorithm used is the shunting yard infix notation algorithm retrieved from https://brilliant.org/wiki/shunting-yard-algorithm/
 * Author: John Deslippe
 * Date: July 13, 2023
 */
namespace RPNCalculator
{
    public class RPNBuilder
    {
        private string formula; //contains the raw user input
        private Stack<Operator> operatorStack = new Stack<Operator>();

        private List<EquationItem> rpn = new List<EquationItem>(); //list containing the final rpn Notation formula
        private List<EquationItem> infix = new List<EquationItem>(); //list containing the infix notation formula the user provides

        private char[] allOperators = { '+', '-', '*', '/' }; //list of valid operators
        public RPNBuilder(string formula) { this.formula = formula.Replace(" ", "") ; } //constructor, ensures that the users input will not have any white space int it


        /*
         * Name: BuildRPN
         * Purpose: primary function of the RPNBuilder class, process the values stores in formula passed during object creation and display all formatted values to console
         * Accepts: nothing
         * Returns: void
         */
        public void BuildRPN()
        {
            FormatFormula(); //clean the users input
            BuildInfix(); //generates the infix statement from user input

            //iterate through infix, implement shunting yard formula to rearrange the formula into postfix RP notation
            foreach(EquationItem item in infix)
            {
                if (item.GetType() == typeof(Operand)) //if the item is an operand(number value) always add it to the RPN equation
                {
                    rpn.Add(item);
                }
                else if(item.GetType().IsSubclassOf(typeof(BinaryOperator))) //if its an operator put it onto the operator stack, if any operator is on the stack, ensure precedence is handled
                {
                    Operator op = (Operator)item;
                    while( operatorStack.Count > 0 && operatorStack.Peek().GetPrecedence() > op.GetPrecedence())
                    {
                        rpn.Add(operatorStack.Pop());
                    }
                    operatorStack.Push(op);
                }
                else if (item.GetType().IsSubclassOf(typeof(PrecedenceOperator))) //if its a '(' or ')' handle precedence accordingly
                {
                    if(item.GetType() == typeof(LParenthesis)){
                        operatorStack.Push((LParenthesis)item);
                    }
                    else
                    {
                        while(operatorStack.Peek().GetType() != typeof(LParenthesis))
                        {
                            rpn.Add(operatorStack.Pop());
                        }
                        operatorStack.Pop(); //discarding the ( item
                    }
                }
            }
            while(operatorStack.Count> 0) //after the infix notation has been completely handled, ensure no operators are left unhandled on the stack
            {
                rpn.Add(operatorStack.Pop());
            }

            //display results to the console
            foreach(EquationItem item in rpn)
            {
                if(item.GetType().IsSubclassOf(typeof(Operator)))
                {
                    Operator op = (Operator)item;
                    Console.Write(op.GetOperator());
                }
                else
                {
                    Operand op = (Operand)item;
                    Console.Write(op.GetValue() + " ");
                }
            }
            Console.WriteLine("");
            SolveRPN();
            foreach (EquationItem item in rpn)
            {
                if (item.GetType().IsSubclassOf(typeof(Operator)))
                {
                    Operator op = (Operator)item;
                    Console.Write(op.GetOperator());
                }
                else
                {
                    Operand op = (Operand)item;
                    Console.Write(op.GetValue() + " ");
                }
            }
        }

        /*
         * Name: BuildInfix
         * Purpose: convert the white space delimited string the user provides into a infix notatio formula utilizing the various classes inherited from Equation items
         * Accepts: nothing
         * Returns: void
         */
        private void BuildInfix()
        {
            List<String> allItems = new List<String>(formula.Split(" ")); // all items in the formula, delimited by a whitespace
            foreach (String item in allItems) //foreach item, determine if it is a operator, parenthesis or operand
            {
                if (IsOperator(item))
                {
                    infix.Add(GetOperator(item)!);
                }
                else if (IsParenthesis(item)) {
                    infix.Add(GetParenthesis(item)!);
                }
                else //if not operator, must be operand
                {
                    infix.Add(new Operand(Int32.Parse(item)));
                }
            }
        }

        /*
         * Name: SolveRPN
         * Purpose: using the rpn object list, solve the equation using the inherited Operate method of the operators
         * Accepts: nothing
         * Returns: void
         */
        private void SolveRPN()
        {
            
            for(int i = 0; i < rpn.Count; i++)
            {
                if (rpn[i].GetType().IsSubclassOf(typeof(BinaryOperator)))
                {
                    BinaryOperator op = (BinaryOperator)rpn[i];
                    Operand temp = new Operand(op.Operate((Operand)rpn[i - 2], (Operand)rpn[i - 1]));
                    rpn[i] = temp;
                    rpn.RemoveAt(i-1);
                    i--;
                    rpn.RemoveAt(i - 1);
                    i--;

                }
            }
        }

        /*
         * Name: FormatFormula
         * Purpose: cleans the users input to ensure that all items in the string are delimited appropriately by whitespace
         * Accepts: nothing
         * Returns: voids
         */
        private void FormatFormula()
        {
            StringBuilder temp = new StringBuilder();
            for(int i = 0; i < formula.Length; i++)
            {
                if (IsOperator(formula[i].ToString()))
                {
                    if(i > 0 && temp[temp.Length-1].ToString() == " ")
                    {
                        temp.Append(formula[i] + " ");
                    }
                    else
                    {
                        temp.Append(" " + formula[i] + " ");
                    }
                }
                else if (IsParenthesis(formula[i].ToString())){
                    if (i == formula.Length - 1)
                    {
                        temp.Append(" " + formula[i]);
                    }
                    else if(i > 0 && temp[temp.Length-1].ToString() == " ")
                    {
                        temp.Append(formula[i] + " ");
                    }
                    else if(i == 0)
                    {
                        temp.Append(formula[i] + " ");
                    }
                   else
                    {
                        temp.Append(" " + formula[i] + " ");
                    }
                }
                else
                {
                    temp.Append(formula[i]);
                }
            }//end for
            formula = temp.ToString();
        }//end FormatFormula

       /*
        * Name: IsOperator
        * Purpose: Determinse if a string is an operator that the program is suited to handle
        * Accepts: A String of the potential operator to evaluate
        * Returns: True if the string is a valid operator
        */
       private bool IsOperator(string item)
        {
            for (int j = 0; j < allOperators.Length; j++)
            {
                if (item == allOperators[j].ToString())
                {
                    return true;
                }// end if
            }  //end for 
            return false;
        }

        /*
         * Name: IsParenthesis
         * Purpose: Determines if a string is a Parenthesis
         * Accepts: A String of the potential parenthesis
         * Returns: True if the string is a parenthesis
         */
        private bool IsParenthesis(string item)
        {
            if(item == ")" || item == "(")
            {
                return true;
            }
            return false;
        }

        /*
         * Name: GetOperator
         * Purpose: Create an operator object corresponding to the string passed to it
         * Accepts: A string representation of the object to create
         * Returns: An Operator object based on string provided, returns null if the string is invalid
         */
        private Operator? GetOperator(string item)
        {
           if(item == "+")
            {
                return new Addition();
            }
           else if(item == "-")
            {
                return new Subtraction();
            }
           else if(item == "*")
            {
                return new Multiplication();
            }
           else if(item == "/")
            {
                return new Division();
            }
           else
            {
               return null;
            }
        }
        /*
        * Name: GetParenthesis
        * Purpose: Create a PrecedenceOperator object corresponding to the string passed to it
        * Accepts: A string representation of the object to create
        * Returns: A PrecedenceOperator object based on string provided, returns null if the string is invalid
        */
        private PrecedenceOperator? GetParenthesis (string item)
        {
            if(item == "(")
            {
                return new LParenthesis();
            }
            else if(item == ")")
            {
                return new RParenthesis();
            }
            else
            {
                return null;
            }
        }
    }
}
