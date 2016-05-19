 
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
 
/**
 * @author Crunchify.com
 */
 
public class HttpController {
 
	public static void main(String[] args) {
		try {
			URL url = new URL("http://crunchify.com/");
			BufferedReader br = new BufferedReader(new InputStreamReader(url.openStream()));
			String strTemp = "";
			while (null != (strTemp = br.readLine())) {
				System.out.println(strTemp);
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}
