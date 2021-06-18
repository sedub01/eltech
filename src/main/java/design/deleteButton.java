package design;
import java.awt.event.ActionListener;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.BorderLayout;
import team.Team;

public class deleteButton implements ActionListener{
    private MyModel model;
    private Team theBest;
    private JFrame owner;
    deleteButton(MyModel model, Team theBest, JFrame owner){
        this.model = model;
        this.theBest = theBest;
        this.owner = owner;
    }
    public void actionPerformed(ActionEvent e){
        JDialog deleteBox = new JDialog(owner, "Выгнать игрока", true);
        JTextField smallField = new JTextField(4);
        smallField.setHorizontalAlignment(JTextField.RIGHT);
        JPanel content = new JPanel();
        JLabel text = new JLabel("Введите ID игрока: ");
                
        smallField.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //System.out.println("Hello thrrrr");
                try{
                    int ID = Integer.parseInt(smallField.getText());
                    theBest.find(ID);
                    theBest.delete(ID);
                    JOptionPane.showMessageDialog(deleteBox, "Игрок удален", "", 
                    JOptionPane.INFORMATION_MESSAGE);
                    model.removeRow(ID-theBest.firstID());
                    deleteBox.dispose();
                    //так как ID в структуре меняется, а на выводе нет, 
                    //то таблицу нужно выводить заново
                    while (model.getRowCount()>0) model.removeRow(0);
                    model.showTable(theBest);
                }
                catch(NullPointerException exNull){
                    JOptionPane.showMessageDialog(deleteBox, "Нет такого игрока", "", 
                    JOptionPane.ERROR_MESSAGE);
                }
                catch(NumberFormatException exNum){
                    JOptionPane.showMessageDialog(deleteBox, "Некорректные данные", "", 
                    JOptionPane.ERROR_MESSAGE);
                }
            }
        });
                
        content.add(text, BorderLayout.NORTH);
        content.add(smallField);
        deleteBox.setContentPane(content);
        deleteBox.setSize(300, 130);
        deleteBox.setResizable(false);
        deleteBox.setLocationRelativeTo(null);;
        deleteBox.setVisible(true);
    }
}
