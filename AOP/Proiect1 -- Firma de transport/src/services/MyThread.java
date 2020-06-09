package services;

public class MyThread extends Thread {
    public void run() {
        new GUI();
    }
}
