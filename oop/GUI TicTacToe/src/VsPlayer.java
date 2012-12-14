
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JOptionPane;



 	public class VsPlayer implements ActionListener {
 		private TicTacToe tictactoe;

		public void actionPerformed(ActionEvent e) {
			
			tictactoe=TicTacToe.getThis();//access TicTacToe.java
			tictactoe.setState(1);
			tictactoe.setMark("X");
			ArrayList<JButton> buttons = tictactoe.getButtons();//get the buttons from TicTacToe.java
			 //clear 9 squares
			for(int i=0; i<9; i++) {
				 buttons.get(i).setText("");
				 buttons.get(i).setEnabled(true);
				 buttons.get(i).setBackground(null);
			 }
			JOptionPane.showMessageDialog(null, "Player vs Player!   X is first to run");
			System.out.println("X is first to start!");
			    }
		public static void main(String[] args)
	    {
	            new VsPlayer();
	    }

	}
			  
    	
	
	
 	
 	  

