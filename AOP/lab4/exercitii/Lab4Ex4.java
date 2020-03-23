package lab4.exercitii;

import java.util.Scanner;

public class Lab4Ex4 {
    static boolean isIntegerSeries(String string) {
        for (int i = 0; i < string.length(); i++) {
            if (string.charAt(i) == ' ') {
                continue;
            } else {
                if (string.charAt(i) == '-') {
                    i++;
                }
                while (i < string.length() && Character.isDigit(string.charAt(i))) {
                    i++;
                }

                if (i < string.length() && string.charAt(i) != ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String line = in.nextLine();
        if (isIntegerSeries(line)) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    }
}
