import java.io.*;
import java.net.*;

public class _2_server {
    public static void main(String[] args)throws IOException,EOFException{
        ServerSocket ss = new ServerSocket(6060);
        Socket s = ss.accept();
        System.out.println("Connected\n");
        DataInputStream dis = new DataInputStream(s.getInputStream());
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());
        dos.writeUTF("Hello from server");
        //dis = new DataInputStream(System.in);
        String line = dis.readUTF();
        System.out.println(line);
        System.out.println("sent");
        dos.flush();
    }
}
