package lab4.exercitii;

import java.util.Scanner;

public class Lab4Ex3 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String string = in.next();
        if (string.length() < 2) {
            System.out.println("NO");
        } else {
            String beginning = string.substring(0, 2);
            if (string.endsWith(beginning) || string.endsWith(new StringBuffer(beginning).reverse().toString())) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
}
