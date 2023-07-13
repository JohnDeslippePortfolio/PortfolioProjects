using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
 * Name: Operand
 * Purpose: defines the concrete implementation of the Operand class
 * Author: John Deslippe
 * Date: July 13, 2023
 */
namespace RPNCalculator
{
    public class Operand : EquationItem
    {
        private int _value; //value of the operand 

        public Operand(int value)
        {
            _value = value;
        }

        public Operand(string value)
        {
            _value = int.Parse(value);
        }

        public int GetValue() { return _value; }
    }
}
