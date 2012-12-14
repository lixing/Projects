/**
 * @author Lian Li Xing/ Yves
 * @Student ID 0830300023
 */

import java.util.Scanner;

public class TwentyFour{
    Scanner keyboard=new Scanner(System.in);
    
    public static void main(String[] args){
    	TwentyFour TwentyFour= new TwentyFour();
        TwentyFour.main();
    }
    
    void main(){
        System.out.println( "Welcome to the game of TwentyFour. You will choose one of the sets of numbers below.\n" +
                            "You then need to use each of the four numbers in this set exactly once, combining them \n" +
                            "somehow with the basic mathematical operators (+,-,*,/) to yield the value twenty-four. \n" +
                            "Possible sets of numbers are:\n"+
                            "  8         5         7         5          9         8   \n"+
                            "5   1     1   1     8   8     9   4      2   2     6   4 \n"+
                            "  8         6         2         3          5         2   \n");
        String operator="";
        int number=0;
        int result=0;
        System.out.print("Please enter the first number:");
        result=keyboard.nextInt();
        for(int n =0;n<3;n++){
            System.out.print("Enter the operator to be used(+,-,*,or/):");
            operator=keyboard.next();
            System.out.print("Enter the next number:");
            number=keyboard.nextInt();
            if(operator.equals("+")){
                result+=number;
            }
            else if(operator.equals("-")){
                result-=number;
            }
            else if(operator.equals("*")){
                result*=number;
            }
            else if(operator.equals("/")){
                result/=number;
            }
            System.out.println("That gives:"+result +
                               " \n");
        }
        if(result==24){
             System.out.println("Well done, genius!\n");
        }
        else{
             System.out.println("Sorry, you are wrong.\n");
        }
    }
}
