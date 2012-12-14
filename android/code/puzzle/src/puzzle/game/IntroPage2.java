package puzzle.game;

import android.app.TabActivity;
import android.os.Bundle;
import android.widget.TabHost;
import android.widget.TextView;
import android.widget.TabHost.TabSpec;

public class IntroPage2 extends TabActivity {

	private int myMenuRes[] = {
			R.drawable.tab1,
			R.drawable.tab2,
			R.drawable.tab3,
			R.drawable.tab4,
			
	};

	TabHost tabHost;
	TabSpec firstTabSpec;
	TabSpec secondTabSpec;
	TabSpec threeTabSpec;
	TabSpec fourTabSpec;
	
   TextView info1;
   TextView info2;
   TextView info3;
   TextView info4;
   
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.intro2);

		setTitle("Introduction to Jigsaw");

	
		tabHost = (TabHost) findViewById(android.R.id.tabhost);
		tabHost.setBackgroundResource(R.drawable.background);

		firstTabSpec = tabHost.newTabSpec("tid1");
		secondTabSpec = tabHost.newTabSpec("tid2");
		threeTabSpec = tabHost.newTabSpec("tid3");
		fourTabSpec = tabHost.newTabSpec("tid4");
		
		firstTabSpec.setIndicator("OverView", getResources().getDrawable(
				myMenuRes[0]));
		secondTabSpec.setIndicator("PlayGame", getResources().getDrawable(
				myMenuRes[1]));
		threeTabSpec.setIndicator("ChoosePic", getResources().getDrawable(
				myMenuRes[2]));
		fourTabSpec.setIndicator("Ranking", getResources().getDrawable(
				myMenuRes[3]));
		
		String msg1,msg2,msg3,msg4;
		msg1="The program divides a picture (photo) into blocks (3x3, 4x4, etc), player resolves blocks to the original picture. \n\n";
   		msg1=msg1+"When running on device, one can touch the screen and drag the blocks to play the game.\n\n";
   		msg1=msg1+"User can choose picture from camera or gallery to play the puzzle, the record will be save in database and shown in ranking by comparing to the original records.";
		
   		msg2="1. Type in your name on the login page.\n\n";
        msg2=msg2+"2. Click <Choose Picture> to select a picture/photo first.\n\n";
        msg2=msg2+"3. Choose <Play Game> and select a difficulty level.\n\n";
        msg2=msg2+"4. Click the blocks to resolve the picture.";
        msg2=msg2+" You can see your name, how many steps and seconds you use at the top left.";
        msg2=msg2+" You can click the <Hint> button to see the original picture, however, the time will increase 10 seconds if you use hint.\n\n";
        msg2=msg2+ "5. After you finish resolving the picture, your new record will be checked if it is the top 5.";
        msg2=msg2+ " If yes, your new record will be kept. Then,it will go back to the game menu page.\n\n";
        msg2=msg2+ "6. If you choose to quit the game while you are playing, your record will not be saved and it will go back to the game menu page.";
   		
   		
        msg3="You can either choose a local picture from the gallery or use the camera to take a photo first and then use the photo as the puzzle picture.";
        
        
        msg4="If you click the <Ranking> button, you can see your records of each game difficulty. The records are represented with seconds.\n\n"; 
		msg4= msg4+ "You can only see the top 5 records.\n\n";
		msg4 = msg4+ "The ranking will show you the ranking, player name and time cost.";

   		info1=(TextView)findViewById(R.id.textview1);
	     info1.setText(msg1);
	     
	     info2=(TextView)findViewById(R.id.textview2);
	     info2.setText(msg2);

	     
	     info3=(TextView)findViewById(R.id.textview3);
	     info3.setText(msg3);

	     info4=(TextView)findViewById(R.id.textview4);
	     info4.setText(msg4);


		firstTabSpec.setContent(R.id.textview1);
		secondTabSpec.setContent(R.id.textview2);
		threeTabSpec.setContent(R.id.textview3);
		fourTabSpec.setContent(R.id.textview4);
		
		 
	     
	     
	     
	     
		tabHost.addTab(firstTabSpec);
		tabHost.addTab(secondTabSpec);
		tabHost.addTab(threeTabSpec);
		tabHost.addTab(fourTabSpec);
		
	}
}
