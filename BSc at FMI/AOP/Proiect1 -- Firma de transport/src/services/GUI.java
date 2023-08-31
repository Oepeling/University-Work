package services;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI extends JFrame implements ActionListener {
    private TransportCompanyService tcs;

    public GUI() {
        tcs = TransportCompanyService.getInstance();

        String[] buttonLabels = "Show settlements&Show roads&Show routes&Show vehicles&Show vehicles on route&Exit".split("&");

        for (String label : buttonLabels) {
            JButton button = new JButton((label));
            if ("Exit".equals(label)) {
                button.setBackground(Color.red);
                button.setForeground(Color.darkGray);
                button.setBorderPainted(true);
            } else {
                button.setBackground(Color.gray);
                button.setForeground(Color.darkGray);
            }
            button.setOpaque(true);
            button.addActionListener(this);
            add(button);
        }

        setLayout(new GridLayout(3, 2));
        setSize(500, 500);
        setVisible(true);
        setBackground(Color.gray);
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
