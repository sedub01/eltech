package design;

import javax.swing.*;

import java.awt.*;
import java.awt.event.*;

//добавлю скролл и неизменяемую рамку
public class helpButton implements ActionListener, SwingConstants{
    //нужно создать отдельный логгер? Думаю, нет
    /**Окно со всем содержимым */
    private JDialog helpBox;
    /**Кнопка в самом конце*/
    private JButton OK;
    /** Скролл для движения вниз*/
    private JScrollPane scroll;
    /**Панель с контентом */
    private JPanel content;
    private JPanel superPanel;
    /** */
    private String[] strings;
    private JFrame owner;

    helpButton(JFrame owner){
        this.owner = owner;
    }

    public void actionPerformed(ActionEvent e){
        helpBox = new JDialog(owner, "Туториал", true);
        helpBox.setLayout(new BorderLayout());
        OK = new JButton("Я все понял");
        
        content = new JPanel();
        content.setLayout(new BoxLayout(content, BoxLayout.Y_AXIS));
        superPanel = new JPanel();
        superPanel.setLayout(new BorderLayout());
        //не добавлять BorderLayout!!!
        strings = new String[]{
            "<html><p style=\"margin-left: 30px;\">Для сохранения изменений в приложении "+
            "используйте <br><p style=\"margin-left: 110px;\">кнопку сохранения</html>",

            "<html><p style=\"margin-left: 30px;\">Чтобы добавить игрока в команду, нажмите на значок '+',"+
            "<br><p style=\"margin-left: 90px;\">а затем внесите данные о нем</html>",
            
            "<html><p style=\"margin-left: 30px;\">Чтобы выгнать игрока из сборной, нажмите кнопку 'x', после"+
            "<br><p style=\"margin-left: 100px;\">этого введите его ID</html>",
            
            "<html><p style=\"margin-left: 30px;\">Чтобы редактировать информацию о футболисте, нажмите"+
            "<br><p style=\"margin-left: 40px;\">на кнопку с карандашом, введите ID игрока, а затем измените"+ 
            "<br><p style=\"margin-left: 100px;\">необходимую информацию</html>",

            "<html><p style=\"margin-left: 50px;\">Для использования календарного окна нажмите"+
            "<p style=\"margin-left: 100px;\"> на соответствующую иконку"+
            "<br><p style=\"margin-left: 50px;\">Для удаление даты сначала выделите ее, а потом "+
            "<br><p style=\"margin-left: 90px;\">нажмите на кнопку \"Удалить дату\""+
            "<br><p style=\"margin-left: 40px;\">Для добавления даты нажмите на кнопку \"Добавить дату\", "+
            "<br><p style=\"margin-left: 80px;\">а потом введите необходимую информацию</html>",

            "<html>Чтобы совершать действия над игроком, надо сначала найти его по ID"+
            "<br><p style=\"margin-left: 20px;\">Для этого введите имя и фамилию внизу таблицы и нажмите"+
            "<br><p style=\"margin-left: 120px;\"> кнопку поиска"+
            "<br><p style=\"margin-left: 40px;\">Остальное узнаете из всплывающих подсказок</html>",
            "<html><p style=\"margin-left: 215px;\">@sedub01 Июль 2021</html>"
        };

        content.add(new JLabel(strings[0]));
        JLabel img = new JLabel(new ImageIcon("./src/main/resources/tutorial/save.png"));
        img.setToolTipText("Как по центру вставить?");
        content.add(img);
        
        content.add(new JLabel(strings[1]));
        content.add(new JLabel(strings[2]));
        content.add(new JLabel(strings[3]));
        content.add(new JLabel(" "));

        content.add(new JLabel(strings[4]));
        img = new JLabel(new ImageIcon("./src/main/resources/tutorial/calendar.gif"));
        img.setToolTipText("Качество как из жопы, признаю");
        img.setHorizontalAlignment(CENTER);
        content.add(img);
        content.add(new JLabel(" "));

        content.add(new JLabel(strings[5]));
        JLabel colored = new JLabel(strings[6]);

        content.add(colored);
        colored.setForeground(new Color(255, 0, 0));

        Thread colorThread = new Thread(new Runnable(){//мне кажется, здесь проще установить гифку
            public void run(){
                int count = 0;
                try{
                    while(count < 20){
                        int i, n=2;
                        for(i=0; i<=255; i++) {colored.setForeground(new Color(255, 0, 0+i)); Thread.sleep(n);}
                        for(i=0; i<=255; i++) {colored.setForeground(new Color(255-i, 0, 255)); Thread.sleep(n);}
                        for(i=0; i<=255; i++) {colored.setForeground(new Color(0, 0+i, 255)); Thread.sleep(n);}
                        for(i=0; i<=255; i++) {colored.setForeground(new Color(0, 255, 255-i)); Thread.sleep(n);}
                        for(i=0; i<=255; i++) {colored.setForeground(new Color(0+i, 255, 0)); Thread.sleep(n);}
                        for(i=0; i<=255; i++) {colored.setForeground(new Color(255, 255-i, 0)); Thread.sleep(n);}
                        count++;
                    }
                }
                catch(Exception ex){}
            }
        });
        colorThread.start();

        OK.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                helpBox.dispose();
                colorThread.interrupt();
            }
        });

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(OK, BorderLayout.SOUTH);

        superPanel.add(content, BorderLayout.NORTH);
        superPanel.add(buttonPanel, BorderLayout.SOUTH);
        scroll = new JScrollPane(superPanel);
        helpBox.add(scroll);
        
        helpBox.setSize(450, 530);
        helpBox.setResizable(false);
        helpBox.setLocationRelativeTo(null);
        helpBox.setVisible(true);
    }
}
