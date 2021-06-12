package design;

import team.*;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.*;
import javax.swing.JFrame;
import javax.swing.*;

public class addButton implements ActionListener, IRoles{
    private JFrame owner;
    private Team theBest;
    private MyModel model;
    addButton(JFrame owner, Team theBest, MyModel model){
        this.owner = owner;
        this.theBest = theBest;
        this.model = model;
    }
    public void actionPerformed(ActionEvent e){
        JPanel commonPanel = new JPanel();

        JDialog addBox = new JDialog(owner, "Добавление игрока", true);
        JLabel boyID = new JLabel("ID: "+Integer.toString(theBest.lastID()+1));
        JLabel boyName = new JLabel("Имя:");
        JLabel boyLastName = new JLabel("Фамилия:");
        JLabel boyRole = new JLabel("Специализация:");
        JLabel boyClub = new JLabel("Клуб:");
        JLabel boyCity = new JLabel("Город:");
        JLabel boyGoals = new JLabel("Кол-во голов:");
        JLabel boySalary = new JLabel("Зарплата:");

        JTextField newName = new JTextField(12);
        JTextField newLastName = new JTextField(12);
        JComboBox<String> newRole = new JComboBox<String>(new String[]{
            roles[0], roles[1], roles[2], roles[3]
        });
        JTextField newClub = new JTextField(12);
        JTextField newCity = new JTextField(12);
        JTextField newGoals = new JTextField(12);
        JTextField newSalary = new JTextField(12);

        JPanel IDPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        JPanel namePanel = new JPanel();
        JPanel lastNamePanel = new JPanel();
        JPanel rolePanel = new JPanel();
        JPanel clubPanel = new JPanel();
        JPanel cityPanel = new JPanel();
        JPanel goalsPanel = new JPanel();
        JPanel salaryPanel = new JPanel();

        JButton addPlayer = new JButton("Добавить");
        
        IDPanel.add(boyID, "North");
        namePanel.add(boyName);
        namePanel.add(newName);
        lastNamePanel.add(boyLastName);
        lastNamePanel.add(newLastName);
        rolePanel.add(boyRole);
        rolePanel.add(newRole);
        clubPanel.add(boyClub);
        clubPanel.add(newClub);
        cityPanel.add(boyCity);
        cityPanel.add(newCity);
        goalsPanel.add(boyGoals);
        goalsPanel.add(newGoals);
        salaryPanel.add(boySalary);
        salaryPanel.add(newSalary);

        commonPanel.add(IDPanel);
        commonPanel.add(namePanel);
        commonPanel.add(lastNamePanel);
        commonPanel.add(rolePanel);
        commonPanel.add(clubPanel);
        commonPanel.add(cityPanel);
        commonPanel.add(goalsPanel);
        commonPanel.add(salaryPanel);
        commonPanel.add(addPlayer, BorderLayout.NORTH);

        //Добавили панели - теперь добавляем игрока
        addPlayer.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                String neededRole = (String)newRole.getSelectedItem();
                int neededRoleInt=-1;
                if (neededRole.equals(roles[0])) neededRoleInt = 0;
                else if (neededRole.equals(roles[1])) neededRoleInt = 1;
                else if (neededRole.equals(roles[2])) neededRoleInt = 2;
                else if (neededRole.equals(roles[3])) neededRoleInt = 3;
                try{
                    Footballer boy = new Footballer(theBest.lastID()+1, newName.getText(), newLastName.getText(), 
                        newClub.getText(), newCity.getText(), Integer.parseInt(newGoals.getText()), 
                        Integer.parseInt(newSalary.getText()), neededRoleInt);
                    boy.isAllRight();
                    theBest.add(boy);
                    model.addRow(new String[]{
                        Integer.toString(boy.getID()), 
                        boy.getName(), 
                        boy.getLastName(),
                        roles[boy.getRole()], 
                        boy.getClub(),
                        boy.getCity(), 
                        Integer.toString(boy.getGoals()),
                        Integer.toString(boy.getSalary())
                    });
                    JOptionPane.showMessageDialog(addBox, "Игрок добавлен", "", 
                    JOptionPane.INFORMATION_MESSAGE);
                    addBox.dispose();
                }
                catch(NumberFormatException exNum){
                    JOptionPane.showMessageDialog(addBox, "В одном из чисел\nобнаружены буквы", "", 
                    JOptionPane.ERROR_MESSAGE);
                }
                catch(IllegalArgumentException exArg){
                    JOptionPane.showMessageDialog(addBox, "В одной из строк\nобнаружено число", "", 
                    JOptionPane.ERROR_MESSAGE);
                }
                
            }
        });

        addBox.setContentPane(commonPanel);
        addBox.setSize(235, 360);
        addBox.setResizable(false);
        addBox.setLocationRelativeTo(null);
        addBox.setVisible(true);
    }
    
}
