
package puzzle.game;



import android.app.Activity;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.widget.ImageView;
import android.widget.TextView;


public class Hint extends Activity implements Runnable {

	 ImageView imgView;
	TextView information;
	private int time=5;
	Handler handler;
	TextView count;
	private String path = "/data/data/puzzle.game/puzzle.jpg";
	
    
	public void onCreate(Bundle savedInstanceState) {
		  
        super.onCreate(savedInstanceState);
        setContentView(R.layout.hint);
    	Drawable blockImage;    
		blockImage = new BitmapDrawable(path);
        count=(TextView)findViewById(R.id.count4);
     	 count.setText(""+time);
      
        imgView = (ImageView) this.findViewById(R.id.imageView2);
        imgView.setImageDrawable(blockImage);
    
        information = (TextView) this.findViewById(R.id.textView2);
        information.setText("Your time will be additionally added 10 seconds.");
     
    	
     
      
		 handler=new Handler();
	      handler.postDelayed(this,0);
	    }
	                public void run()
	                {                     
	                	count.setText("The hint will be closed in "+time+" secends.");
	                	time--;
	                	handler.postDelayed(this, 1000);
	                   if(time==0){
	                    finish();
	                         }
	                }
		}
    
		
		
			



		
	

