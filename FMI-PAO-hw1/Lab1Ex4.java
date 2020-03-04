package lab1.exercitii;
import java.util.*;

class Numbers {
    public static int Factorial(int n) {
        int ans = 1;
        for (int i = 2; i <= n; i++) {
            ans *= i;
        }
        return ans;
    }
}

public class Lab1Ex4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(Numbers.Factorial(n));
    }
}