package services;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI extends JFrame implements ActionListener {
    private TransportCompanyService tcs;

    public GUI() {
        tcs = TransportCompanyService.getInstance();

        JButton button1 = new JButton("Show settlements");
        JButton button2 = new JButton("Show roads");
        JButton button3 = new JButton("Show routes");
        JButton button4 = new JButton("Show vehicles");
        JButton button5 = new JButton("Show vehicles on route");
        JButton button6 = new JButton("Exit");


        button1.addActionListener(this);
        button2.addActionListener(this);
        button3.addActionListener(this);
        button4.addActionListener(this);
        button5.addActionListener(this);
        button6.addActionListener(this);

        add(button1);
        add(button2);
        add(button3);
        add(button4);
        add(button5);
        add(button6);
        setLayout(new GridLayout(3, 2));
        setSize(500, 500);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        switch (action) {
            case "Show settlements":
                tcs.guiHandler(this, 1);
                break;
            case "Show roads":
                tcs.guiHandler(this, 2);
                break;
            case "Show routes":
                tcs.guiHandler(this, 3);
                break;
            case "Show vehicles":
                tcs.guiHandler(this, 4);
                break;
            case "Show vehicles on route":
                tcs.guiHandler(this, 5);
                break;
            case "Exit":
                tcs.guiHandler(this, 6);
                break;
        }
    }
}
