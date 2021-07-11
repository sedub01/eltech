package design;
import java.awt.event.ActionListener;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.BorderLayout;
import team.Team;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
/** Кнопка для удаления игрока*/
public class deleteButton implements ActionListener{
    private static final Logger DBlog = LogManager.getLogger(deleteButton.class);
    private MyModel model;
    private JTable players;
    private Team theBest;
    private JFrame owner;
    /**
     * 
     * @param model Отображаемая таблица
     * @param theBest Команда
     * @param owner Предыдущий фрейм
     */
    deleteButton(MyModel model, Team theBest, JFrame owner, JTable players){
        this.model = model;
        this.theBest = theBest;
        this.owner = owner;
        this.players = players;
    }
    public void actionPerformed(ActionEvent e){
        DBlog.info("Opening deleting frame");
        try{
            int selected = players.getSelectedRow();
            model.removeRow(selected);
            theBest.delete(theBest.firstID()+selected);
            while (model.getRowCount()>0) model.removeRow(0);
            model.showTable(theBest);
            JOptionPane.showMessageDialog(owner, "Игрок удален", "", 
            JOptionPane.INFORMATION_MESSAGE);
            DBlog.info("Player was deleted");
        }
        catch(ArrayIndexOutOfBoundsException ex){
            JDialog deleteBox = new JDialog(owner, "Выгнать игрока", true);
            JTextField smallField = new JTextField(4);
            smallField.setHorizontalAlignment(JTextField.RIGHT);
            JPanel content = new JPanel();
            JLabel text = new JLabel("Введите ID игрока: ");
            smallField.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    try{
                        DBlog.info("Preparing for deleting player");
                        int ID = Integer.parseInt(smallField.getText());
                        theBest.find(ID);
                        theBest.delete(ID);
                        model.removeRow(ID-theBest.firstID());
                        deleteBox.dispose();
                        //так как ID в структуре меняется, а на выводе нет, 
                        //то таблицу нужно выводить заново
                        while (model.getRowCount()>0) model.removeRow(0);
                        model.showTable(theBest);

                        JOptionPane.showMessageDialog(deleteBox, "Игрок удален", "", 
                        JOptionPane.INFORMATION_MESSAGE);
                        DBlog.info("Player was deleted");
                    }
                    catch(NullPointerException exNull){
                        DBlog.error("Player not found");
                        JOptionPane.showMessageDialog(deleteBox, "Нет такого игрока", "", 
                        JOptionPane.ERROR_MESSAGE);
                    }
                    catch(NumberFormatException exNum){
                        DBlog.error("Characters instead of digits");
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
        DBlog.info("Closing deleting frame");
    }
}
