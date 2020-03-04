package lab1.exercitii;
import java.util.*;

public class Lab1Ex7 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        int a = 1, b = 1, c = 1;
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }

        System.out.println(c);
    }
}