
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.Socket;
import java.net.URL;
import java.net.UnknownHostException;

import javax.swing.JTextArea;

public class TestClient{
	// validateControls(false, true, false, true);
	private String ip = "192.168.240.1";
	private int port = 123;
	private String toSend;
	private String msgReceived;
	private Socket clientSocket;
	private DataOutputStream outToServer;
	private BufferedReader inFromServer;
	private boolean isConnected;
	private JTextArea console;
	public TestClient(JTextArea console){
		isConnected=false;
		this.console = console;
	}
	public String connect(){
		return connect(ip,port);
	}
	private String connect(String host, int port) {
		try {
			clientSocket = new Socket(host, port);
			outToServer = new DataOutputStream(clientSocket.getOutputStream());
			inFromServer = new BufferedReader(new InputStreamReader(
					clientSocket.getInputStream()));
			return doHandshake();
		} catch (UnknownHostException e) {
			e.printStackTrace();
			return "Error" + e.getMessage() + '\n';
		} catch (IOException e) {
			e.printStackTrace();
			return "Error" + e.getMessage() + '\n';
		}

	}

	private String sendMsg(String msg) {
		try {
			outToServer.writeBytes(msg + '\n');
			return  "[ "+ msg +" ] Command was sent. \n";
		} catch (IOException e) {
			e.printStackTrace();
			return e.getMessage()+ '\n';
		}

	}

	public String closeConnection() {
		try {
			exit();
			clientSocket.close();
			this.isConnected = false;
			return "Connection was closed.\n";
		} catch (IOException e) {
			e.printStackTrace();
			return e.getMessage()+ '\n';
		}

	}

	private String readAnswer() {
		String answer = "";
		try {
			answer = inFromServer.readLine();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		return "Ack received \n";

	}

	
	public String forward(){
		return sendMsg("forward")+readAnswer();
	}
	public String backward(){
		return sendMsg("backward")+readAnswer();
	}
	public String leftF(){
		return sendMsg("leftForward")+readAnswer();
	}
	public String rightF(){
		return sendMsg("rightForward")+readAnswer();
	}
	public String leftB(){
		
		return sendMsg("leftBackward")+readAnswer();
	}
	public String rightB(){
		return sendMsg("rightBackward")+readAnswer();
	}
	
	public String stop(){
		return sendMsg("stop")+readAnswer();
	}
	public String park(){
		return sendMsg("test")+readAnswer();
	}
	public String exit(){
		return sendMsg("Exit")+readAnswer();
	}
	
	public String doHandshake(){
		sendMsg("Handshake");
		if(!readAnswer().equals("")){
			this.isConnected = true;
			//Server s = new Server(this.console,this.inFromServer);
			//s.start();
			return "Connection created successfully"; 
		}
		else {
			return "Error occured" ;
		}
	}
	
	public boolean isConnected() {
		return isConnected;
	}


}
