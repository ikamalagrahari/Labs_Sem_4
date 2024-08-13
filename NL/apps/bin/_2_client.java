import java.io.*;
import java.net.*;

public class _2_client {
    public static void main(String[] args)throws IOException,EOFException{
        Socket s = new Socket("localhost", 6060);
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());
        DataInputStream dis = new DataInputStream(s.getInputStream());
        dos.writeUTF("hello from client on localhost");
        System.out.println("sent");
        String out = dis.readUTF();
        System.out.println(out);
        dos.flush();
        dos.close();
    }
}
