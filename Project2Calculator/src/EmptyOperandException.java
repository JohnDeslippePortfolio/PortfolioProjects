/**
* Program Name: LongOperandException.java
* Purpose: Creates a custom exception for handling Empty Operands entered into the calculator
* @author John Deslippe 0754326
* Date: Aug 6, 2022
*/

public class EmptyOperandException extends Exception {
	EmptyOperandException(){
		super("Empty operand exception occured");
	}
}
//End of class