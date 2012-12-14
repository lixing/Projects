
/**
 * @author 0830300021 
 *
 */
import javax.swing.*; 


import java.awt.*;
import java.awt.event.*;

import java.util.ArrayList;
public class TicTacToe extends JFrame implements ActionListener 
{
	static TicTacToe instans;
	private ArrayList<JButton> buttons = new ArrayList<JButton>();

     //create 9 JButton for 9 squares
	  private JButton box1 = new JButton("");
		private JButton box2 = new JButton("");
	        private JButton box3 = new JButton("");
	        private JButton box4 = new JButton("");
	        private JButton box5 = new JButton("");
	        private JButton box6 = new JButton("");
	        private JButton box7 = new JButton("");
	        private JButton box8 = new JButton("");
	        private JButton box9 = new JButton("");
	private int count=0;
	private int state=0;
    private String mark = "X";
	boolean win = false;
	Color black = new Color(0,0,0);
	Color notblack = new Color(255,255,255);
	private NewGame open;



    
    //Constructor
    public TicTacToe()
    {
    	super("TicTacToe"); 
    	setSize(350,350); 
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
		setJMenuBar(createMenuBar());
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());
		contentPane.setLayout(new GridLayout(3, 3));
	    //add the buttons to the frame
		buttons.add(box1);
	    buttons.add(box2);
	    buttons.add(box3);
	    buttons.add(box4);
	    buttons.add(box5);
	    buttons.add(box6);
	    buttons.add(box7);
	    buttons.add(box8);
	    buttons.add(box9);
	           //add Button ActionListeners for 9 buttons
                for(int i=0; i<9; i++) {
                  contentPane.add(buttons.get(i));
                  buttons.get(i).addActionListener(this);
                }
      
        setVisible(true); 
        instans=this;
    }
     
//menu items and add them to the menu bar
public JMenuBar createMenuBar() {
        JMenuBar menuBar;
        JMenu menu;
        JMenuItem menuItem;

        menuBar = new JMenuBar();
        menu = new JMenu("Menu");
        
        menuItem = new JMenuItem("Player vs Player");
        menuItem.addActionListener(new VsPlayer());
        menu.add(menuItem);
        
        menuItem = new JMenuItem("Player vs AI");
        menuItem.addActionListener(new VsComputer());
        menu.add(menuItem);
        
        menuItem = new JMenuItem("New Game");
        open=new NewGame();
        menuItem.addActionListener(open);
        menu.add(menuItem);
 
        menuItem = new JMenuItem("Open");
        menuItem.addActionListener(new OpenGame());
       
        menu.add(menuItem);
    
        menuItem = new JMenuItem("Save");
        menuItem.addActionListener(new SaveGame());
        menu.add(menuItem);
       
        menuBar.add(menu);
        menuItem = new JMenuItem("Exit");
        menuItem.addActionListener(new Exit());
        
        menu.add(menuItem);

        return menuBar;
    }
       
    public void actionPerformed(ActionEvent e)
    {
    	
    	if(state==1 || state==2){//if the player choose a menu, the buttons can work.
    	do
    		{
       //show the position of the squares which have been chosen
        for(int i = 0; i<9; i++) {
           if(e.getSource()==buttons.get(i)) {
               buttons.get(i).setText(getMark());
               buttons.get(i).setEnabled(false);
               count+=1;
           }
        }
    	
    	if(state==1){//state=1 is for "player vs player"
    		Player();
    	    WinStatement();
    	       
    	    //To judge who is the winner,or , if the game is tie.
    	   	 	 if (count==9 && win==false)
    	    	    {

    	    	        int answer=JOptionPane.showConfirmDialog(null, "It's a tie! Restart Play?", "Want to end?",JOptionPane.YES_NO_OPTION);
    	    			if(answer==JOptionPane.YES_OPTION){
    	    				win=false;
    	    				open.Restart();
    	    			}
    	    			else System.exit(0);
    	    	    }
    	    	    if (win==true)
    	    	    {
    	    	    	if(getMark().equals("X")){
    	    	        int answer=JOptionPane.showConfirmDialog(null,   "O WINS! Restart Play?", null,JOptionPane.YES_NO_OPTION);
    	    			if(answer==JOptionPane.YES_OPTION){
    	    				win=false;
    	    				open.Restart();
    	    			}
    	    			else System.exit(0);
    	    	    }
    	    	    	else{
    	    	    		 int answer=JOptionPane.showConfirmDialog(null,  "X WINS! Restart Play?", null,JOptionPane.YES_NO_OPTION);
    	    	    			if(answer==JOptionPane.YES_OPTION){
    	    	    				win=false;
    	    	    				open.Restart();
    	    	    			}
    	    	    			else System.exit(0);
    	    	    	}
    	    	    }
    	    	    
    	}
    	if(state==2){//state=2 is for "player vs Computer"
    		Computer();
     		WinStatement();
     		
     		//To judge who is the winner,or , if the game is tie.
      	 	 if (count==9 && win==false)
     	    {

     	        int answer=JOptionPane.showConfirmDialog(null, "It's a tie! Restart Play?", "Want to end?",JOptionPane.YES_NO_OPTION);
     			if(answer==JOptionPane.YES_OPTION){
     				win=false;
     				open.Restart();//restart the game
     			}
     			else System.exit(0);
     	    }
     	    if (win==true)
     	    {
     	      
     	     if(count%2==1 && count!=9) {
     	    	 int answer=JOptionPane.showConfirmDialog(null,  "O WINS! Restart Play?", null,JOptionPane.YES_NO_OPTION);
   			if(answer==JOptionPane.YES_OPTION){
 				win=false;
 				open.Restart();//restart the game
 			}
 			else System.exit(0);
    	}
     	     else {
     	    	 int answer=JOptionPane.showConfirmDialog(null,  "X WINS! Restart Play?", null,JOptionPane.YES_NO_OPTION);
      			if(answer==JOptionPane.YES_OPTION){
      				win=false;
      				open.Restart();
     	     }
      			else System.exit(0);
     	    
     	    }
     	    }
    	} 
    		}while(win=false);
    	}
    
    	else JOptionPane.showMessageDialog(null, "Choose one type from the menu!");
    
    }
    
    //method to judge who wins
   public void WinStatement(){
	   if (box1.getText().equals(box2.getText()) && box2.getText().equals(box3.getText()) && box1.getText().equals("")==false)
	    {
	        box1.setBackground(notblack);
	        box2.setBackground(notblack);
	        box3.setBackground(notblack);
	        win=true;        
	    }
	    else if (box4.getText().equals(box5.getText()) && box5.getText().equals(box6.getText())&& box4.getText().equals("")==false)
	    {
	        box4.setBackground(notblack);
	        box5.setBackground(notblack);
	        box6.setBackground(notblack);    
	        win=true;    
	    }
	    else if (box7.getText().equals(box8.getText()) && box8.getText().equals(box9.getText())&& box7.getText().equals("")==false)
	    {
	        box7.setBackground(notblack);
	        box8.setBackground(notblack);
	        box9.setBackground(notblack);
	        win=true;        
	    }
	    else if (box1.getText().equals(box4.getText()) && box4.getText().equals(box7.getText())&& box1.getText().equals("")==false)
	    {
	        box1.setBackground(notblack);
	        box4.setBackground(notblack);
	        box7.setBackground(notblack);
	        win=true;        
	    }
	    else if (box2.getText().equals(box5.getText()) && box5.getText().equals(box8.getText())&& box2.getText().equals("")==false)
	    {
	        box2.setBackground(notblack);
	        box5.setBackground(notblack);
	        box8.setBackground(notblack);
	        win=true;        
	    }
	    else if (box3.getText().equals(box6.getText()) && box6.getText().equals(box9.getText())&& box3.getText().equals("")==false)
	    {
	        box3.setBackground(notblack);
	        box6.setBackground(notblack);
	        box9.setBackground(notblack);        
	        win=true;    
	    }
	    else if (box1.getText().equals(box5.getText()) && box5.getText().equals(box9.getText())&& box1.getText().equals("")==false)
	    {
	        box1.setBackground(notblack);
	        box5.setBackground(notblack);
	        box9.setBackground(notblack);        
	        win=true;
	    }
	    else if (box3.getText().equals(box5.getText()) && box5.getText().equals(box7.getText())&& box3.getText().equals("")==false)
	    {
	        box3.setBackground(notblack);
	        box5.setBackground(notblack);
	        box7.setBackground(notblack);        
	        win=true;
	    }
     
    	   }
   
   
   public void Player(){
	   if (getMark().equals("X"))
  	    {
  	        setMark("O");
  	        System.out.println("Time to O!");
  	    }
  	    else
  	    {
  	    	setMark("X");
  	        System.out.println("Time to X!");
  	    }
   }
   
    public void Computer(){
    	boolean loop=false;
    	if(getCount()==1 || getCount() == 3 || getCount() ==5 || getCount() == 7){//Player is run firstly, Computer is second.
    		do
    		{
    		double x= Math.random();//random a number
    		int i = (int) (9.0*x); //random a number in the range of 9
    		if(!buttons.get(i).getText().equals("X") && !buttons.get(i).getText().equals("O")){// to find the empty button
    			buttons.get(i).setText("O");
    			buttons.get(i).setEnabled(false);
    			count+=1;
    			loop=true;
    		}
    		else loop=false;
    		
    	}while(loop==false);
    	}
		
    	
    		
    }
   
//the get and set method. so that the other classes can use the values
    public ArrayList<JButton> getButtons() {return buttons;}
    
    public  static TicTacToe getThis()
    {
		return instans;
    }
    public int getState() {
		return state;
	}
	public void setState(int state) {
		this.state = state;
	}
	public int getCount() {
		return count;
	}
	public void setCount(int count) {
		this.count = count;
	}
	public void setMark(String mark) {
		this.mark = mark;
	}
	public String getMark() {
		return mark;
	}
	
	//Exit inner class
	private class Exit implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			//pops up a dialog box to ask whether the player wants to exit the game for sure
			int answer=JOptionPane.showConfirmDialog(null, "End program?",null ,JOptionPane.YES_NO_OPTION);
			if(answer==JOptionPane.YES_OPTION)
    		ExitGame();
    	}
		
	public void ExitGame(){
			System.exit(0);
		}
	}
	
	//test
public static void main(String[] args)
    {
            new TicTacToe();
    }

}

