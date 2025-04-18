package userInterface;

import java.awt.*;
import javax.swing.*;

public class ATM {

	private JFrame mainFrame;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ATM window = new ATM();
					window.mainFrame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public ATM() {
		this.initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		mainFrame = new JFrame();
		mainFrame.setResizable(true);
		mainFrame.setBounds(100, 100, 450, 300);
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		mainFrame.getContentPane().setLayout(null);
		
		JButton showBalance = new JButton("Balance");
		showBalance.setBounds(20, 0, 85, 37);
		mainFrame.getContentPane().add(showBalance);
		
		JPanel panel = new JPanel();
		panel.setBounds(20, 5, 85, 248);
		mainFrame.getContentPane().add(panel);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBounds(117, 6, 310, 247);
		mainFrame.getContentPane().add(panel_1);
	}
}
