

/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.awt.*; 
import java.awt.event.*;
import javax.swing.*; 

public class Calculator extends JFrame implements ActionListener 
{  
	// Strings for all of the 20 buttons
	public static String[][] btnStrings = {{"7","8","9","/"},
		                                   {"4","5","6","*"},
		                                   {"1","2","3","-"},
		                                   {"0",".","=","+"},
		                                   {"!","sqr(x)","e^x","ln(x)"}};
	private int numRows = btnStrings.length;
	private int numCols = btnStrings[0].length;
	// String to hold input text
	private String inputText = "";
	// Char to hold the operator (+-*/)
	private char operator = '+';
	// The two operands, e.g. a*b
	private double a =0.0, b = 0.0;
	// TextField to display results
	private JTextField displayText =null;
	public static  boolean re=false;
	public Calculator () { 
		super("Calculator for COMP2020"); 
		setSize(350,350); 
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 

		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());
		
		// Create a Panel to hold the display text and clear button
		JPanel displayPanel = new JPanel();
		displayPanel.setLayout(new FlowLayout());
		displayText = new JTextField(20);
		displayPanel.add(displayText);
		JButton clearBtn = new JButton("clear");
		clearBtn.setActionCommand("clear");
		clearBtn.addActionListener(this);
		displayPanel.add(clearBtn);
		
		// Create a panel to hold the 16 buttons
		JPanel buttonsPanel = new JPanel();
		// Set the Layout Manager for a Grid of 4x4 
		buttonsPanel.setLayout(new GridLayout(numRows, numCols));
		// Create grid of buttons 
		for(int i=0; i<numRows; i++)
			for(int j=0; j<numCols;j++){
				JButton btn = new JButton(btnStrings[i][j]);
				btn.setActionCommand(btnStrings[i][j]);
				btn.addActionListener(this);
				buttonsPanel.add(btn);
			}	
		
		contentPane.add(displayPanel, BorderLayout.NORTH);
		contentPane.add(buttonsPanel, BorderLayout.CENTER);
		
		setVisible(true); 
	} 
	
	public void actionPerformed(ActionEvent evt) {
		
		
		String actionCommand = evt.getActionCommand();
		if(actionCommand.equals("clear")){
			re=false;
			inputText="";
			displayText.setText(inputText);
		}
		for(int i=0; i<numRows; i++)
			for(int j=0; j<numCols;j++){
				if(actionCommand.equals(btnStrings[i][j]))
					// Put the call to handleCommand in a 
					//   try/catch format -- needed because
					//   handleCommand may generate a
					//     NumberFormatException
					try{
						handleCommand(btnStrings[i][j]);
					}catch(NumberFormatException e){
						displayText.setText("Oops! Incorrect format!");
					}catch (Method1Exception e ) {
						displayText.setText("You should input an integer!");
			        }catch (Method2Exception e ) {
			        	displayText.setText("You should input a positive number!");
			        }  
		   
       
    }
	}
	
	public void handleCommand(String commandString) throws Method1Exception,
                                                           Method2Exception{
		char c = commandString.charAt(0);
		System.out.println("command = "+commandString);
		switch(c){
		case '0': case '1': case '2':
		case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			// For a digit, we just add it to the end of inputText
			inputText += c;
			displayText.setText(inputText);
			break;
		case '.':
			// For the decimal, we just add it to the end of inputText
			inputText += c;
			displayText.setText(inputText);
			break;
		case '/': case '*': case '+': 
			// For an operator, we store its value
			operator = c;
			// We parse the string and create its double value
			// Note - parseDouble can throw a NumberFormatException
			a = Double.parseDouble(inputText);
			// Clear the text to get the second operand (b)
			inputText = "";
			displayText.setText(inputText);
			break;
			
		case '-':
		if(!re && inputText=="")
		{
		inputText = ""+c ;
		displayText.setText(inputText);
		re=true;
		
		break;
		}
	    	operator = c;
	    	// We parse the string and create its double value
			// Note - parseDouble can throw a NumberFormatException
			a = Double.parseDouble(inputText);
			inputText = "";
			displayText.setText(inputText);
			break;
		case '!':
			
			operator = c;
			// We parse the string and create its double value
			// Note - parseDouble can throw a NumberFormatException
			a = Double.parseDouble(inputText);
			
			
			if(a<0)//to judge the condition for a
				throw new Method2Exception();// catch a exception of method2
			
			
			if(a%1.0!=0)//to judge the condition for a
				throw new Method1Exception();// catch a exception of method1
			
			displayText.setText(inputText);
			break;
		case 's':
			operator = c;
			// We parse the string and create its double value
			// Note - parseDouble can throw a NumberFormatException
			a = Double.parseDouble(inputText);
			if(a<0)//to judge the condition for a
				throw new Method2Exception();// catch a exception of method2
			displayText.setText(inputText);
			break;
		case 'e':
			operator = c;
			// We parse the string and create its double value
			// Note - parseDouble can throw a NumberFormatException
			a = Double.parseDouble(inputText);
			displayText.setText(inputText);
			break;
		case 'l':
			operator = c;
			// We parse the string and create its double value
			a = Double.parseDouble(inputText);
			if(a<=0)
				throw new Method2Exception();// catch a exception of method2
			displayText.setText(inputText);
			break;
		
		case '=':
			computeResult();//run the method
			re=true;
			break;
		}
	}
	class Method1Exception extends Exception {}
	class Method2Exception extends Exception {}
	
	public void computeResult()  {
		double result = 0.0;
		// Parse the inputText to get the value of b
		// Note - parseDouble can throw a NumberFormatException
		b = Double.parseDouble(inputText);
		// Compute the appropriate operation and display result
		if(operator == '/') result = a/b;//caculate the operator of "/"
		else if(operator == '*') result = a*b;//caculate the operator of "*"
		else if(operator == '+') result = a+b;//caculate the operator of "+"
		else if(operator == '-') result = a-b;//caculate the operator of "-"
		else if(operator == '!')
			result= factorial((int) a);//caculate the operator of "!"
		else if(operator == 's')
			result= Math.sqrt(a);//caculate the operator of "sqr(X)"
		else if(operator == 'e')
			result= Math.exp(a);//caculate the operator of "e^x"
		else if(operator == 'l') 
			result= Math.log(a);//caculate the operator of "ln(x)"
		else {}
		displayText.setText(""+result);
		inputText = ""+result;
	}
	
	public void computeExponential(double a){
		displayText.setText(""+Math.exp(a));
	}
	
	public void computeNaturalLog(double a){
		displayText.setText(""+Math.log(a));
	}
	
	public void computeSqrt(double a){
		displayText.setText(""+Math.sqrt(a));
	}
	
	public void computeFactorial(int x){
		displayText.setText(""+factorial(x));
	}
	
	public int factorial(int x){
		if(x==0) return 1;
		else return x*factorial(x-1);
	}
	
	public static void main(String[] args){new Calculator();} 
}
