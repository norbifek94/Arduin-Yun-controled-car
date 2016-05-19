import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JTextArea;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JMenu;

public class UI {

	private JFrame frame;
	private TestClient controler;
	private Server server;
	JTextArea console ;
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UI window = new UI();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public UI() {
		initialize();
		controler = new TestClient(console);
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 480, 433);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		JButton btnForward = new JButton("forward");
		btnForward.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent arg0) {
				console.append(controler.forward() +"\n");
			}
			@Override
			public void mouseReleased(MouseEvent arg0) {
				console.append(controler.stop() +"\n");
			}
		});

		btnForward.setBounds(161, 32, 89, 49);
		frame.getContentPane().add(btnForward);
		
		JButton btnLeftF = new JButton("leftF");
		btnLeftF.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent arg0) {
				console.append(controler.leftF() +"\n");
			}
			@Override
			public void mouseReleased(MouseEvent arg0) {
				console.append(controler.stop() +"\n");
			}
		});

		btnLeftF.setBounds(71, 67, 89, 36);
		frame.getContentPane().add(btnLeftF);
		
		JButton btnRightF = new JButton("rightF");
		btnRightF.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent arg0) {
				console.append(controler.rightF() +"\n");
			}
			@Override
			public void mouseReleased(MouseEvent arg0) {
				console.append(controler.stop() +"\n");
			}
		});

		btnRightF.setBounds(249, 67, 89, 36);
		frame.getContentPane().add(btnRightF);
		
		JButton btnBackward = new JButton("backward");
		btnBackward.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent arg0) {
				console.append(controler.backward() +"\n");
			}
			@Override
			public void mouseReleased(MouseEvent arg0) {
				console.append(controler.stop() +"\n");
			}
		});

		btnBackward.setBounds(161, 131, 89, 49);
		frame.getContentPane().add(btnBackward);
		
		JButton btnStop = new JButton("stop");
		btnStop.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				console.append(controler.stop() +"\n");
			}
		});
		btnStop.setBounds(161, 92, 89, 23);
		frame.getContentPane().add(btnStop);
		
		JButton btnPark = new JButton("park");
		btnPark.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				console.append(controler.park() +"\n");
				
			}
		});
		btnPark.setBounds(375, 32, 89, 23);
		frame.getContentPane().add(btnPark);
		
	
		
		JButton btnLeftB = new JButton("leftB");
		btnLeftB.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent arg0) {
				console.append(controler.leftB() +"\n");
			}
			@Override
			public void mouseReleased(MouseEvent arg0) {
				console.append(controler.stop() +"\n");
			}
		});
		btnLeftB.setBounds(71, 102, 89, 36);
		frame.getContentPane().add(btnLeftB);
		
		JButton btnRightB = new JButton("rightB");
		btnRightB.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent arg0) {
				console.append(controler.rightB() +"\n");
			}
			@Override
			public void mouseReleased(MouseEvent arg0) {
				console.append(controler.stop() +"\n");
			}
		});
		btnRightB.setBounds(249, 97, 89, 41);
		frame.getContentPane().add(btnRightB);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(10, 191, 444, 192);
		frame.getContentPane().add(scrollPane);
		
		console = new JTextArea();
		console.setEditable(false);
		scrollPane.setViewportView(console);
		
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		
		JMenu mnFile = new JMenu("File");
		menuBar.add(mnFile);
		
		JMenuItem mntmConnect = new JMenuItem("Connect");
		mntmConnect.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				console.append(controler.connect());

				
			}
		});
		mnFile.add(mntmConnect);
		
		JMenuItem mntmDisconnect = new JMenuItem("Disconnect");
		mntmDisconnect.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				console.append(controler.closeConnection());
			}
		});
		mnFile.add(mntmDisconnect);
		
		JMenuItem mntmSearchForAvaiable = new JMenuItem("Search for avaiable car");
		mnFile.add(mntmSearchForAvaiable);
		
		JMenuItem menuItem = new JMenuItem("New menu item");
		menuBar.add(menuItem);
	}
}
