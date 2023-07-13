using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;

/*
 * Name: Operator
 * Purpose: Defines the abstract Operator class, used for the purpose of inheritance
 * Author: John Deslippe
 * Date: July 13, 2023
 */
namespace RPNCalculator
{
    public abstract class Operator : EquationItem
    {
        
        //Accessor Methods
        public abstract char GetOperator();
        public abstract int GetPrecedence();

    }
}
