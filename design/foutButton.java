package design;
import java.awt.event.ActionListener;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.BorderLayout;

import team.Footballer;
import team.Team;

public class foutButton implements ActionListener{
    private Team theBest;
    private JFrame owner;
    foutButton(Team theBest, JFrame owner){
        this.theBest = theBest;
        this.owner = owner;
    }
    public void actionPerformed(ActionEvent e){
        JDialog infoBox = new JDialog(owner, "Информация об игроке", true);
        JTextField textField = new JTextField(4);
        textField.setHorizontalAlignment(JTextField.RIGHT);
        JPanel content = new JPanel();
        JLabel text = new JLabel("Введите ID игрока: ");
        textField.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                int ID = Integer.parseInt(textField.getText());
                Footballer boy = theBest.find(ID);
                infoBox.dispose();
                JOptionPane.showMessageDialog(infoBox, boy.info(), boy.getName()+" "+boy.getLastName(), 
                JOptionPane.INFORMATION_MESSAGE);
            }
        });
        content.add(text, BorderLayout.NORTH);
        content.add(textField);
        infoBox.setContentPane(content);
        infoBox.setSize(300, 130);
        infoBox.setResizable(false);
        infoBox.setLocationRelativeTo(null);
        infoBox.setVisible(true);
    }
}
