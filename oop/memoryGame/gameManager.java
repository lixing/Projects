/**
 * 
 */
package memoryGame;
/**
 * @author 0830300021
 * @author 0830300023
 * @author 0830300012
 */
import java.util.Scanner;// Needed for getting input from keyboard

public class gameManager {
    
    private gameState game = new gameState();
	private Player player0 = new Player("Mike");
	private Player player1 = new Player("Bill");
	private int score0 = 0;
	private int score1 = 0;// instance variables
	
        /***************************************
	 *  Game Play Methods
	 ***************************************/
	   public void playGame(){
	        game.initCards();
	        initPlayer(0);
			initPlayer(1);
			
			start();
			getPair();
			EndOfGame(score0, score1);

	    }//set the orders for each function
	  

 
	public gameManager() {
	}
	
	public gameManager(String name0, String name1){
		player0 = new Player(name0);
		player1 = new Player(name1);
	}


        /*************************************
         *  Mutator and Accessor methods
         *************************************/
	public void setPlayer(int num, Player p){
		if(num == 0) player0 = p;
		else player1 = p;
	}
	public Player getPlayer(int num) {
		if(num == 0) return player0;
		else return player1;
	}
 
    public void initPlayer(int num) {
		
		System.out.println("Player "+num+", type in your name:");
		Scanner scanner = new Scanner(System.in);
		String name = scanner.nextLine( );
		if(num==0) player0.setName(name);
		else player1.setName(name);
	}//set the names for each player
	
	public void start() {
		Scanner keyboard = new Scanner(System.in);
		System.out.println("Hit \"enter\" to continue");
		    if(keyboard.hasNextLine())
		    System.out.println("* * * *\n* * * *\n* * * *\n* * * *\n");
			System.out.println(player0.getName()+ ": 0  "+ player1.getName()+": 0");
	}// Start the game and use "*" to represent the cards

        /***************************************
	 *  Other Game Manager Method
	 ***************************************/

     public boolean getPair() {
    	
    	if (game.doTurn(player0)) {
    		changeScore0(score0);
	    	return true;
    	}
    	else
    	{
    		   System.out.println("+++"+player0.getName() + ":" + score0
	        			+ " "+ player1.getName() + ":" + score1);
    	}
    		
    		
    	 
       	if (game.doTurn(player1)) {
       		changeScore1(score1);
       		return true;
	   	}
    	else
    	{
    		   System.out.println("---"+player0.getName() + ":" + score0
	        			+ " "+ player1.getName() + ":" + score1);
    	}
    		
       		
       	
	   	 
	   		
		return false;
    	 
    }// to set the score for players
    
    public void EndOfGame(int score0, int score1) {
    	this.score0 = score0;  
    	this.score1 = score1; 
    	int pair=0;
    	while(pair != 8){
	           if (getPair()){
	             	pair+=1;
	             	}
	           
	          }
    				if (pair == 8){
    					
    			    if (score0 > score1)
    			    	
    		         	System.out.println("Congratalations " + player0 + " you win!!!");
    	            else if (score0 < score1)
    		        	System.out.println("Congratalations " + player1 + " you win!!!");
    		        else 
    		         	System.out.println("Draw game!");
    			    
    			}
    			
    			}//Method to judge when the game is end and who is the winner    	
    
    public void changeScore0(int score0){
    
    	score0 +=1;
    	this.score0 = score0; 
    	System.out.println(player0.getName() + ":" + score0
    			+ " "+ player1.getName() + ":" + score1);
    	
    	}
    
    public void changeScore1(int score1){
    	
    	score1 +=1;
    	this.score1 = score1; 
    	System.out.println(player0.getName() + ":" + score0
    			+ " "+ player1.getName() + ":" + score1);
    	
    	}//Methods to add up the score to the player
   


}

/**
*   public static void main(String[] args) {
*	    	gameManager a=new gameManager();
*	    	a.playGame();
*               
*    	}
*
*/

	

		

    
        


