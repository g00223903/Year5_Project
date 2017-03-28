
// File Name GreetingServer.java
import java.net.*;
import java.io.*;

public class GreetingServer extends Thread {
   private ServerSocket serverSocket;
   
   public GreetingServer(int port) throws IOException {
      serverSocket = new ServerSocket(port);
      serverSocket.setSoTimeout(1000000);
   }

   public void run() {
      while(true) {
         try {
            System.out.println("Waiting for client on port " + 
               serverSocket.getLocalPort() + "...");
            Socket server = serverSocket.accept();
            System.out.println("Just connected to " + server.getRemoteSocketAddress());
            //input from client
            BufferedReader   in = new BufferedReader(new InputStreamReader(server.getInputStream()));
            //String clientCommand = in.readLine();
            System.out.println(in.readLine());
            
            //output to client
            PrintWriter out = new PrintWriter(new OutputStreamWriter(server.getOutputStream()));
            String s = "Hello from server\0";
            out.println(s);
            out.flush();
            server.close();
                      
         }catch(SocketTimeoutException s) {
            System.out.println("Socket timed out!");
            break;
         }catch(IOException e) {
            e.printStackTrace();
            break;
         }
      }
   }
   
   public static void main(String [] args) {
      int port = Integer.parseInt(args[0]);
      try {
         Thread t = new GreetingServer(port);
         t.start();
      }catch(IOException e) {
         e.printStackTrace();
      }
   }
}