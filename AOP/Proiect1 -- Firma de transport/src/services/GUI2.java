package services;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI2 extends JFrame implements ActionListener {
    private TransportCompanyService tcs;

    public GUI2(String[] s) {
        tcs = TransportCompanyService.getInstance();
        setLayout(new BorderLayout());
        JButton button = new JButton("Back to menu");
        JScrollPane jScrollPane = new JScrollPane();
        button.addActionListener(this);
        JList list = new JList(s);
        jScrollPane.setViewportView(list);
        add(jScrollPane, BorderLayout.CENTER);
        add(button, BorderLayout.SOUTH);

        setSize(500, 500);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        tcs.guiHandler(this, 0);
    }
}
