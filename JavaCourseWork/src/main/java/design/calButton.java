package design;
import java.awt.event.ActionListener;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.*;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import team.Calendar;
import team.Team;
/**
 * Кнопка, вызывающая календарь
 */
public class calButton implements ActionListener {
    private static final Logger Callog = LogManager.getLogger(calButton.class);
    private Team theBest;
    private JFrame owner;
    /**
     * 
     * @param theBest Команда
     * @param owner Предыдущий фрейм
     */
    calButton(Team theBest, JFrame owner){
       
        this.theBest = theBest;
        this.owner = owner;
    }
    public void actionPerformed(ActionEvent e){
        Callog.info("Calendar frame was opened");
        JTable dates;
        MyModel newModel;
        JButton addDateButton, deleteDateButton;
        JScrollPane newScroll;
        JDialog calBox = new JDialog(owner,"Календарь игр", true);
        String[] cols = {"Дата", "Счет сборной", "Счет противника"};
        String[][] data = new String[0][];
        newModel = new MyModel(data, cols){
            @Override
            /**Вывод информации в таблицу, не более того */
            public void showTable(Team theBest){
                for (Calendar cal : theBest.getCal()){
                    String[] buf = new String[3];
                    buf[0] = cal.getDate();
                    buf[1] = Integer.toString(cal.getWins());
                    buf[2] = Integer.toString(cal.getLosses());
                    addRow(buf);
                }
            }
        };
        addDateButton = new JButton("Добавить дату");
        deleteDateButton = new JButton("Удалить дату");
        dates = new JTable(newModel){
            @Override
            public boolean isCellEditable(int row, int column){ return false; }
        };
        newScroll = new JScrollPane(dates);

        Thread calThread = new Thread(new Runnable(){
            public void run(){
                Callog.info("Creating the table");
                calBox.setIconImage(new ImageIcon("./src/main/resources/img/calendar.png").getImage());
                theBest.addDates(newModel);
                Callog.info("Table was created");
            }
        });
        calThread.start();
        
        calBox.add(newScroll, BorderLayout.CENTER);
        /** Удаление даты из календаря */
        deleteDateButton.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                try{
                    Callog.info("Trying delete date");
                    int selected = dates.getSelectedRow();
                    newModel.removeRow(selected);
                    
                    theBest.deleteDate(selected);
                    Callog.info("Date was deleted");
                }
                catch(Exception ex){
                    Callog.error("User didn't choose the date");
                    JOptionPane.showMessageDialog(calBox, "Для начала выберите строку", "Вызов исключения", 
                    JOptionPane.INFORMATION_MESSAGE);
                }
            }
        });
        addDateButton.addActionListener(new ActionListener(){
            /** Добавление даты в календарь*/
            public void actionPerformed(ActionEvent e){
                Callog.info("New date frame opened");
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
                        Calendar addedDate;
                        try{
                            Callog.info("Trying add new date");
                            addedDate = new Calendar(newDate.getText().trim(), 
                            Integer.parseInt(newWins.getText().trim()), 
                            Integer.parseInt(newLosses.getText().trim()));
                            addedDate.isDateRight();
                            //lst.add(addedDate);
                            theBest.addDate(addedDate);
                            JOptionPane.showMessageDialog(addDateBox, "Дата добавлена", "", 
                            JOptionPane.INFORMATION_MESSAGE);
                            while (newModel.getRowCount()>0) newModel.removeRow(0);
                            newModel.showTable(theBest);
                            addDateBox.dispose();
                            Callog.info("Date was added");
                        }
                        catch(NumberFormatException exNum){
                            Callog.error("Characters instead of digits");
                            JOptionPane.showMessageDialog(addDateBox, "Некорректные числовые данные", "", 
                            JOptionPane.ERROR_MESSAGE);
                        }
                        catch(IllegalArgumentException exArg){
                            Callog.error("Wrong date format");
                            JOptionPane.showMessageDialog(addDateBox, "Неправильная дата", "", 
                            JOptionPane.ERROR_MESSAGE);
                        }
                        catch(ArrayIndexOutOfBoundsException exArg){
                            Callog.error("Wrong date format");
                            JOptionPane.showMessageDialog(addDateBox, "Введите дату полностью", "", 
                            JOptionPane.ERROR_MESSAGE);
                        }
                    }
                    
                    
                });

                addDateBox.setContentPane(commonPanel);
                addDateBox.setSize(250, 150);
                addDateBox.setResizable(false);
                addDateBox.setLocationRelativeTo(null);
                addDateBox.setVisible(true);
                Callog.info("New date frame closed");
            }
        });
        
        JPanel calPanel = new JPanel();
        calPanel.add(addDateButton);
        calPanel.add(deleteDateButton);
        
        calBox.add(calPanel, BorderLayout.SOUTH);
        calBox.setAlwaysOnTop(true);
        calBox.setSize(300, 300);
        calBox.setResizable(false);
        calBox.setLocationRelativeTo(null);
        calBox.setVisible(true);
        Callog.info("Calendar frame was closed");
    }
    
}
