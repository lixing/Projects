/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.awt.*; 
import java.awt.event.*;
import java.util.*;
import javax.swing.*; 

public abstract class DrawShape {
	public static String CIRCLE = "Circle"; 
	public static String FILL_CIRCLE = "FilledCircle"; 
	public static String RECTANGLE = "Rectangle";
	public static String FILL_RECTANGLE = "FilledRectangle";
	public static String ARC = "Arc";
	public static String FILL_ARC = "FilledArc";
	public static String SQUARE = "Squares";
	public static String FILL_SQUARE = "FilledSquare";
	public static String OVAL = "Oval";
	public static String FILL_OVAL = "FilledOval";
	
	// Instance variables shared by all subclasses
	private int x,y; // location of shape
	
	private boolean filled = false;
	
	// Accessor, Mutator methods
	public int getX() {return x;}
	public void setX(int x) {this.x = x;}
	
	public int getY() {return y;}
	public void setY(int y) {this.y = y;}
	
	
	
	public boolean isFilled() {return filled;}
	public void setFilled(boolean filled) {this.filled = filled;}
	
	// Methods that are identical in all subclasses
	public void moveTo(int x, int y){
		this.x = x;
		this.y = y;
	}
	
	// Methods that each subclass will implement differently
	public abstract void drawSelf(Graphics g);
	public abstract void resizeTo(int newX, int newY);
}
