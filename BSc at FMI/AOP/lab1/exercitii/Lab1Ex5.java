package lab1.exercitii;
import java.util.*;

class Numbers {
    public static boolean IsPrime(int n) {
        if (n % 2 == 0 || n == 1) {
            return false;
        }

        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }
}

public class Lab1Ex5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(Numbers.IsPrime(n));
    }
}