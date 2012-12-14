/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.awt.*; 
import java.awt.event.*;
import java.util.*;
import javax.swing.*; 

public class Canvas extends JPanel implements MouseListener, MouseMotionListener{
	private int size;
	private int oldX=0, oldY=0;
	private Vector<DrawShape> shapes = new Vector();
	private String currentShapeType = DrawShape.CIRCLE;
	private DrawShape currentShape = null;
	
	public Canvas(int size) {
		super();
		this.setSize(size,size);
		this.size = size;

		addMouseListener(this);
		addMouseMotionListener(this);
	}
	
	public void setDrawingShape(String type){
		currentShapeType = type;
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		Graphics2D g2 = (Graphics2D)g;
		for(DrawShape s: shapes) {
			s.drawSelf(g2);
		}
	}
	
	// MouseListener Interface Methods
	public void mousePressed(MouseEvent e) {
		System.out.println("mouse press at ("+e.getX()+","+e.getY()+")");
		oldX = e.getX();
		oldY = e.getY();
		DrawShape shape=null;
		if(currentShapeType.equals(DrawShape.CIRCLE))
			shape = new Circle(oldX, oldY, 0);
		else  if(currentShapeType.equals(DrawShape.FILL_CIRCLE)) {
			shape = new Circle(oldX, oldY, 0);
			shape.setFilled(true);
		}
		else if(currentShapeType.equals(DrawShape.RECTANGLE)){
			shape = new Rectangle(oldX, oldY, 0,0);
		}
		else  if(currentShapeType.equals(DrawShape.FILL_RECTANGLE)) {
			shape = new Rectangle(oldX, oldY, 0,0);
			shape.setFilled(true);
		}
		else if(currentShapeType.equals(DrawShape.SQUARE)){
			shape = new Square(oldX, oldY, 0,0);
		}
		else  if(currentShapeType.equals(DrawShape.FILL_SQUARE)) {
			shape = new Square(oldX, oldY, 0,0);
			shape.setFilled(true);
		}
		else if(currentShapeType.equals(DrawShape.ARC)){
			shape = new Arc(oldX, oldY, 0,0,0,0);
		}
		else  if(currentShapeType.equals(DrawShape.FILL_ARC)) {
			shape = new Arc(oldX, oldY, 0,0,0,0);
			shape.setFilled(true);
		}
		else if(currentShapeType.equals(DrawShape.OVAL)){
			shape = new Oval(oldX, oldY, 0,0);
		}
		else  if(currentShapeType.equals(DrawShape.FILL_OVAL)) {
			shape = new Oval(oldX, oldY, 0,0);
			shape.setFilled(true);
		}
		else {}
		
		if(shape!=null){
			shapes.add(shape);
			currentShape = shape;
		}
		repaint(); // Force panel to repaint itself
	}
	public void mouseClicked(MouseEvent e){
		System.out.println("mouse click at ("+e.getX()+","+e.getY()+")");
	}
	public void mouseReleased(MouseEvent e){
		System.out.println("mouse release at ("+e.getX()+","+e.getY()+")");
	}
	public void mouseEntered(MouseEvent e){
		System.out.println("mouse enter at ("+e.getX()+","+e.getY()+")");
	}
	public void mouseExited(MouseEvent e){
		System.out.println("mouse exit at ("+e.getX()+","+e.getY()+")");
	}
	
	// MouseMotionListener Methods
	public void mouseDragged(MouseEvent e){
		System.out.println("mouse dragged to ("+e.getX()+","+e.getY()+")");
		if(currentShape != null) currentShape.resizeTo(e.getX(),e.getY());
		repaint(); // Force panel to repaint itself
	}
	public void mouseMoved(MouseEvent e){
		System.out.println("mouse moved to ("+e.getX()+","+e.getY()+")");
	}
}

