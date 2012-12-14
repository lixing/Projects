
package puzzle.game;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;


public class IntroPage1 extends Activity {

	 ImageView imgView;
	TextView information;
	
	
	public void onCreate(Bundle savedInstanceState) {
		  
        super.onCreate(savedInstanceState);
      

        setContentView(R.layout.intro1);
       
        imgView = (ImageView) this.findViewById(R.id.imageView);
        imgView.setBackgroundResource(R.drawable.m8);
        String msg="The aims of this app are to highlight the screen resolution (720*480), G-Sensor, camera (3.2 Megapixel) and screen-touching of M8.";
        information = (TextView) this.findViewById(R.id.textView);
        information.setText(msg);
       
    	Button button7 = (Button) findViewById(R.id.button7);
		button7.setOnClickListener(new Button.OnClickListener() {
					public void onClick(View v)
					{														
						finish();
					}
				});
     
      
     
		}
    }
		
		
			



		
	

