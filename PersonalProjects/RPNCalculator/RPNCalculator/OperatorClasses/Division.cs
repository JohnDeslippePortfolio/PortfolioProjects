using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
 * Name: Subtraction
 * Purpose: defines the concrete implementation of the '/' operator
 * Author: John Deslippe 
 * Date: July 13, 2023
 */
namespace RPNCalculator.OperatorClasses
{
    public class Division : BinaryOperator
    {
        private char _op = '/';
        private int _precedence = 2;
        public override char GetOperator()
        {
            return _op;
        }

        public override int GetPrecedence()
        {
            return _precedence;
        }

        public override int Operate(Operand lhs, Operand rhs)
        {
            return lhs.GetValue() / rhs.GetValue();
        }
    }
}
