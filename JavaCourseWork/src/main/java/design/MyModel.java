package design;

import javax.swing.table.DefaultTableModel;
import team.*;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
/**
 * Класс был создан для того, чтобы в класс {@code DefaultTableModel}
 * добавить функцию вывода информации об игроках
 */
public class MyModel extends DefaultTableModel implements IRoles {
    private static final Logger MMlog = LogManager.getLogger(MyModel.class);
    MyModel(String[][] data, String[] columns){super(data, columns);}
    public void showTable(Team theBest){
        MMlog.info("Finding gamers for creating table");
        for (Footballer boy : theBest.getFootballers()){
            String[] buf = new String[8];
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
        MMlog.info("Table was created");
    }
}
