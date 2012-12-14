/**
 * 
 */
package memoryGame;

/**
 * @author 0830300021  
 * @author 0830300023  
 * @author 0830300012  
 */
public class Player {
	private String name = "UnNamed";
	private int score = 0;
	
	public Player(){}
	
	public Player(String name) {
		this.name = name;
	}
	
	public Player(int score){
		this.score = score;
	}

    /*************************************
     *  Mutator and Accessor methods
     *************************************/
	public void setName(String name) {
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public void setScore(int score){
		this.score = score;
	}
	
	public int getScore(){
		return score;
	}
}

/**
*   public static void main(String[] args) {
*	    	Player a=new Player();
*	    	a.setName("Allen");
*               a.setName("Michael");
*               a.setScore(0);
*               a.setScore(0);
*        System.out.println(" "+player0.getName() + ":" + score0
*	        			+ " "+ player1.getName() + ":" + score1);
*    	}
*
*/