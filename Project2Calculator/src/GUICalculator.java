/**
* Program Name: GUICalculator.java
* Purpose: Generates the GUI of the calculator, and calls the main method
* @author John Deslippe 0754326
* Date: Aug 6, 2022
*/
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class GUICalculator extends JFrame{
	
	//Public declarations of all GUI Elements
	public Container thisContentPane;	
	private boolean flag = false;
	private JTextField display = new JTextField();
	
	private JMenuBar menu = new JMenuBar();
	private JMenu file, convert, help;
	private JMenuItem exitItem, howItem, aboutItem;
	private JRadioButtonMenuItem hexItem, decItem, octItem, binItem;
	private JButton clearB, backB, percentB, signB, squareB, rootB, blankB, otherBlankB, divB, addB, subB, multiB, equalsB, oneB, zeroB, twoB, threeB, fourB,
					fiveB, sixB, sevenB, eightB, nineB, decB;
	
	Font font = new Font("SansSerif", Font.PLAIN, 22);
	
	private Calculator calc = new Calculator();
	
	//Constructor
	//Defines physical layout of calculator application
	public GUICalculator() {
		super("Calculator");
		
		JPanel buttons = new JPanel();
		
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(300, 365);
		this.setLocationRelativeTo(null);
		this.setLayout(new FlowLayout());
		
		display.setPreferredSize(new Dimension(270, 30));
		display.setHorizontalAlignment(JTextField.RIGHT);
		display.setText("0.0");
		display.setFont(font);
		display.setEditable(false);
		
		this.setJMenuBar(menu);
		file = new JMenu("File");
		convert = new JMenu("Convert");
		help = new JMenu("Help");
		
		//adding the drop-down options to the menubar
		menu.add(file);
		menu.add(convert);
		menu.add(help);
		
		hexItem = new JRadioButtonMenuItem("Hex");
		decItem = new JRadioButtonMenuItem("Dec");
		octItem = new JRadioButtonMenuItem("Oct");
		binItem = new JRadioButtonMenuItem("Bin");
		ButtonGroup group = new ButtonGroup();
		group.add(hexItem);
		convert.add(hexItem);
		group.add(decItem);
		convert.add(decItem);
		group.add(octItem);
		convert.add(octItem);
		group.add(binItem);
		convert.add(binItem);
		
		
		exitItem = file.add("Exit");
		howItem = help.add("How To Use");
		aboutItem = help.add("About");
		
		//declaring and adding all buttons to the container
		clearB = new JButton("C");
		clearB.setFont(font);
		squareB = new JButton("X\u00B2");
		squareB.setFont(font);
		backB = new JButton("\u232B");
		backB.setFont(font);
		percentB = new JButton("%");
		percentB.setFont(font);
		signB = new JButton("\u00B1");
		signB.setFont(font);
		rootB = new JButton("\u221A");
		rootB.setFont(font);
		blankB = new JButton("");
		divB = new JButton("/");
		divB.setFont(font);
		sevenB = new JButton("7");
		sevenB.setFont(font);
		eightB = new JButton("8");
		eightB.setFont(font);
		nineB = new JButton("9");
		nineB.setFont(font);
		multiB = new JButton("X");
		multiB.setFont(font);
		fourB = new JButton("4");
		fourB.setFont(font);
		fiveB = new JButton("5");
		fiveB.setFont(font);
		sixB = new JButton("6");
		sixB.setFont(font);
		subB = new JButton("-");
		subB.setFont(font);
		oneB = new JButton("1");
		oneB.setFont(font);
		twoB = new JButton("2");
		twoB.setFont(font);
		threeB = new JButton("3");
		threeB.setFont(font);
		addB = new JButton("+");
		addB.setFont(font);
		otherBlankB = new JButton("");
		zeroB = new JButton("0");
		zeroB.setFont(font);
		decB = new JButton(".");
		decB.setFont(font);
		equalsB = new JButton("=");
		equalsB.setFont(font);
		
		buttons.setLayout(new GridLayout(6, 4, 5, 5));
		
		buttons.add(clearB);
		buttons.add(backB);
		buttons.add(percentB);
		buttons.add(signB);
		buttons.add(squareB);
		buttons.add(rootB);
		buttons.add(blankB);
		buttons.add(divB);
		buttons.add(sevenB);
		buttons.add(eightB);
		buttons.add(nineB);
		buttons.add(multiB);
		buttons.add(fourB);
		buttons.add(fiveB);
		buttons.add(sixB);
		buttons.add(subB);
		buttons.add(oneB);
		buttons.add(twoB);
		buttons.add(threeB);
		buttons.add(addB);
		buttons.add(otherBlankB);
		buttons.add(zeroB);
		buttons.add(decB);
		buttons.add(equalsB);
		HearingAid listenUp = new HearingAid(); //declares an action listener to define button behaviour
		
		//add action listeners to all clickable elements
		clearB.addActionListener(listenUp);
		backB.addActionListener(listenUp);
		percentB.addActionListener(listenUp);
		signB.addActionListener(listenUp);
		squareB.addActionListener(listenUp);
		rootB.addActionListener(listenUp);
		divB.addActionListener(listenUp);
		sevenB.addActionListener(listenUp);
		eightB.addActionListener(listenUp);
		nineB.addActionListener(listenUp);
		multiB.addActionListener(listenUp);
		fourB.addActionListener(listenUp);
		fiveB.addActionListener(listenUp);
		sixB.addActionListener(listenUp);
		subB.addActionListener(listenUp);
		oneB.addActionListener(listenUp);
		twoB.addActionListener(listenUp);
		threeB.addActionListener(listenUp);
		addB.addActionListener(listenUp);
		zeroB.addActionListener(listenUp);
		decB.addActionListener(listenUp);
		equalsB.addActionListener(listenUp);
		exitItem.addActionListener(listenUp);
		hexItem.addActionListener(listenUp);
		decItem.addActionListener(listenUp);
		octItem.addActionListener(listenUp);
		binItem.addActionListener(listenUp);
		aboutItem.addActionListener(listenUp);
		howItem.addActionListener(listenUp);
		
		this.add(display);
		this.add(buttons);
		this.setVisible(true);
	}
	
	private class HearingAid implements ActionListener{
		/*
		 * Name: actionPerformed
		 * Accepts: ActionEvent
		 * Purpose: Defines behaviour of each button and menu item
		 * Returns: void
		 */
		public void actionPerformed(ActionEvent ev) {
			thisContentPane = getContentPane();
			
			if(ev.getActionCommand().equals("0")) {
				try {
					calc.buildOperand("0");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("1")) {
				try {
					calc.buildOperand("1");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("2")) {
				try {
					calc.buildOperand("2");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("3")) {
				try {
					calc.buildOperand("3");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("4")) {
				try {
					calc.buildOperand("4");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("5")) {
				try {
					calc.buildOperand("5");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("6")) {
				try {
					calc.buildOperand("6");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("7")) {
				try {
					calc.buildOperand("7");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("8")) {
				try {
					calc.buildOperand("8");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("9")) {
				try {
					calc.buildOperand("9");
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals(".")) {
				try {
					if(!calc.getDecimalPressed() && calc.getOperand().indexOf(".") == -1) {
						calc.buildOperand(".");
						calc.setDecimalPressed(true);
						display.setText(calc.getOperand());
					}
				} catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
				
			}
			else if(ev.getActionCommand().equals("C")) {
				calc.clear();
				display.setText("0.0");
			}
			else if(ev.getActionCommand().equals("\u232B")) { 
				try {
					calc.setOperand(calc.backspace(calc.getOperand()));
					display.setText(calc.getOperand());
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
				
			}
			else if(ev.getActionCommand().equals("%")) { 
				try {
					calc.setOperand(calc.findPercentage(calc.getOperand()));
					display.setText(calc.getOperand());
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
			}
			else if(ev.getActionCommand().equals("\u00B1")) { //sign button
				try {
					calc.setOperand(calc.togglePlusMinus(flag));
					if(flag) {
						flag = false;
					}
					else {
						flag = true;
					}
					display.setText(calc.getOperand());
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}	
			}
			else if(ev.getActionCommand().equals("X\u00B2")) { 
				try {
					calc.setOperand(calc.findSquared(calc.getOperand()));
					display.setText(calc.getOperand());
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
			}
			else if(ev.getActionCommand().equals("\u221A")) { 
				try {
					calc.setOperand(calc.findSquareRoot(calc.getOperand()));
					display.setText(calc.getOperand());
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
			}
			else if(ev.getActionCommand().equals("/")) { 
				try {
					calc.buildExpression("/");
					display.setText("/");
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
			}
			else if(ev.getActionCommand().equals("X")) { 
				try {
					calc.buildExpression("*");
					display.setText("X");
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
			}
			else if(ev.getActionCommand().equals("-")) { 
				try {
					calc.buildExpression("-");
					display.setText("-");
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
			}
			else if(ev.getActionCommand().equals("+")) { 
				try {
					calc.buildExpression("+");
					display.setText("+");
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
			}
			else if(ev.getActionCommand().equals("=")) { 
				try {
					display.setText(Double.toString(calc.calculate()));
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
			}
			else if(ev.getActionCommand().equals("Exit")) { 
				System.exit(0);
			}
			else if(ev.getActionCommand().equals("Hex")) { 
				try {
					display.setText(calc.convertHex(calc.getOperand()));
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
				catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
			}
			else if(ev.getActionCommand().equals("Dec")) {
				display.setText(calc.getOperand());
			}
			else if(ev.getActionCommand().equals("Oct")) { 
				try {
					display.setText(calc.convertOct(calc.getOperand()));
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
				catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
			}
			else if(ev.getActionCommand().equals("Bin")) { 
				try {
					display.setText(calc.convertBin(calc.getOperand()));
				} catch (EmptyOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: No operand exists to perform this action");
				}
				catch (LongOperandException e) {
					JOptionPane.showMessageDialog(thisContentPane, "Error: Too large of an operand");
				}
			}
			else if(ev.getActionCommand().equals("About")) { 
				JOptionPane.showMessageDialog(thisContentPane, calc.toString());
			}
			else if(ev.getActionCommand().equals("How To Use")) { 
				JOptionPane.showMessageDialog(thisContentPane, "Enter any floating point number, followed by an operator and a second number.\n"
						+ "This can be repeated as needed.\n Various other functions exist as seen on the buttons avaliable");
			}
		}
	}
	
	public static void main(String[] args) {
		new GUICalculator();
	}
}
//End of class