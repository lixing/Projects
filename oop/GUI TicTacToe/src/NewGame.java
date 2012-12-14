
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JOptionPane;


	
//NewGame class
	public class NewGame implements ActionListener {
		private  TicTacToe tictactoe;
		public static  boolean loop=false;
		public void actionPerformed(ActionEvent e) {
			//pop up a dialog box to ask if the player wants to start a new game
			int answer=JOptionPane.showConfirmDialog(null, "Start a new game?", null ,JOptionPane.YES_NO_OPTION);
			if(answer==JOptionPane.YES_OPTION)
			Restart();
		
    	}
		//Restart method
	public void Restart(){
		
		tictactoe=TicTacToe.getThis();
		tictactoe.setMark("X");
		tictactoe.setCount(0);
		//this loop tells the player that he or she must choose a game type here
		do{
		Object[] possibleValues = { "Player vs Player", "Player vs Computer"};
		Object selectedValue = JOptionPane.showInputDialog(null, 
		"Choose one", "Choose type to start",
		JOptionPane.INFORMATION_MESSAGE, null,
		possibleValues, possibleValues[0]);
		
		try{
			
		if(selectedValue.equals("Player vs Player")){
		tictactoe.setState(1); //state=1 is for "Player vs Player"
		JOptionPane.showMessageDialog(null, "Player vs Player!   X is first to run");
		System.out.println("X is first to start!");
		}
		if(selectedValue.equals("Player vs Computer")){
		tictactoe.setState(2);//state=2 is for "Player vs Computer"
		JOptionPane.showMessageDialog(null, "Player vs Computer!  You are X, first to run");
		}
		loop=true;
			
		}catch(Exception e){
			JOptionPane.showMessageDialog(null, "Please choose a type!!");
			loop=false;
		}
		}while(loop==false);
		
	
		ArrayList<JButton> buttons = tictactoe.getButtons();//get the buttons from TicTacToe.java
		 //clear 9 squares
		for(int i=0; i<9; i++) {
			 buttons.get(i).setText("");
			 buttons.get(i).setEnabled(true);
			 buttons.get(i).setBackground(null);
    }
	}
	public static void main(String[] args)
    {
            new NewGame();
    }

}