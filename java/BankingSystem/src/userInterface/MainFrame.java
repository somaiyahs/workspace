package userInterface;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class MainFrame extends JFrame {

	private static final long serialVersionUID = -5483651333966792253L;
	private JPanel content;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainFrame frame = new MainFrame();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public MainFrame() {
		this.initialize();
		this.setSize();

	}
	
	
	public void initialize() {
		content = new JPanel();
		content.getBorder();
		this.setContentPane(content);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	public void setSize() {
		this.setBounds(0,0, 400, 600);
	}

}
