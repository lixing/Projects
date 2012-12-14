/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.awt.*;
import java.awt.geom.*;

public class Rectangle extends DrawShape {
	// Rectangle inherits int x int y 
	//   we will use these for the center of the circle
    private int width; // width of Rectangle 
    private int height;// height of Rectangle 
    
    public Rectangle(int x, int y, int width, int height) {
    	setX(x);
    	setY(y);
    	this.width = width;
    	this.height = height;
    }
    
    public String toString() {
		return DrawShape.RECTANGLE+ ":"+getX()+":"+getY()+":"+width+":"+height+":"+isFilled();
	}
    
	//Must Override from abstract class
	public void drawSelf(Graphics g) {
		if(isFilled()) {
			g.setColor(Color.green);
			g.fillRect(getX(), getY(), width, height);
		}
		else {
			g.setColor(Color.black);
			g.drawRect(getX(), getY(), width, height);
		}
	}

	public void resizeTo(int newX, int newY){
		double delx = getX() - newX;
		double dely = getY() - newY;
		this.width = (int) Math.abs(delx);
	    this.height = (int) Math.abs(dely);
	}
}
