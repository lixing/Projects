
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JOptionPane;



 	public class VsComputer implements ActionListener {
 		private TicTacToe tictactoe;

		public void actionPerformed(ActionEvent e) {
			tictactoe=TicTacToe.getThis();//access TicTacToe.java
			tictactoe.setMark("X");
			tictactoe.setState(2);
			tictactoe.setCount(0);
			ArrayList<JButton> buttons = tictactoe.getButtons();//get the buttons from TicTacToe.java
			 //clear 9 squares
			for(int i=0; i<9; i++) {
				 buttons.get(i).setText("");
				 buttons.get(i).setEnabled(true);
				 buttons.get(i).setBackground(null);
			 }
			JOptionPane.showMessageDialog(null, "Player vs Computer!  You are X, first to run");
			System.out.println("X is first to start!");
			    }
		public static void main(String[] args)
	    {
	            new VsComputer();
	    }

	}
			  
 	
    	
	
	
 	