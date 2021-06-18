package design;

import javax.swing.table.DefaultTableModel;
import team.*;
/**
 * Класс был создан для того, чтобы в класс {@code DefaultTableModel}
 * добавить функцию вывода информации об игроках
 */
public class MyModel extends DefaultTableModel implements IRoles {
    MyModel(String[][] data, String[] columns){super(data, columns);}
    public void showTable(Team theBest){
        for (int i = 0; i<theBest.getSizeTeam(); ++i){
            String[] buf = new String[8];
            Footballer boy = theBest.find(theBest.firstID()+i);
            buf[0] = Integer.toString(boy.getID());
            buf[1] = boy.getName();
            buf[2] = boy.getLastName();
            buf[3] = roles[boy.getRole()];
            buf[4] = boy.getClub();
            buf[5] = boy.getCity();
            buf[6] = Integer.toString(boy.getGoals());
            buf[7] = Integer.toString(boy.getSalary());
            addRow(buf);
        }
    }
}
