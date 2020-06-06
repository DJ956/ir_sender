import java.io.ByteArrayOutputStream;
import java.net.Socket;

public class Main {

	//format TYPE:DATA
	public static void main(String[] args) {
		// TODO 自動生成されたメソッド・スタブ

		final String data = "0:010101010101101011110001010010000110100010001011";
		//final String data = "0:101010100101101010001111000100100001011011010001";

		try(var socket = new Socket("192.168.0.15", 1234);
			var memory = new ByteArrayOutputStream();) {
			System.out.println("Connected to " + socket.getInetAddress());

			var output = socket.getOutputStream();

			output.write(data.getBytes());
			output.flush();

			var input = socket.getInputStream();

			int ch;
			byte[] buffer = new byte[1024];
			while((ch = input.read(buffer)) > 0) {
				memory.write(buffer, 0, ch);
			}

			var result = new String(memory.toByteArray());
			System.out.println("recv:" + result);

		}catch(Exception ex) {
			ex.printStackTrace();
		}
	}

}
