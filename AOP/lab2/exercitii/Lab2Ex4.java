package lab2.exercitii;

import java.io.PrintStream;
import java.util.*;
import java.util.regex.Pattern;

class Student {
    private String name;
    private float grade;

    Student() {
        this.name = "";
        this.grade = 0;
    }

    Student(String name, float grade) {
        this.name = name;
        this.grade = grade;
    }

    public float getGrade() {
        return grade;
    }

    public void setGrade(float grade) {
        this.grade = grade;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void read(Scanner in) {
        this.name = in.next(Pattern.compile("[^0-9]*"));
        this.grade = in.nextFloat();
    }

    public void print(PrintStream out) {
        out.println(this.name + this.grade);
    }
}

public class Lab2Ex4 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        Student[] v = new Student[n];

        for (int i = 0; i < n; i++) {
            v[i].read(in);
        }

        for (int i = 0; i < n; i++) {
            v[i].print(System.out);
        }
    }
}
