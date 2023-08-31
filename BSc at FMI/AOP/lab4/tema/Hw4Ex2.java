package lab4.tema;

import java.util.Iterator;
import java.util.Scanner;
import java.util.Vector;

public class Hw4Ex2 {
    public static void main(String[] agrs) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        Vector<String> a = new Vector<String>();
        for (int i = 0; i < n; i++) {
            a.add(in.next());
        }

        Vector<String> b = new Vector<String>();
        for (Iterator<String> value = a.iterator(); value.hasNext();) {
            String curr = value.next();
            if (isPalindrom(curr)) {
                b.add(curr);
            }
        }

        String ans = "";
        for (Iterator<String> value = b.iterator(); value.hasNext();) {
            String curr = value.next();
            if (ans.length() < curr.length()) {
                ans = curr;
            }
        }
        System.out.println(ans);
    }

    static boolean isPalindrom(String string) {
        String reversed = new StringBuffer(string).reverse().toString();
        return (string.compareTo(reversed) == 0);
    }
}
