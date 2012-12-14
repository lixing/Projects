package puzzle.game;



import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import org.openintents.sensorsimulator.hardware.SensorManagerSimulator;

import android.app.Activity;
import android.os.Handler;
import android.os.Message;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Resources;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class Puzzles extends Activity implements  SensorListener, Runnable{
 
	private BlockView draw = null;
	
	private int time = 0;
	
	private float value1;
	private float value2;

	
	private int i=0;

	private DataAccess data;
	Handler handler;
	private Cursor  cura;
	private Cursor  curb;
	private Cursor  curc;
	private Cursor  curd;
	private Cursor  cure;
	
	
	private String Name;

	TextView showstep;
	
	TextView count;
	TextView player;
	TextView command;
	
	private int Level;
	
	private String table;
	
	private int timerecord;
	
	private SensorManager mSensorManager;

	private int k;

	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        
        setContentView(R.layout.game);
        
        Intent intent = Puzzles.this.getIntent();
        
        Bundle bl= intent.getExtras(); 
        
    	Name = bl.getString("name");
    	
    	Level=bl.getInt("Level");
    	
    
    
        
    	draw = (BlockView) findViewById(R.id.draw);
    
    	if(Level==4){
			
    		draw.setRows(4);
    		draw.setCols(4);
		}
		 if(Level==5){
			draw.setRows(5);
			draw.setCols(5);
		
		}
		if(Level==6){
		
			draw.setRows(6);
			draw.setCols(6);

		}
	 
	 
	
		
         player=(TextView)findViewById(R.id.player);
     	player.setText("Player Name: "+ Name+"");
     	
     	 command=(TextView)findViewById(R.id.command);
     	command.setText("Shake to restart | Click hint will add up 10s.");
     	
         showstep=(TextView)findViewById(R.id.showstep);
     	 showstep.setText("Steps: 0");
         draw.setTextView(showstep);
         
       
       	
       	count=(TextView)findViewById(R.id.count);
       	count.setText("Time Cost: 0 seconds");
       
       	
       mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
       
      
       	Button button10 = (Button) findViewById(R.id.button10);
    	button10.setOnClickListener(new Button.OnClickListener() {
     		public void onClick(View v)
     		{ 
              try{
     		
     		
     		Intent intent = new Intent();
   			intent.setClass(Puzzles.this,Hint.class);
   			startActivity(intent);	
   			time=time+5;
     			
     		
     		}catch(Exception e){}	
     	}});
    	
     
        handler=new Handler();
        handler.postDelayed(this,0);
    	
    }
                public void run()
                {    
                          	count.setText("Time Cost: "+time+" seconds");
                                        time++;
                                        
                                        handler.postDelayed(this, 1000);
                             
                
                       
                        
                }
      
       	
    
     public boolean onKeyDown(int keyCode,KeyEvent event) {   
           if (keyCode == KeyEvent.KEYCODE_BACK) {   
        	   timerecord=time;  
        	 
        	   ShowInfo();   
        	   
              mSensorManager.unregisterListener(this);
       
               return true;   
           } else
        	   
               return super.onKeyDown(keyCode,event);   
           }     	
            
    
    

   public void ShowInfo() {

	     
    	if(draw.getStatus().equals("incomplete")){
    		String msg = "";
    		msg= msg + "Player Name:  " + Name + "\n";
    		msg= msg + "Status: incomplete\n";
    		msg= msg + "Time:  " + timerecord + "\n";
    		msg= msg + "Step:  " + draw.getStep()+ "\n";;
    		msg= msg + "You are incomplete, your performance will not be recorded.";
    			
    			
    			new AlertDialog.Builder(this)
    			.setTitle("Performance")
    			.setMessage(""+msg)
    			.setPositiveButton("OK", new DialogInterface.OnClickListener() {
    				public void onClick(DialogInterface dialog, int which) {
    					 android.os.Process.killProcess(android.os.Process.myPid());   
    				}
    			})
    			.show();
			
		}
    	
		
        if(draw.getStatus().equals("complete")){
        
        	
    		
    		
          	
    		String msg = "";
    		msg= msg + "Player Name:  " + Name + "\n";
    		msg= msg + "Status: complete\n";
    		msg= msg + "Time:  " + timerecord + "\n";
    		msg= msg + "Step:  " + draw.getStep();
    		
    			
    			
    			new AlertDialog.Builder(this)
    			.setTitle("Performance")
    			.setMessage(""+msg)
    			.setPositiveButton("OK", new DialogInterface.OnClickListener() {
    				public void onClick(DialogInterface dialog, int which) {
    					if(Level==4){
    						table="level4";
    					}
    					else if(Level==5){
    						table="level5";
    					}
    					if(Level==6){
    						table="level6";
    						
    					}
    					checkDatabase(table);
    					android.os.Process.killProcess(android.os.Process.myPid());   
    				}
    			})
    			.show();
    		
        }
   
       }
    	
    	  

	public void checkDatabase(String table) {

  	        
	    data = new DataAccess(this);
		
		
		cura = data.loadRanking(table,5);
		curb = data.loadRanking(table,4);
		curc = data.loadRanking(table,3);
		curd = data.loadRanking(table,2);
		cure = data.loadRanking(table,1);
		
            
            if(cura.isAfterLast()){
            	
            	
            	if(curb.isAfterLast()){
            		
                	if(curc.isAfterLast()){
                		
                		if(curd.isAfterLast()){
                			
                			if(cure.isAfterLast()){
                				data.save(table,Name, timerecord, 1);
                			}
                			else{
                				 int record1 = cure.getInt(1);
                        		 if(timerecord< record1){
                                 	
                                 	data.save(table,cure.getString(0), cure.getInt(1), 2);
                                 	data.deleteRecord(table,1);
                                 	data.save(table,Name, timerecord, 1);
                			}
                        		 else data.save(table,Name, timerecord, 2);
                		}
                    	
                    	
                    }
                	else {
                		 int record2 = curd.getInt(1);
                		 if(timerecord< record2){
                			 data.save(table,curd.getString(0), curd.getInt(1), 3);
                           	data.deleteRecord(table,2);
                		 
                		     int record1 = cure.getInt(1);
                		     if(timerecord< record1){
                		    	
                              	data.save(table,cure.getString(0), cure.getInt(1), 2);
                             	data.deleteRecord(table,1);
                             	data.save(table,Name, timerecord, 1);
                		     }
                		     else data.save(table,Name, timerecord, 2);
                		 }
                		 else data.save(table,Name, timerecord, 3);
                         	
                	}
                	}
                	else{
                		 int record3 = curc.getInt(1);
                		 if(timerecord< record3){
                			 data.save(table,curc.getString(0), curc.getInt(1), 4);
                           	data.deleteRecord(table,3);
                            int record2 = curc.getInt(1);
                           	if(timerecord< record2){
                   			 data.save(table,curd.getString(0), curd.getInt(1), 3);
                             data.deleteRecord(table,2);
                             int record1 = cure.getInt(1);
                             if(timerecord< record1){
                            	 data.save(table,cure.getString(0), cure.getInt(1), 2);
                                 data.deleteRecord(table,1);
                                 data.save(table,Name, timerecord, 1);
                                 }
                             else data.save(table,Name, timerecord, 2);
                             }
                           	else data.save(table,Name, timerecord, 3);
                	}
                		 else data.save(table,Name, timerecord, 4);
                	}
            	}
            	else{
            		int record4=curb.getInt(1);
            		 if(timerecord< record4){
            			data.save(table,curb.getString(0), curb.getInt(1), 5);
                       	data.deleteRecord(table,4);
                        int record3=curc.getInt(1);
                        if(timerecord< record3){
               			 data.save(table,curc.getString(0), curc.getInt(1), 4);
                          data.deleteRecord(table,3);
                           int record2 = curc.getInt(1);
                          	if(timerecord< record2){
                  			 data.save(table,curd.getString(0), curd.getInt(1), 3);
                            data.deleteRecord(table,2);
                            int record1 = curc.getInt(1);
                            if(timerecord< record1){
                           	 data.save(table,cure.getString(0), cure.getInt(1), 2);
                                data.deleteRecord(table,1);
                                data.save(table,Name, timerecord, 1);
                                }
                            else data.save(table,Name, timerecord, 2);
                            }
                          	else data.save(table,Name, timerecord, 3);
               	}
                        else data.save(table,Name, timerecord, 4);
               		 
               	}
            		 else data.save(table,Name, timerecord, 5);
            	}
            	}
                	
            
            
            
        else {
        	
            int record5 = cura.getInt(1);
           
            int record4 = curb.getInt(1);
            
            int record3 = curc.getInt(1);
            
            int record2 = curd.getInt(1);
            
            int record1 = cure.getInt(1);
          
          if(timerecord<record5){
        	  data.deleteRecord(table,5);
        	  
                if(timerecord< record4){
                	
                	data.save(table,curb.getString(0), curb.getInt(1), 5);
                	data.deleteRecord(table,4);
           
                       
                       if(timerecord< record3){
              			 data.save(table,curc.getString(0), curc.getInt(1), 4);
                         data.deleteRecord(table,3);
                          
                         	if(timerecord< record2){
                 			 data.save(table,curd.getString(0), curd.getInt(1), 3);
                             data.deleteRecord(table,2);
                       
                           if(timerecord< record1){
                            	 data.save(table,cure.getString(0), cure.getInt(1), 2);
                               data.deleteRecord(table,1);
                               data.save(table,Name, timerecord, 1);
                               }
                           else data.save(table,Name, timerecord, 2);
                           }
                         	else data.save(table,Name, timerecord, 3);
              	}
                       else data.save(table,Name, timerecord, 4);
              		 
              	}
           		 else data.save(table,Name, timerecord, 5);
                	
                }
                
        }
        data.close();
		}
	
	
	protected void onResume() {
    	draw.setUpdateRunningAfterInited(true);
    	mSensorManager.registerListener(this, SensorManager.SENSOR_ACCELEROMETER
				| SensorManager.SENSOR_MAGNETIC_FIELD
				| SensorManager.SENSOR_ORIENTATION,
				SensorManager.SENSOR_DELAY_FASTEST);
			
    	super.onResume();
    }

	public void onAccuracyChanged(int arg0, int arg1) {
		// TODO Auto-generated method stub
		
	}

	public void onSensorChanged(int sensor, float[] value) {

	    if (sensor == SensorManager.SENSOR_ORIENTATION)
	    {
	       
	    	value1=value[0];
	    	   
	    	if (value1-value2>30 || value1-value2<-30){
	    	
	    		if(value[0]>=180 && value[0]<360){				
	    			
	    			i++;
	    			if(i==3){
	    				time=0;
	    				try {
							Thread.sleep(1000);
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
	    				draw.setStep(0);
	    				showstep.setText("Steps: 0");
	    				draw.randomPannel();
	    				i=0;
	    				value2=value[0];
	    				
	    			}
	    		
	    			
	    		}
	    	
	    	
	    	
	    	}
	    	
	        }
	        
	    	 
	    	 
	    	 
	 
		 
	
}

	
	
	
}