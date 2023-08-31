package lab4.exercitii;

import java.util.*;

public class Lab4Ex1 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.next();
        System.out.println(getFirstUniqueChar(s));
    }

    private static char getFirstUniqueChar(String s) {
        HashSet<Character> char_set = new HashSet<Character>();

        char ans = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            char curr_char = s.charAt(i);
            if (!char_set.contains(curr_char)) {
                ans = curr_char;
                char_set.add(curr_char);
            }
        }

        return ans;
    }
}