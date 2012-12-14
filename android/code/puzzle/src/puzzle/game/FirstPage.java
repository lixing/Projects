package puzzle.game;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

public class FirstPage extends Activity {
    

	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.firstpage);


        ImageButton button6 = (ImageButton) findViewById(R.id.button6);
     	button6.setOnClickListener(new Button.OnClickListener() {
     		public void onClick(View v)
     		{ 
     			Intent intent = new Intent();
     			 
     			intent.setClass(FirstPage.this,IntroPage1.class);
     			
     			startActivity(intent);	
     			
     			
     			
     		}
     	});
     	ImageButton button8 = (ImageButton) findViewById(R.id.button8);
         button8.setOnClickListener(new Button.OnClickListener() {
         		public void onClick(View v)
         		{
         			Intent intent = new Intent();
        			
        			intent.setClass(FirstPage.this,IntroPage2.class);
        			
        			startActivity(intent);	
        			
         			
         	}});
       
         ImageButton button9 = (ImageButton) findViewById(R.id.button9);
         button9.setOnClickListener(new Button.OnClickListener() {
         	 public void onClick(View v)
         		{
         			Intent intent = new Intent();
       			
       			intent.setClass(FirstPage.this,UserName.class);
       			
       			startActivity(intent);	
       		
         		}});


         
         

 }     
    
     
}