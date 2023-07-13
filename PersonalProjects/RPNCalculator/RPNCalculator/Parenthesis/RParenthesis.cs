using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RPNCalculator.Parenthesis
{
    public class RParenthesis : PrecedenceOperator
    {
        private char _op = ')';
        private int _precedence = 0;

        public override char GetOperator()
        {
            return _op;
        }

        public override int GetPrecedence()
        {
            return _precedence;
        }

    }
}
