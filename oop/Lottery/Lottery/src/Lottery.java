
/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.util.*;

public class Lottery<T> {
     private ArrayList<T> items = new ArrayList<T>();
     
     
     public void add(T item){
    	 items.add(item);
     }
     public boolean isEmpty(){
    	 return items.size()==0;
     }
     public T pickItem() {
    	 int index = (int) ((double)items.size()*Math.random());
    	 return items.get(index);
     }
     
     //The generic method 
     public <Object> void isInBox(Object object){ 
    	if(object.equals(100)||object.equals(500)||object.equals(1000)||object.equals(2000)||object.equals(5000)){
    		System.out.println("OK, that is one of our prizes. Good luck!");
    	}
    	else
    		System.out.println("Sorry - that is not one of our prizes, but you can play anyway.");
     }//to judge if "object" is an item in the box of prizes. 

     
     public static void main(String[] args){
         Scanner keyboard1 = new Scanner(System.in);
    	 Lottery<Integer> prizebox = new Lottery<Integer>();
    	 prizebox.add(new Integer(100)); 
    	 prizebox.add(new Integer(500)); 
    	 prizebox.add(new Integer(1000)); 
    	 prizebox.add(new Integer(2000)); 
    	 prizebox.add(new Integer(5000)); //add five prizes for the lottery
    	 boolean done = false;
    	 System.out.println("Welcome to the COMP2020 Lottery!!");
    	 System.out.println("What prize are you interested in?");
    	 Scanner keyboard2 = new Scanner(System.in);
    	 try{
         Object object = keyboard2.nextInt( );//set object equals to the user's input for the interest money
    	 prizebox.isInBox(object);//call the generic method
    	 }catch(Exception e) {
             System.out.println("Ooops! It is not an integer, but you can play anyway.");
    	 }//exception handling if the input is not an integer
    	 while(!done){
    		 System.out.println("On this drawing, you get a "+prizebox.pickItem()+"\n");
    		 System.out.print("Play the lottery again? (type yes or no)");
             String answer = keyboard1.nextLine( );
             if (!(answer.equalsIgnoreCase("yes")))
                   done = true;//go out to end the game.
    	 }
    	 System.out.print("Thanks for playing!!");
     }
}
