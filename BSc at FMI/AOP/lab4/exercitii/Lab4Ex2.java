package lab4.exercitii;

import java.util.*;

class StringExtra {
    static boolean isPalindrom(String string) {
        String reversed = new StringBuffer(string).reverse().toString();
        return (string.compareTo(reversed) == 0);
    }
}

public class Lab4Ex2 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String string = in.next();
        if (StringExtra.isPalindrom(string)) {
            System.out.println("Palindrom");
        } else {
            System.out.println("Not palindrom");
        }
    }
}
