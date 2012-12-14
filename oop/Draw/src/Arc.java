/*
 * @author Yves Lian
 * @ID 0830300023
 */

import javax.swing.JOptionPane;
import java.awt.*;
import java.awt.geom.*;



public class Arc extends DrawShape {
	// Arc inherits int x int y 
	//   we will use these for the center of the circle
	private int width; // width of Arc 
	private int height;// height of Arc 
	private int startAngle; // startAngle of Arc 
	private int arcAngle;// arcAngle of Arc 
	    
	public Arc(int x, int y, int width, int height, int startAngle, int arcAngle) {
	    setX(x);
	    setY(y);
	    this.width = width;
	    this.height = height;
	    this.startAngle = startAngle;
	    this.arcAngle = arcAngle;
		}
	
	   public String toString() {
			return DrawShape.ARC+ ":"+getX()+":"+getY()+":"+width+":"+height+":"+startAngle+":"+arcAngle+":"+isFilled();
		}
	    
		//Must Override from abstract class
		public void drawSelf(Graphics g) {
			if(isFilled()) {
				g.setColor(Color.pink);
				g.fillArc(getX(), getY(), width, height, startAngle, arcAngle);
			}
			else {
				g.setColor(Color.black);
				g.drawArc(getX(), getY(), width, height, startAngle, arcAngle);
			}
		}

		public void resizeTo(int newX, int newY){
			double delx = getX() - newX;
			double dely = getY() - newY;
			this.width = (int) Math.abs(delx);
		    this.height = (int) Math.abs(dely);
			startAngle=0;
			arcAngle=90;
			
			
		}
	}
