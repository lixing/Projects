
package puzzle.game;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.PixelFormat;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


public class UserName extends Activity {

	private EditText Name;
	
	


	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
        setContentView(R.layout.username);

		Name = (EditText) findViewById(R.id.username);
		
        Drawable blockImage = getResources().getDrawable(R.drawable.original);
 		
 		try {
			saveBitmap(drawableToBitmap(blockImage));
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		Button confirmButton = (Button) findViewById(R.id.confirmbutton);
		confirmButton.setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v)
			{
				
				
				Intent it = new Intent();
			    Bundle bl = new Bundle();  
			    bl.putString("name", Name.getText().toString());  
			    
			    it.putExtras(bl); 
			    
				
				it.setClass(UserName.this,GameMenu.class);
                startActivity(it);
                finish();
			}
		});
		
		
			}

	public static Bitmap drawableToBitmap(Drawable drawable) {  

	    Bitmap bitmap = Bitmap  
	                    .createBitmap(  
	                                    drawable.getIntrinsicWidth(),  
	                                    drawable.getIntrinsicHeight(),  
	                                    drawable.getOpacity() != PixelFormat.OPAQUE ? Bitmap.Config.ARGB_8888  
	                                                    : Bitmap.Config.RGB_565);  
	    Canvas canvas = new Canvas(bitmap);  
	     
	    drawable.setBounds(0, 0, drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight());  
	    drawable.draw(canvas);  
	    return bitmap;  
	} 
	
	public void saveBitmap(Bitmap bitmap) throws IOException
	{
	        File file = new File("/data/data/puzzle.game/"+"puzzle.jpg");
	        FileOutputStream out;
	        try{
	                out = new FileOutputStream(file);
	                if(bitmap.compress(Bitmap.CompressFormat.JPEG, 70, out))
	                {
	                        out.flush();
	                        out.close();
	                }
	        }
	        catch (FileNotFoundException e)
	        {
	                e.printStackTrace();
	        }
	        catch (IOException e)
	        {
	                e.printStackTrace();
	        }
	}


		
	}

