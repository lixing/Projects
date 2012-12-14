/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.awt.*;
import java.awt.geom.*;

public class Circle extends DrawShape {
	// Circle inherits int x int y 
	//   we will use these for the center of the circle
    private int r; // radius of circle 
    
    public Circle(int x, int y, int r) {
    	setX(x);
    	setY(y);
    	this.r = r;
    }
    
    public String toString() {
		return DrawShape.CIRCLE+ ":"+getX()+":"+getY()+":"+r+":"+isFilled();
	}
    
	//Must Override from abstract class
	public void drawSelf(Graphics g) {
		if(isFilled()) {
			g.setColor(Color.red);
			g.fillOval(getX()-r, getY()-r, 2*r, 2*r);
		}
		else {
			g.setColor(Color.black);
			g.drawOval(getX()-r, getY()-r, 2*r, 2*r);
		}
	}

	public void resizeTo(int newX, int newY){
		double delx = getX() - newX;
		double dely = getY() - newY;
		this.r = (int) Math.sqrt(delx*delx + dely*dely);
	}
}
