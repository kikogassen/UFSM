/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package randomnumbers;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author kikog
 */
public class main {
    
    public static void writeInFile(String filename, ArrayList<Double> values){
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
            for (Double value: values){
                writer.append(String.format(Locale.US, "%.3f", value));
                if (values.indexOf(value) % 5 == 4) writer.append("\n");
                else writer.append(" ");
            }
            writer.flush();
            writer.close();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static ArrayList<Double> getRandomValues(float minutesOfSimulation, double lowerLimit, double upperLimit){
        ArrayList<Double> values = new ArrayList<>();
        double minutesTraveled = 0;
        while (minutesTraveled <= minutesOfSimulation){
            Double randomValue = (Math.random() * (upperLimit - lowerLimit)) + lowerLimit;
            minutesTraveled += randomValue;
            values.add(randomValue);
        }
        return values;
    }
    
    public static void main(String[] args) {
        writeInFile("attendance_clients.txt", getRandomValues(24*60, (double) 20/60, (double) 40/60));
        writeInFile("arrival_clients.txt", getRandomValues(24*60, (double) 0/60, (double) 60/60));
        writeInFile("queue_time.txt", getRandomValues(24 * 60, (double) 20/60, (double) 120/60));
    }
    
}
