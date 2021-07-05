/**Пакет, содержащий в себе графический интерфейс */
package design;
import java.awt.event.ActionListener;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.BorderLayout;

import team.Footballer;
import team.Team;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
/**Вывод информации о конкретном футболисте*/
public class foutButton implements ActionListener{
    /**Логгер для окон */
    private static final Logger FOlog = LogManager.getLogger(foutButton.class);
    private JTable players;
    /**Команда */
    private Team theBest;
    /**Владелец фрейма */
    private JFrame owner;
    /**Фрейм с введением ID игрока для поиска */
    JDialog infoBox;
    /**Текстовое поле для ввода */
    JTextField textField;
    /**Панель с контентом */
    JPanel content;
    /**Надпись слева от текстового поля */
    JLabel text;
    /**Находимый футболист */
    Footballer boy;
    foutButton(Team theBest, JFrame owner, JTable players){
        this.theBest = theBest;
        this.owner = owner;
        this.players = players;
    }
    public void actionPerformed(ActionEvent e){
        FOlog.info("Frame was created");
        try{
            int selected = players.getSelectedRow();
            Footballer boy = theBest.find(theBest.firstID()+selected);
            JOptionPane.showMessageDialog(owner, boy.info(), boy.getName()+" "+boy.getLastName(), 
            JOptionPane.INFORMATION_MESSAGE);
            FOlog.info("Gamer found");
        }
        catch(NullPointerException ex){
            infoBox = new JDialog(owner, "Информация об игроке", true);
            textField = new JTextField(4);
            textField.setHorizontalAlignment(JTextField.RIGHT);
            content = new JPanel();
            text = new JLabel("Введите ID игрока: ");
            textField.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    try{
                        FOlog.info("Trying to find gamer");
                        boy = theBest.find(Integer.parseInt(textField.getText().trim()));
                        infoBox.dispose();
                        JOptionPane.showMessageDialog(infoBox, boy.info(), boy.getName()+" "+boy.getLastName(), 
                        JOptionPane.INFORMATION_MESSAGE);
                        FOlog.info("Gamer found");
                    }
                    catch(NullPointerException ex){
                        JOptionPane.showMessageDialog(infoBox, "Нет такого игрока", "", 
                        JOptionPane.ERROR_MESSAGE);
                        FOlog.error("Gamer not found");
                    }
                    catch(NumberFormatException exNum){
                        FOlog.error("Characters instead of digits");
                        JOptionPane.showMessageDialog(infoBox, "Некорректные данные", "", 
                        JOptionPane.ERROR_MESSAGE);
                    }
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
        

        FOlog.info("Frame closed");
    }
}
