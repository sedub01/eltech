package design;

import team.*;
import exceptions.*;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.*;
import javax.swing.JFrame;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import javax.swing.*;
/**
 * Кнопка добавления игрока
 */
public class addButton implements ActionListener, IRoles{
    private static final Logger ABlog = LogManager.getLogger(addButton.class);
    private JFrame owner;
    private Team theBest;
    private MyModel model;
    /**
     * Просто конструктор
     * @param owner Окно, откуда появился этот фрейм
     * @param theBest Команда
     * @param model Отображаемая таблица
     */
    addButton(JFrame owner, Team theBest, MyModel model){
        this.owner = owner;
        this.theBest = theBest;
        this.model = model;
    }
    public void actionPerformed(ActionEvent e){
        ABlog.info("Adding new player frame opened");
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
                    ABlog.info("Trying to add new player");
                    Footballer boy = new Footballer(theBest.lastID()+1, newName.getText().trim(), newLastName.getText().trim(), 
                        newClub.getText().trim(), newCity.getText().trim(), Integer.parseInt(newGoals.getText().trim()), 
                        Integer.parseInt(newSalary.getText().trim()), neededRoleInt);

                    // Footballer boy = new Footballer();
                    // boy.setName(newName.getText().trim());
                    // boy.setLastName(newLastName.getText().trim());
                    // boy.setClub(newClub.getText().trim());
                    // boy.setCity(newCity.getText().trim());
                    // boy.setGoals(Integer.parseInt(newGoals.getText().trim()));
                    // boy.setSalary(Integer.parseInt(newSalary.getText().trim()));
                    // boy.setRole(neededRoleInt);

                    boy.isAllRight();
                    theBest.addFootballer(boy);
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
                    ABlog.info("New player was added");
                }
                catch(NumberFormatException exNum){
                    ABlog.error("Characters instead of digits");
                    JOptionPane.showMessageDialog(addBox, "Некорректное(ые) число(а)", "", 
                    JOptionPane.ERROR_MESSAGE);
                }
                catch(IllegalArgumentException exCity){
                    ABlog.error("Wrong city");
                    JOptionPane.showMessageDialog(addBox, exCity.getMessage(), "", 
                    JOptionPane.ERROR_MESSAGE);
                }
                catch(ArithmeticException exClub){
                    ABlog.error("Wrong club");
                    JOptionPane.showMessageDialog(addBox, exClub.getMessage(), "", 
                    JOptionPane.ERROR_MESSAGE);
                }
                catch(WrongNameException exName){
                    ABlog.error("Wrong name");
                    JOptionPane.showMessageDialog(addBox, exName.getMessage(), "", 
                    JOptionPane.ERROR_MESSAGE);
                }
                catch(WrongLastNameException exLName){
                    ABlog.error("Wrong last name");
                    JOptionPane.showMessageDialog(addBox, exLName.getMessage(), "", 
                    JOptionPane.ERROR_MESSAGE);
                }
                
            }
        });

        addBox.setContentPane(commonPanel);
        addBox.setSize(235, 360);
        addBox.setResizable(false);
        addBox.setLocationRelativeTo(null);
        addBox.setVisible(true);
        ABlog.info("Adding new player frame closed");
    }
}
