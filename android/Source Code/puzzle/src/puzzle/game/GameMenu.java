package puzzle.game;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.ContentResolver;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;


public class GameMenu extends Activity {
    
    int m_count = 0;
    private static  Bitmap resizeBmp;
    private static  Bitmap p;
	protected static final int REQUEST_CODE = 0;
	private int music = 1;
	ProgressDialog m_pDialog;
	private String Name;
	Bitmap myBitmap=null;
	private byte[] mContent;
	private String Level;

	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.gamemenu);

        Integer[] images = { R.drawable.img1, R.drawable.img2,
                R.drawable.img3, R.drawable.img4};
  
        ImageAdapter adapter = new ImageAdapter(this, images);
        adapter.createReflectedImages();

        GalleryFlow galleryFlow = (GalleryFlow) findViewById(R.id.Gallery01);
        galleryFlow.setAdapter(adapter);
        galleryFlow.setOnItemClickListener(new OnItemClickListener() {

		
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
		 			long arg3) {
				// TODO Auto-generated method stub
				if(arg2==0)
					ChooseLevel();
				if(arg2==1)
					ChoosePic();
				if(arg2==2)
					CheckRanking();
				if(arg2==3){
					if(music==1)
         			{
         				Intent intent = new Intent();
         				intent.setClass(GameMenu.this,BackgroundMusic.class);
         				stopService(intent);
         				music = 0;
         			}	
         			else
         			{
         				Intent intent = new Intent();
         				intent.setClass(GameMenu.this,BackgroundMusic.class);
         				startService(intent);
         				music = 1;
         			}
				}
			
				
			}
		});
		
 		
        Intent intent = GameMenu.this.getIntent();
        intent.setClass(GameMenu.this,BackgroundMusic.class);
		startService(intent);
		
        Bundle bl= intent.getExtras(); 
        
    	Name = bl.getString("name");
        
    

 }     
    
     

private void ChoosePic()
{
final CharSequence[] items = {"Camera", "Gallery"};
new AlertDialog.Builder(this).setTitle("Choose a picture from:")
.setItems(items, new DialogInterface.OnClickListener() {
	
	public void onClick(DialogInterface dialog, int which) {
	
		if(items[which].equals("Camera"))
		{
			try{
			Intent getImageByCamera= new Intent("android.media.action.IMAGE_CAPTURE");   
			startActivityForResult(getImageByCamera, 1);   
			}catch(Exception e){
				e.printStackTrace();	
			}
		}
		else
		{
			try{
			Intent getImage = new Intent(Intent.ACTION_GET_CONTENT); 
	        getImage.addCategory(Intent.CATEGORY_OPENABLE); 
	        getImage.setType("image/jpeg"); 
	        startActivityForResult(getImage, 0); 
			}catch(Exception e){
				e.printStackTrace();	
			}
		}
	}
}).show();

}

private void ChooseLevel(){
final CharSequence[] items = {"4*4", "5*5", "6*6"};
new AlertDialog.Builder(this).setTitle("Choose the difficulties")
.setItems(items, new DialogInterface.OnClickListener() {
	
	public void onClick(DialogInterface dialog, int which) {
		
		if(items[which].equals("4*4"))
		{
			
			Intent intent = new Intent();
			
		    Bundle bl = new Bundle();  
		    bl.putString("name", Name);  
		    bl.putInt("Level", 4);  
		    
		    intent.putExtras(bl); 
			
			intent.setClass(GameMenu.this,Puzzles.class);
		
            startActivityForResult(intent, REQUEST_CODE);
		}
		else if(items[which].equals("5*5"))
		{
			Intent intent = new Intent();
			Bundle bl = new Bundle();  
		    bl.putString("name", Name);  
		    bl.putInt("Level", 5);  
		    intent.putExtras(bl);
			intent.setClass(GameMenu.this,Puzzles.class);
			
            startActivityForResult(intent, REQUEST_CODE);
		}
		else
		{
			Intent intent = new Intent();
			Bundle bl = new Bundle();  
		    bl.putString("name", Name);  
		    bl.putInt("Level", 6);  
		    intent.putExtras(bl);
			intent.setClass(GameMenu.this,Puzzles.class);
            startActivityForResult(intent, REQUEST_CODE);
		}
	}
}).show();
}


private void CheckRanking(){
final CharSequence[] items = {"4*4 Ranking", "5*5 Ranking", "6*6 Ranking"};
new AlertDialog.Builder(this).setTitle("View the Ranking")
.setItems(items, new DialogInterface.OnClickListener() {
	
	public void onClick(DialogInterface dialog, int which) {
		
		if(items[which].equals("4*4 Ranking"))
		{
			
		   
			
		
        Intent intent = new Intent();
			
		    Bundle bl = new Bundle();  
		   
		    bl.putInt("Level", 4);  
		    
		    intent.putExtras(bl); 
			
			intent.setClass(GameMenu.this,Ranking.class);
		
            startActivityForResult(intent, REQUEST_CODE);
            
		}
		else if(items[which].equals("5*5 Ranking"))
		{
            Intent intent = new Intent();
			
		    Bundle bl = new Bundle();  
		   
		    bl.putInt("Level", 5);  
		    
		    intent.putExtras(bl); 
			
			intent.setClass(GameMenu.this,Ranking.class);
		
            startActivityForResult(intent, REQUEST_CODE);
		}
		else
		{
          Intent intent = new Intent();
			
		    Bundle bl = new Bundle();  
		   
		    bl.putInt("Level", 6);  
		    
		    intent.putExtras(bl); 
			
			intent.setClass(GameMenu.this,Ranking.class);
		
            startActivityForResult(intent, REQUEST_CODE);
		}
	}
}).show();

}




protected void onActivityResult(int requestCode, int resultCode, Intent data) { 
    
    ContentResolver resolver = getContentResolver(); 
   
    if (requestCode == 0) { 
        try { 
          
            Uri originalUri = data.getData(); 
                      
            mContent=readStream(resolver.openInputStream(Uri.parse(originalUri.toString())));
           
            myBitmap = getPicFromBytes(mContent, null); 
          
            saveBitmap(myBitmap);
            
            saveBitmap(fitSizeImg("/data/data/puzzle.game/"+"puzzle.jpg"));
            
            if(resizeBmp.isRecycled()==false) 
		    	resizeBmp.recycle(); 
		    if(p.isRecycled()==false) 
		    	p.recycle();   
          
        } catch (Exception e) { 
        	e.printStackTrace();
        } 

    }else if(requestCode ==1){
    	try {
        	super.onActivityResult(requestCode, resultCode, data);
	    	Bundle extras = data.getExtras();
	    	myBitmap = (Bitmap) extras.get("data");
	    	ByteArrayOutputStream baos = new ByteArrayOutputStream();     
	    	myBitmap.compress(Bitmap.CompressFormat.JPEG , 100, baos);     
			mContent=baos.toByteArray();
		    saveBitmap(myBitmap);
		    saveBitmap(fitSizeImg("/data/data/puzzle.game/"+"puzzle.jpg"));
		    if(resizeBmp.isRecycled()==false) 
		    	resizeBmp.recycle(); 
	    	    resizeBmp = null;
		    if(p.isRecycled()==false) 
		    	p.recycle();   
		        p = null;
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
} 

public static Bitmap getPicFromBytes(byte[] bytes, BitmapFactory.Options opts) { 
    if (bytes != null) 
        if (opts != null) {
        	 p=BitmapFactory.decodeByteArray(bytes, 0, bytes.length,opts);
      
            return p; 
        }
        else {
        	p=BitmapFactory.decodeByteArray(bytes, 0, bytes.length);

            return p; 
        }
    return null; 
} 

public static byte[] readStream(InputStream inStream) throws Exception {
    byte[] buffer = new byte[1024];
    int len = -1;
    ByteArrayOutputStream outStream = new ByteArrayOutputStream();
    while ((len = inStream.read(buffer)) != -1) {
             outStream.write(buffer, 0, len);
    }
    byte[] data = outStream.toByteArray();
    outStream.close();
    inStream.close();
    return data;

}




public void saveBitmap(Bitmap bitmap) throws IOException
{
        File file = new File("/data/data/puzzle.game/"+"puzzle.jpg");
        
        FileOutputStream out;
        try{
                out = new FileOutputStream(file);
                if(bitmap.compress(Bitmap.CompressFormat.JPEG, 100, out))
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


      public static Bitmap fitSizeImg(String path) {
             if(path == null || path.length()<1 ) 
            	 return null;
             File file = new File(path);
             BitmapFactory.Options opts = new BitmapFactory.Options();

 
       
         if (file.length() < 307200) {
                  opts.inSampleSize = 1;
            } 
            else if (file.length() < 819200) { 
                  opts.inSampleSize = 2;
            }
            else if (file.length() < 1048576) {
                  opts.inSampleSize = 4;
            }
            else {
                  opts.inSampleSize = 6;
             }
       

             resizeBmp = BitmapFactory.decodeFile(file.getPath(), opts);

            return resizeBmp;
 

}
      
      
      public boolean onKeyDown(int keyCode,KeyEvent event) {   
            if (keyCode == KeyEvent.KEYCODE_BACK) {   
            	Intent intent = new Intent();
 				intent.setClass(GameMenu.this,BackgroundMusic.class);
 				stopService(intent);
 				music = 0;
         	  finish();
        
                return true;   
            } else
         	   
                return super.onKeyDown(keyCode,event);   
            }     	
             


}