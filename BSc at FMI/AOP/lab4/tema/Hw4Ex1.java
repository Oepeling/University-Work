package lab4.tema;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Hw4Ex1 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String a = in.nextLine();
        String b = in.nextLine();
        if (areAnagrams(a, b)) {
            System.out.println("\"" + a + "\" si \"" + b + "\" sunt anagrame");
        } else {
            System.out.println("\"" + a + "\" si \"" + b + "\" nu sunt anagrame");
        }
    }

    private static boolean areAnagrams(String a, String b) {
        a = a.toLowerCase();
        Map<Character, Integer> a_char = new HashMap<Character, Integer>();
        for (int i = 0; i < a.length(); i++) {
            a_char.compute(a.charAt(i), (k, v) -> (v == null) ? 1 : v + 1);
        }

        b = b.toLowerCase();
        Map<Character, Integer> b_char = new HashMap<Character, Integer>();
        for (int i = 0; i < b.length(); i++) {
            b_char.compute(b.charAt(i), (k, v) -> (v == null) ? 1 : v + 1);
        }

        for (char i = 'a'; i <= 'z'; i++) {
            if (a_char.get(i) != b_char.get(i)) {
                return false;
            }
        }
        return true;
    }
}
