package design;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionEvent;
import java.awt.*;

import team.Calendar;
import team.Team;

public class calButton implements ActionListener {
    private List<Calendar> lst;
    private JFrame owner;
    calButton(Team theBest, JFrame owner){
        this.lst = theBest.getCal();
        this.owner = owner;
    }
    public void actionPerformed(ActionEvent e){
        JDialog calBox = new JDialog(owner,"Календарь игр", true);
        calBox.setIconImage(new ImageIcon("./img/calendar.png").getImage());
        String[] cols = {"Дата", "Счет сборной", "Счет противника"};
        String[][] data = new String[0][];
        DefaultTableModel newModel = new DefaultTableModel(data, cols);
        JButton addDateButton = new JButton("Добавить дату");
        JButton deleteDateButton = new JButton("Удалить дату");
        //JButton changeDateButton = new JButton("Изменить дату");
        for (Calendar cal:lst) {
            String buf[] = new String[3];
            buf[0] = cal.getDate();
            buf[1] = Integer.toString(cal.getWins());
            buf[2] = Integer.toString(cal.getLosses());
            newModel.addRow(buf);
        }
        JTable dates = new JTable(newModel){
            @Override
            public boolean isCellEditable(int row, int column){ return false; }
        };
        JScrollPane newScroll = new JScrollPane(dates);
        calBox.add(newScroll, BorderLayout.CENTER);
        deleteDateButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                try{
                    int selected = dates.getSelectedRow();
                    newModel.removeRow(selected);
                    lst.remove(selected);
                }
                catch(Exception ex){
                    JOptionPane.showMessageDialog(calBox, "Для начала выберите строку", "Вызов исключения", 
                    JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        addDateButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                JDialog addDateBox = new JDialog(calBox, "Добавление даты", true);
                JPanel commonPanel = new JPanel();
                JTextField newDate = new JTextField(10);
                JTextField newWins = new JTextField(4);
                JTextField newLosses = new JTextField(4);
                JButton addDateButton = new JButton("Добавить");

                JLabel newDateText = new JLabel("Введите дату: ");
                JLabel newWinsText = new JLabel("Введите счет сборной: ");
                JLabel newLossesText = new JLabel("Введите счет противника: ");
                
                commonPanel.add(newDateText, BorderLayout.NORTH);
                commonPanel.add(newDate, BorderLayout.AFTER_LINE_ENDS);
                commonPanel.add(newWinsText, BorderLayout.AFTER_LAST_LINE);
                commonPanel.add(newWins, BorderLayout.AFTER_LINE_ENDS);
                commonPanel.add(newLossesText, BorderLayout.AFTER_LAST_LINE);
                commonPanel.add(newLosses, BorderLayout.AFTER_LINE_ENDS);
                commonPanel.add(addDateButton, BorderLayout.SOUTH);

                addDateButton.addActionListener(new ActionListener(){
                    public void actionPerformed(ActionEvent e){
                        Calendar addedDate = new Calendar(newDate.getText(), 
                            Integer.parseInt(newWins.getText()), 
                            Integer.parseInt(newLosses.getText()));
                        lst.add(addedDate);
                        JOptionPane.showMessageDialog(addDateBox, "Дата добавлена", "", 
                        JOptionPane.INFORMATION_MESSAGE);
                        addDateBox.dispose();
                        String[] buf = {addedDate.getDate(), 
                            Integer.toString(addedDate.getWins()), 
                            Integer.toString(addedDate.getLosses())};
                        newModel.addRow(buf);
                    }
                });

                addDateBox.setContentPane(commonPanel);
                addDateBox.setSize(250, 150);
                addDateBox.setResizable(false);
                addDateBox.setLocationRelativeTo(null);
                addDateBox.setVisible(true);
            }
        });
        
        JPanel calPanel = new JPanel();
        calPanel.add(addDateButton);
        calPanel.add(deleteDateButton);
        //calPanel.add(changeDateButton);
        
        calBox.add(calPanel, BorderLayout.SOUTH);
        calBox.setAlwaysOnTop(true);
        calBox.setSize(300, 300);
        calBox.setResizable(false);
        calBox.setLocationRelativeTo(null);
        calBox.setVisible(true);
    }
    
}
