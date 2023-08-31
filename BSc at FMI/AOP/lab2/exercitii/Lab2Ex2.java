package lab2.exercitii;

import java.util.*;

public class Lab2Ex2 {
    public static int[] append(int[] elements, int element) {
        int[] newArray = Arrays.copyOf(elements, elements.length + 1);
        newArray[elements.length] = element;

        return newArray;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] pare = new int[0];
        int[] impare = new int[0];


        for (int i = 0; i < n; i++) {
            int x = sc.nextInt();
            if (x % 2 == 0) {
                pare = append(pare, x);
            } else {
                impare = append(impare, x);
            }
        }

        if (pare.length > impare.length) {
            System.out.println("Mai multe pare");
        } else if (pare.length == impare.length) {
            System.out.println("La fel de multe");
        } else {
            System.out.println("Mai multe impare");
        }
    }
}
