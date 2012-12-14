import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JOptionPane;


//SaveGame class
 	public class SaveGame implements ActionListener {
 		private TicTacToe tictactoe;
 		private ArrayList<String> save = new ArrayList<String>();
 		public void actionPerformed(ActionEvent e) {
				try{
					//pops up a dialog box to ask the player to enter the file name
					String filename = JOptionPane.showInputDialog(null,
					  "Create File Name:(like tictactoe.txt)",
					  "Save text File",
					  JOptionPane.QUESTION_MESSAGE);
    		performSave(filename);//execute "Save" operation
		}catch (Exception e1){
			JOptionPane.showMessageDialog(null, "You did not write the name!!");
    	}
 		}
	
	//method to execute "Save" operation
 	  public void performSave(String filename){
 		 
 		 tictactoe=TicTacToe.getThis();//access TicTacToe.java
 		ArrayList<JButton> buttons = tictactoe.getButtons();//get the buttons from TicTacToe.java
 			try{
 				BufferedWriter outputStream = 
 			       new BufferedWriter(new OutputStreamWriter(
 			    		                 new FileOutputStream(filename)));
 				//get the state of game type, state=1 is for "player vs player", state=2 is for "player vs Computer AI"
 				int state= tictactoe.getState();
 				//variable to design who is next turn player
 				int order;
 				if(tictactoe.getCount()%2==0)
 					order=0; //if order = 0, next turn is for X
 				else order=1;//if order = 1, next turn is for O 
 				
 				 //write the state of squares into the text file
 				for(int i=0; i<9; i++) {
 					save.add(i, buttons.get(i).getText());

 					 if(!save.get(i).equals("X") && !save.get(i).equals("O")){
 					
 						save.set(i, "A");//In the text file, we write "A" to represent the empty squares
 					 }
 					 outputStream.write(save.get(i)+"\r\n");
 					 }
 					 
 				outputStream.write(state+"\r\n");
 				outputStream.write(order+"\r\n");
 				outputStream.close();
 				JOptionPane.showMessageDialog(null,  "File saved correctly");
 			}
 			catch(IOException e){
 				JOptionPane.showMessageDialog(null,  "Write IO problem!!");
 			}
 		}
 	  
 	  //text main
 	 public static void main(String[] args)
	    {
	            new SaveGame();
	    }

	}
 	  

