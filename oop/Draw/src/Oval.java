/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.awt.*;
import java.awt.geom.*;

public class Oval extends DrawShape {
	// Oval inherits int x int y 
	//   we will use these for the center of the circle
    private int width; // width of Oval  
    private int height;// height of Rectangle 
    
    public Oval(int x, int y, int width, int height) {
    	setX(x);
    	setY(y);
    	this.width = width;
    	this.height = height;
    }
    
    public String toString() {
		return DrawShape.OVAL+ ":"+getX()+":"+getY()+":"+width+":"+height+":"+isFilled();
	}
    
	//Must Override from abstract class
	public void drawSelf(Graphics g) {
		if(isFilled()) {
			g.setColor(Color.blue);
			g.fillOval(getX(), getY(), width, height);
		}
		else {
			g.setColor(Color.black);
			g.drawOval(getX(), getY(), width, height);
		}
	}

	public void resizeTo(int newX, int newY){
		double delx = getX() - newX;
		double dely = getY() - newY;
		this.width = (int) Math.abs(delx);
	    this.height = (int) Math.abs(dely);
	}
}
