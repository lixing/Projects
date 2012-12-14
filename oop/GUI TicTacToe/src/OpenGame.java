import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JOptionPane;


//OpenGame class
	public class OpenGame implements ActionListener {
		private TicTacToe tictactoe;
		private ArrayList<String> open = new ArrayList<String>();
		public void actionPerformed(ActionEvent e) {
			try {
				//pops up a dialog box to ask the player to enter the file name
				String filename = JOptionPane.showInputDialog(null,
			
					  "Enter File Name:",
					  "Open text File",
					  JOptionPane.QUESTION_MESSAGE);
				read(filename);//execute "read" operation
			}catch (Exception e1){
				JOptionPane.showMessageDialog(null, "Cannot find the file!!");
				}
    		
    	}
		//method to execute "read" operation
		public void read(String filename) {
			tictactoe=TicTacToe.getThis();//access TicTacToe.java
			
			tictactoe.setCount(0); 
			ArrayList<JButton> buttons = tictactoe.getButtons();//get the buttons from TicTacToe.java
			
			try {
			
				BufferedReader inputStream =
				    new BufferedReader(
				        new InputStreamReader(new FileInputStream(filename)));
				 //first, we clear all the squares
				for(int i=0; i<9; i++) {
					 buttons.get(i).setText("");
					 buttons.get(i).setEnabled(true);
					 buttons.get(i).setBackground(null);
					//read data from the text file
					 open.add(inputStream.readLine());
				     //if squares are not empty, load them from the text file 
				     if(!open.get(i).equals("A")){
				    	 buttons.get(i).setText(open.get(i));
				    	 buttons.get(i).setEnabled(false);
				     }
				   //For those squares which are empty, still set them empty.
				     else buttons.get(i).setText("");
				 }
				//read the text file to find out which game type is being played
				String state = inputStream.readLine();
				int a=Integer.parseInt(state);
				tictactoe.setState(a);
				//read the text file to find out who is the next turn to play
				String order = inputStream.readLine();
				int b=Integer.parseInt(order);
			    inputStream.close();
				JOptionPane.showMessageDialog(null, "File: "+ filename+ " was read correctly");
				//if state of game type =1, game type is "Game of Player vs Player"
				if(tictactoe.getState()==1){
					JOptionPane.showMessageDialog(null, "Game of Player vs Player!!");
					//if order=0=b,next turn is for X
					if(b==0){
						JOptionPane.showMessageDialog(null, "Time to X!!");
					    tictactoe.setMark("X");
					}
					//else,next turn is for O
					else {
						JOptionPane.showMessageDialog(null, "Time to O!!");
				        tictactoe.setMark("O");
					}
				}
				//if state of game type =2, game type is "Game of Player vs Computer"
				if(tictactoe.getState()==2){
					JOptionPane.showMessageDialog(null, "Game of Player vs Computer!!");
					if(b==0){
						JOptionPane.showMessageDialog(null, "Time to X!!");
					    tictactoe.setMark("X");
					}
					else {
						JOptionPane.showMessageDialog(null, "Time to O!!");
				        tictactoe.setMark("O");
					}
				}
				//if state of game type =0, game is empty
				else if(tictactoe.getState()==0)
					JOptionPane.showMessageDialog(null, "The game is empty!!");
			
			}
			catch(IOException e){
				JOptionPane.showMessageDialog(null, "Read IO problem!!");
			}
		}
	//text main
		public static void main(String[] args)
	    {
	            new OpenGame();
	    }

	}
  
