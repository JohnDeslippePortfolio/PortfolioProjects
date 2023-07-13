/**
* Program Name: Calculator.java
* Purpose: Defines the behaviour of the buttons avaliable on the calculator application
* @author John Deslippe 0754326
* Date: Aug 6, 2022
*/

import java.util.ArrayList;

public class Calculator {
	//Attributes
	private String operand; //contains the current working number
	private String operator; //contains the current operator
	private boolean decimalPressed; //flag if the operand already contains a '.'
	private ArrayList<String> list; //stores all of the operands and operators
	
	//Constructor
	//Creates a new calculator object with default values
	public Calculator() {
		operand = "";
		operator = "";
		decimalPressed = false;
		list = new ArrayList<String>();
	}
	
	//Accesors
	public String getOperand() {return operand;}
	public String getOperator() {return operator;}
	public boolean getDecimalPressed() {return decimalPressed;}
	
	//Mutators
	public void setOperand(String op) {operand = op;}
	public void setOperator(String op) {operator = op;}
	public void setDecimalPressed(boolean b) {decimalPressed = b;}
	
	//Methods
	/*
	 * Name: clear
	 * Purpose: Resets all values stored in the calculator to initial values
	 * Returns: void
	 */
	public void clear() {
		operand = "";
		operator = "";
		decimalPressed = false;
		list.clear();
	}
	
	/*
	 * Name: Backspace
	 * Accepts: A string to remove the ending character from
	 * Purpose: Removes the ending character of a string
	 * Returns: The formatted string
	 */
	public String backspace(String in) throws EmptyOperandException {
		if(!in.equals("")) {
			if(in.charAt(in.length() - 1) == '.') {
				this.decimalPressed = false;
			}
			return in.substring(0, in.length()-1);
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: findPercentage
	 * Accepts: a number stored in a String
	 * Purpose: convert the value to a percent represented as a double nnumber
	 * Returns: the formatted number as a String
	 */
	public String findPercentage(String in) throws EmptyOperandException{
		if(!in.equals("")) {
			double d  = Double.parseDouble(in);
			d /= 100;
			return Double.toString(d);
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: toggplePlusMinus
	 * Accepts: boolean that determines if the sign has already been changed
	 * Purpose: Alternates the current operand between positive and negative
	 * Returns: the number as a positive or negative value
	 */
	public String togglePlusMinus(boolean flag) throws EmptyOperandException{
		if(!getOperand().equals("")) {
			if(!flag) {
				return "-" + getOperand();
			}
			else {
				return getOperand().substring(1);
			}
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: findSquared
	 * Accepts: a number to square formatted as a String
	 * Purpose: returns the square of the received number
	 * Returns: the squared value of the received number, formatted as a String
	 */
	public String findSquared(String in) throws EmptyOperandException{
		if(!in.equals("")) {
			double d = Double.parseDouble(in);
			d = d * d;
			return Double.toString(d);
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: findSquareRoot
	 * Accepts: a number to square root formatted as a String
	 * Purpose: returns the square root of the received number
	 * Returns: the square root value of the received number, formatted as a String
	 */
	public String findSquareRoot(String in) throws EmptyOperandException{
		if(!in.equals("")) {
			double d = Double.parseDouble(in);
			d = Math.sqrt(d);
			return Double.toString(d);
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: buildOperand
	 * Accepts: String to add to the operand
	 * Purpose: builds the operand string by appending the received character to the end
	 * Returns: void
	 */
	public void buildOperand(String in) throws LongOperandException{
		if(this.operand.length() == 20) {
			throw new LongOperandException();
		}
		else {
			this.operand += in;
		}
	}
	
	/*
	 * Name: buildExpression
	 * Accepts: String to assign to operator
	 * Purpose: pushes the operator and operand into the list as part of the expression
	 * Returns: vois
	 */
	public void buildExpression(String in) throws EmptyOperandException{
		if(!getOperand().equals("")) {
			operator = in;
			list.add(this.operand);
			list.add(this.operator);
			this.operand = "";
			operator = "";
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: calculate
	 * Accepts: N/A
	 * Purpose: performs math operation in the list ArrayList, following BEDMAS, clears out the list of the used operands and operators
	 * Returns: the final value calculated from the list
	 */
	public double calculate() throws EmptyOperandException, ArithmeticException{
		if(!operand.equals("")) {
			list.add(operand);
			double temp;
			for(int j = 1; j < 3; j++) {
				for(int i = 0; i < list.size() - 1; i++) {
					if(j == 1 && list.get(i).equals("/")){
						temp = (Double.parseDouble(list.get(i-1)) / Double.parseDouble(list.get(i+1)));
						list.set(i-1, Double.toString(temp));
						list.remove(i+1);
						list.remove(i);
						
					}
					else if(j == 1 && list.get(i).equals("*")) {
						temp = (Double.parseDouble(list.get(i-1)) * Double.parseDouble(list.get(i+1)));
						list.set(i-1, Double.toString(temp));
						list.remove(i+1);
						list.remove(i);
						
					}
					else if(j == 2 && list.get(i).equals("+")) {
						temp = (Double.parseDouble(list.get(i-1)) + Double.parseDouble(list.get(i+1)));
						list.set(i-1, Double.toString(temp));
						list.remove(i+1);
						list.remove(i);
					
					}
					else if(j == 2 && list.get(i).equals("-")) {
						temp = (Double.parseDouble(list.get(i-1)) - Double.parseDouble(list.get(i+1)));
						list.set(i-1, Double.toString(temp));
						list.remove(i+1);
						list.remove(i);
					}
				}
			}
			
			operand = list.get(0);
			list.clear();
			return Double.parseDouble(operand);
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: convertHex
	 * Accepts: a number to format in Hex
	 * Purpose: converts the decimal value received as a String parameter to its hex equivalent
	 * Returns: returns the formatted number as a String
	 */
	public String convertHex(String in) throws EmptyOperandException, LongOperandException {
		if(!operand.equals("")) {
			if(operand.length() == 20) {
				throw new LongOperandException();
			}
			double d  = Double.parseDouble(in);
			int rounded = (int)Math.round(d);
			int rem;
			String out = "";
			char [] hexNum = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
			while(rounded != 0) {
				rem = rounded % 16;
				rounded /= 16;
				out = hexNum[rem] + out;	
			}
			return out;
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: convertOct
	 * Accepts: a number to format in Oct
	 * Purpose: converts the decimal value received as a String parameter to its oct equivalent
	 * Returns: returns the formatted number as a String
	 */
	public String convertOct(String in) throws EmptyOperandException, LongOperandException {
		if(!operand.equals("")) {
			if(operand.length() == 20) {
				throw new LongOperandException();
			}
			double d  = Double.parseDouble(in);
			int rounded = (int)Math.round(d);
			int rem;
			String out = "";
			char [] octNum = {'0', '1', '2', '3', '4', '5', '6', '7'};
			while(rounded != 0) {
				rem = rounded % 8;
				rounded /= 8;
				out = octNum[rem] + out;	
			}
			return out;
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	/*
	 * Name: convertBin
	 * Accepts: a number to format in binary
	 * Purpose: converts the decimal value received as a String parameter to its binary equivalent
	 * Returns: returns the formatted number as a String
	 */
	public String convertBin(String in) throws EmptyOperandException, LongOperandException {
		if(!operand.equals("")) {
			if(operand.length() == 20) {
				throw new LongOperandException();
			}
			double d  = Double.parseDouble(in);
			int rounded = (int)Math.round(d);
			int rem;
			String out = "";
			char [] binNum = {'0', '1'};
			while(rounded != 0) {
				rem = rounded % 2;
				rounded /= 2;
				out = binNum[rem] + out;	
			}
			return out;
		}
		else {
			throw new EmptyOperandException();
		}
	}
	
	
	@Override
	public String toString() {
		return "Calculator status\n\nCuurent Operand: " + this.operand + "\nNumber of operands/operators entered: " + (list.size() + 1);
	}
}
//End of class