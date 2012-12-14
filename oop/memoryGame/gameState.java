/**
 * 
 */
package memoryGame;

import java.util.Scanner;

/**
 * @author 0830300021  
 * @author 0830300023  
 * @author 0830300012  
 */
public class gameState {
	
	private Card[][] cards = new Card[4][4];//set the size for the cards
	private int a, b, c, d;// instance variables
    
	public void initCards() {
		int i,j;
		int num[][]={{1,1,2,2},{3,3,4,4},{5,5,6,6},{7,7,8,8}};
		int state[][]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}; 
		for(i=0;i<4;i++)
			for(j=0;j<4;j++) {
				cards[i][j] = new Card();
				cards[i][j].setValue(num[i][j]);
				cards[i][j].setState(state[i][j]);
		}// to set 16 cards
	
		shuffle();
		System.out.println("Welcome to the memory game.\n"+ 
		                   "The object of this game is to match pairs of cards.\n"+
		                   "There are 16 cards (2 groups numbered 1-8) arranged in a 4x4 grid.\n"+
	                   	   "On your turn pick two cards that you think will match.\n"+
		                   "The one with the most matches wins!\n"+
		                   "Let's Start!!");
		}

	 public void shuffle() {
	 	   for(int i = 1; i<50; i++)
	 	   randomSwap();
	 	}
	 	// Swaps two randomly chosen cards 
	 	public void randomSwap() {
	 	   Card card1 = getRandomCard();
	 	   Card card2 = getRandomCard();
	 	   int valueCard1 = card1.getValue();
	 	   int stateCard1 = card1.getState();
	 	   card1.setValue(card2.getValue());
	 	   card1.setState(card2.getState());
	 	   card2.setValue(valueCard1);
	 	   card2.setState(stateCard1);
	 	}
	 	
	 	public Card getRandomCard() {
	 	   double x = Math.random();
	 	   // Generate a random choice for a card index (i,j) 
	 	   int i = (int) (4.0*x); 
	 	   x = Math.random();
	 	   int j = (int) (4.0*x);
	 	   return cards[i][j];
	 	} //In turns to show the card or not
	 	
	 	public boolean doTurn(Player CurrentPlayer) {
			
			System.out.println(CurrentPlayer.getName() + " Enter your choice of cards using four integers--\n"+
			                   "(e.g. 0 2 3 1 for 2 cards, one in (row 0 col 2) and one in (row 3 col 1) )");
			if (inputPoints(CurrentPlayer))
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if((i == a && j == b)||(i == c && j == d)||(cards[i][j].getState() == 1))
							System.out.print(cards[i][j].getValue() + " ");	
						else  if(cards[i][j].getState() == 0)
							System.out.print("* ");// the step to show cards which are founded
					}
					System.out.println();
				}
			return Check(CurrentPlayer);
			
	 	}
	 	
		public boolean Check(Player CurrentPlayer){
			System.out.println("Hit \"1\" to continue");
			Scanner keyboard = new Scanner(System.in);
			 try {
			while(keyboard.nextInt() != 1) {
				System.out.println("Hit \"1\" to continue");
				}
			
			 }
			    catch(Exception e)  // avoid the player input wrong number
			      {    
						 return Check(CurrentPlayer);
			      } 
			return MatchPair(CurrentPlayer);
			 
		}//To show hit "1" to continue every time before a turn start	
		
		public boolean inputPoints(Player CurrentPlayer) {
			Scanner keyboard = new Scanner(System.in);
			try{
			    a = keyboard.nextInt();
				b = keyboard.nextInt();
				c = keyboard.nextInt();
				d = keyboard.nextInt();
				
			    	if (a <4&& b <4 && c <4 && d <4 ){
			    		if (a!= c && b != d){
			    		return true;
			    	}
			        	else if(a==c&&b==d){
			    		System.out.println("Sorry! You have input two same numbers.");
					
			    		doTurn(CurrentPlayer);
			    		}
			    	}
				else {
					System.out.println("Sorry! Invalid input, please try again.");
			    	doTurn(CurrentPlayer);
				}
			}
			 catch(Exception e)  // avoid the player input wrong number
		      { 
				 System.out.println("Sorry, You should print integers but not letters! Please print again!");
				 doTurn(CurrentPlayer);
				 return false;
		      }
			return true;
			 }//Get the input and judge if it is in the domain
	  
	  public boolean MatchPair(Player CurrentPlayer) {
		  if((cards[c][d].getState()==1)||(cards[a][b].getState()==1)){
	        	System.out.println("The pair has been found!");
                return false;
	         }//to notice the player to avoid finding the same pair

	       	if (cards[a][b].getValue() == cards[c][d].getValue()) {
		    	cards[a][b].setState(1);
		    	cards[c][d].setState(1);
		    	System.out.println("That is a match for " + CurrentPlayer.getName());
		    	System.out.println("You have another chance to play!");
		    	 return true;
		     
	     	}//To determine whether there's a matched pair.
		   
                 else{   
			   
	    	    for (int i = 0; i < 4; i++) {
	 			   for (int j = 0; j < 4; j++) {
	 				   
		 				    if (cards[i][j].getState()==1)
		 			     		System.out.print(cards[i][j].getValue() + " ");
		 				 else
		 				 {
		 					System.out.print("* ");
		 				
	} 
	 			   }
	 			System.out.println();
	 		    }//hide the cards
	       	
	  }
	       	
	       	
	       	
	       	
	       	
	       	
	       	
	       	
	       	
	       	 
	 			   
		    	return false;
	    	}//To hide the cards which are not founded
			
	  }
	  
	
	
/**
*   public static void main(String[] args) {
*	    	gameState a=new gameState();
*	    	a.initCards();
*               a.doTurn(player0);
*               a.doTurn(player1);
*    	}
*
*/       	

	    
   	 


     

