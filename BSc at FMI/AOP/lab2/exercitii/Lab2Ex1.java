package lab2.exercitii;

import java.util.*;

public class Lab2Ex1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] note = new int[n];

        for (int i = 0, x = sc.nextInt(); (x != -1) && (i < n); i++, x = sc.nextInt()) {
            note[i] = x;
        }

        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += note[i];
        }

        System.out.println((float) sum / n);
    }
}
