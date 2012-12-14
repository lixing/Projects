
/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.awt.*;
import java.awt.geom.*;

public class Square extends DrawShape {
	// Square inherits int x int y 
	//   we will use these for the center of the circle
    private int width; // width of Square 
    private int height;// height of Square 
    
    public Square(int x, int y, int width, int height) {
    	setX(x);
    	setY(y);
    	this.width = width;
    	this.height = width;
    }
    
    public String toString() {
		return DrawShape.RECTANGLE+ ":"+getX()+":"+getY()+":"+width+":"+height+":"+isFilled();
	}
    
	//Must Override from abstract class
	public void drawSelf(Graphics g) {
		if(isFilled()) {
			g.setColor(Color.orange);
			g.fillRect(getX(), getY(), width, width);
		}
		else {
			g.setColor(Color.black);
			g.drawRect(getX(), getY(), width, width);
		}
	}

	public void resizeTo(int newX, int newY){
		double delx = getX() - newX;
		double dely = getY() - newY;
		this.width = (int) Math.abs(delx);
	    this.height = (int) Math.abs(delx);
	}
}
