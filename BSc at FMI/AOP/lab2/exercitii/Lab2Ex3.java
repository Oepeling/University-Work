package lab2.exercitii;

import java.io.PrintStream;

class Pet {
    private String name;
    private String type;
    private int age;

    public Pet() {
        this.name = "";
        this.type = "";
        this.age = 0;
    }

    public Pet(String name, String type, int age) {
        this.name = name;
        this.type = type;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void increaseAge() {
        this.age++;
    }

    public void increaseAge(int by_what) {
        this.age += by_what;
    }

    public void printName(PrintStream out) {
        out.println("Name: " + this.name);
    }

    public void printType(PrintStream out) {
        out.println("Type: " + this.type);
    }

    public void printAge(PrintStream out) {
        out.println("Age: " + this.age);
    }

    public void print(PrintStream out) {
        this.printName(out);
        this.printType(out);
        this.printAge(out);
        out.println();
    }
}

public class Lab2Ex3 {
    public static void main(String[] args) {
        Pet my_cat = new Pet("Poso", "cat", 15);
        my_cat.print(System.out);
        my_cat.increaseAge();
        my_cat.print(System.out);

        Pet my_dog = new Pet();
        my_dog.setName("Chelsea");
        my_dog.setType("dog");
        my_dog.print(System.out);
        my_dog.increaseAge(5);
        my_dog.printAge(System.out);
    }
}
