/**
* Program Name: LongOperandException.java
* Purpose: Creates a custom exception for handling Long Operands entered into the calculator
* @author John Deslippe 0754326
* Date: Aug 6, 2022
*/

public class LongOperandException extends Exception{
	
	//constructor
	LongOperandException(){
		super("Long operand exception occured");
	}
}
//End of class