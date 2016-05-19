import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

import javax.swing.JTextArea;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


class Server implements Runnable {
   private Thread t;

	private JTextArea console;
    private BufferedReader reader;
   Server( JTextArea console, BufferedReader reader){
       System.out.println("Starting Server");
       this.console = console;
       this.reader = reader;
   }
   
   public void run() {
      System.out.println("Running "  );

    	  while(true){
			String in = "";
			try {
				in = reader.readLine();   // reading message
				console.append(in + "\n");
			} catch (IOException e) {
				e.printStackTrace();
			}
			
		}
   }

   
   public void start ()
   {
      System.out.println("Starting " );
      if (t == null)
      {
         t = new Thread (this);
         t.start ();
      }
   }
   

}