import java.io.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Reliability { //main class
public static void main(String [] args){ 
    int b,n;
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    try{
    b= Integer.parseInt(br.readLine());
    n= Integer.parseInt(br.readLine());
    System.out.println("Budget: "+b);
    System.out.println("Number Machines: "+n);
} catch(IOException i){
   System.out.println(i);
}
}
}

