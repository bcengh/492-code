package gyroscope;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import com.fazecast.jSerialComm.*;
import javax.swing.*;

public class main {

	static SerialPort serialPort;
	private static double chooseTime = 0;
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		JFrame window = new JFrame();
		window.setTitle("Gyroscope info");
		
		window.setSize(400, 150);
		window.setLayout(new BorderLayout());
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		final JComboBox<String> portsBox = new JComboBox<String>();
		final JButton portButton = new JButton("Run");
		final JTextField timeField = new JTextField(5);
		JTextArea timeArea = new JTextArea(1, 25);
		timeArea.append("How long should data record? (in minutes)");
		timeArea.setEditable(false);
		JPanel southPanel = new JPanel();
		southPanel.add(timeArea);
		southPanel.add(timeField);
		window.add(southPanel, BorderLayout.SOUTH);
		JPanel northPanel = new JPanel();
		northPanel.add(portsBox);
		northPanel.add(portButton);
		northPanel.setVisible(true);
		window.add(northPanel, BorderLayout.NORTH);
		
		SerialPort ports[] = SerialPort.getCommPorts();
		
	    System.out.println("Type in a time period and press Enter. Then, select a port to connect to and press Run.");
	    for(int i = 0; i < ports.length; i++){
	    	portsBox.addItem(ports[i].getSystemPortName());
	    	
	    }
	    chooseTime = 0;
	    timeField.addActionListener(new ActionListener() {
	    	 
	           public void actionPerformed(ActionEvent e)
	            {
	                //Execute when button is pressed
	                System.out.println("You entered a value for time");
	                chooseTime = Double.parseDouble(timeField.getText());
	                //convert time from minutes to milliseconds
	         	    chooseTime = chooseTime * 60000;
	                System.out.println(chooseTime);
	            }
	        }); 
	    portButton.addActionListener(new ActionListener() {
 
           public void actionPerformed(ActionEvent e)
            {
                //Execute when button is pressed
                System.out.println("You clicked the button");
                serialPort = SerialPort.getCommPort(portsBox.getSelectedItem().toString());
        		serialPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 0, 0);
        		portButton.setText("running");
        		
        		if(serialPort.openPort()){
        	    	System.out.println("Opened the port");
        		} else{
        	    	System.out.println("Port did not open");
        	    	System.exit(0);
        	    }
        		BufferedReader data = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
        	    double timeSoFar = 0;
        	    String line = null;
        	    try {
        	    	PrintWriter pwriter = new PrintWriter("gyroInfo.txt", "UTF-8");
        	    	boolean firstLine = true;
        			while(((line = data.readLine()) != null) && (timeSoFar < chooseTime)){ //while(data.hasNextLine() && (timeSoFar < chooseTime)){
        				try{
        					//don't print the first line to a file, because it is often an incomplete line
        					if(firstLine){
        						System.out.println(line);
        						TimeUnit.MILLISECONDS.sleep(233);
            					timeSoFar = timeSoFar + 233;
            					firstLine = false;
        					}
        					else{
        						System.out.println(line);   //data.nextLine()
            					pwriter.print("Seconds: " + Math.round((timeSoFar / 1000.0) * 100.0) / 100.0 + " | ");
            					pwriter.println(line);
            					TimeUnit.MILLISECONDS.sleep(233);
            					timeSoFar = timeSoFar + 233;
            					
        					}
        				}
        				catch(Exception e2){}
        				
        			}
        			portButton.setText("Run");
        			pwriter.close();
        			serialPort.closePort();
        		} catch (IOException e1) {
        			System.out.println("delay is not long enough");
        		}
        	   System.out.println("done");
            }
        });      
	    
	    window.setVisible(true);
	}
}
