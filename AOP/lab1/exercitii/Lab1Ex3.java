package lab1.exercitii;
import java.util.*;

public class Lab1Ex3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        for (int d = 1; d <= n; d++) {
            if (n % d == 0) {
                System.out.print(d + " ");
            }
        }
    }
}