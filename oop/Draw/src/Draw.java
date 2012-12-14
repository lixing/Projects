/*
 * @author Yves Lian
 * @ID 0830300023
 */

import java.awt.*; 
import java.awt.event.*;
import javax.swing.*; 

public class Draw extends JFrame {
	private static int size = 400;
	private Canvas canvas;
    private JScrollPane scrollPane;

    public Draw() {
    	super("Draw - COMP2020");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the menu bar
        setJMenuBar(createMenuBar());
        Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

        //Create a drawing area.
        canvas = new Canvas(400);
        scrollPane = new JScrollPane(canvas);

        //Add the text area to the content pane.
        contentPane.add(scrollPane, BorderLayout.CENTER);

        //Display the window.
        setSize(size, size);
        setVisible(true);

    }
	
	public JMenuBar createMenuBar() {
        JMenuBar menuBar;
        JMenu menu;
        JMenuItem menuItem;

        //Create the menu bar.
        menuBar = new JMenuBar();

        //Build Shape menu.
        ShapeListener sl = new ShapeListener();
        menu = new JMenu("Shape");
        // Circle menu 
        menuItem = new JMenuItem("Circle");
        menuItem.setActionCommand(DrawShape.CIRCLE);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Filled Circle menu 
        menuItem = new JMenuItem("Filled Circle");
        menuItem.setActionCommand(DrawShape.FILL_CIRCLE);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Rectangles menu 
        menuItem = new JMenuItem("Rectangles");
        menuItem.setActionCommand(DrawShape.RECTANGLE);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Filled Rectangles menu 
        menuItem = new JMenuItem("Filled Rectangles");
        menuItem.setActionCommand(DrawShape.FILL_RECTANGLE);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Arcs menu 
        menuItem = new JMenuItem("Arcs");
        menuItem.setActionCommand(DrawShape.ARC);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Filled Arcs menu 
        menuItem = new JMenuItem("Filled Arcs");
        menuItem.setActionCommand(DrawShape.FILL_ARC);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Squres menu 
        menuItem = new JMenuItem("Squares");
        menuItem.setActionCommand(DrawShape.SQUARE);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Filled Squres menu 
        menuItem = new JMenuItem("Filled Squares");
        menuItem.setActionCommand(DrawShape.FILL_SQUARE);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Oval menu 
        menuItem = new JMenuItem("Oval");
        menuItem.setActionCommand(DrawShape.OVAL);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Filled Oval menu 
        menuItem = new JMenuItem("Filled Oval");
        menuItem.setActionCommand(DrawShape.FILL_OVAL);
        menuItem.addActionListener(sl);
        menu.add(menuItem);
        // Add Shape menu to menubar
        menuBar.add(menu);

        return menuBar;
    }
	
	// Inner class 
	private class ShapeListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			canvas.setDrawingShape(command);
		}
	}
    
	public static void main(String[] args){new Draw();} 
}


