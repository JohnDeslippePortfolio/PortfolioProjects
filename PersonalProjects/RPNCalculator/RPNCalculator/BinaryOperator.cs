using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
 * Name: BinaryOperator
 * Purpose: defines the abstract class for all Binary operators (operators that take 2 argumentss IE + * / -)
 * Author: John Deslippe
 * Date: July 13, 2023
 */
namespace RPNCalculator
{
    public abstract class BinaryOperator : Operator
    {
        /*
         * Name: Operatore
         * Purpose: provides the abstracte declaration of the Operate function all binary operates must posses
         * Accepts: the left and right hands sides of the expression to be evaluated
         * Returns: the integer value of the calculation
         */
        public abstract int Operate(Operand lhs, Operand rhs);
    }
}
