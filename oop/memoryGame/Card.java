/**
 * 
 */
package memoryGame;

/**
 * @author 0830300021
 * @author 0830300023
 * @author 0830300012
 */
public class Card {
	private int value = 0; 
	private int state = 0;
	
	public Card() {}
	
	public Card(int m) {
		value = m;
	}
	
	public Card(int m, int n) {
		value = m;
		state = n;
	}
	
	public void setValue(int m) {
		value = m;
	}
	
	public int getValue() {
		return value;
	}
	
	public void setState(int n) {
		state = n;
	}
	
	public int getState() {
		return state;
	}
}
	
/**
*   public static void main(String[] args) {
*	    	Card a=new Card();
*	    	a.setvalue();
*               a.setState();
*    	}
*
*/

