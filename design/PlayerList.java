package design;
import team.*;

import java.awt.BorderLayout;
import javax.swing.*;

import java.awt.event.*;

public class PlayerList implements IRoles {
    // Объявления графических компонентов
    private JFrame playerList;
    private MyModel model;
    private JButton save, add, delete, print, fout, cal, info, edit;
    private JToolBar toolBar;
    private JScrollPane scroll;
    private JTable players;
    private JTextField PlayerName, PlayerLastName;
    private JButton filter;
    public void show(Team theBest) {
        //System.out.println("Hello world!");
        
        // Создание окна
        playerList = new JFrame("Список футболистов");
        playerList.setSize(750, 400);
        playerList.setLocation(150, 150);
        playerList.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        playerList.setIconImage(new ImageIcon("./img/football_icon.png").getImage());
        // Создание кнопок и прикрепление иконок
        save = new JButton(new ImageIcon("./img/save.png"));
        add = new JButton(new ImageIcon("./img/add.png"));
        delete = new JButton(new ImageIcon("./img/delete.png"));
        edit = new JButton(new ImageIcon("./img/edit.png"));
        print = new JButton(new ImageIcon("./img/print.png"));
        fout = new JButton(new ImageIcon("./img/fout.png"));
        cal = new JButton(new ImageIcon("./img/calendar.png"));
        info = new JButton(new ImageIcon("./img/info.png"));
        // Настройка подсказок для кнопок
        save.setToolTipText("Сохранить изменения");
        add.setToolTipText("Добавить игрока");
        delete.setToolTipText("Выгнать игрока");
        edit.setToolTipText("Изменить информацию об игроке");
        fout.setToolTipText("Информация о футболисте");
        print.setToolTipText("Распечатать список?");
        cal.setToolTipText("Календарь игр");
        info.setToolTipText("Информация о сборной");
        // Добавление кнопок на панель инструментов
        toolBar = new JToolBar("Панель инструментов");
        toolBar.add(save);
        toolBar.add(add);
        toolBar.add(delete);
        toolBar.add(edit);
        toolBar.add(fout);
        toolBar.add(cal);
        toolBar.add(print);
        toolBar.add(info);
        // Размещение панели инструментов
        playerList.setLayout(new BorderLayout());
        playerList.add(toolBar, BorderLayout.NORTH);
        // Создание таблицы с данными
        String [] columns = {"ID", "Имя", "Фамилия", "Специальность", 
        "Клуб", "Город ", "Кол-во голов", "Зарплата"};
        String [][] data = new String[0][];
        model= new MyModel(data, columns);
        players = new JTable(model){
            @Override
            public boolean isCellEditable(int row, int column){ return false; }
        };
        scroll = new JScrollPane(players);
        model.showTable(theBest);
        // Размещение таблицы с данными
        save.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                theBest.saveChanges();
                JOptionPane.showMessageDialog(playerList, "Данные сохранены", "", 
                JOptionPane.INFORMATION_MESSAGE);
            }
        });
        print.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                JOptionPane.showMessageDialog(playerList, "Я еще не научился печатать отчеты", 
                "ЧТО???", JOptionPane.ERROR_MESSAGE);
            }
        });
        info.setActionCommand("Кнопка info нажата");
        info.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                JOptionPane.showMessageDialog(playerList, theBest.msg(), "Информация о сборной", 
                JOptionPane.INFORMATION_MESSAGE);
            }
        });
        delete.addActionListener(new deleteButton(model, theBest, playerList)); //если забагуется, верну обратно
        fout.addActionListener(new foutButton(theBest, playerList)); //в функцию передается ссылка, а из нее возвращается копия!!!
        cal.addActionListener(new calButton(theBest, playerList)); //передал playerList, чтобы сделать окно модальным через JDialog
        add.addActionListener(new addButton(playerList, theBest, model));
        edit.addActionListener(new editButton(playerList, theBest, model));
        
        playerList.add(scroll, BorderLayout.CENTER);
        // Подготовка компонентов поиска
        PlayerName = new JTextField("Имя");
        PlayerLastName = new JTextField("Фамилия");
        filter = new JButton("Поиск");
        // Добавление компонентов на панель
        JPanel filterPanel = new JPanel();
        filterPanel.add(PlayerName);
        filterPanel.add(PlayerLastName);
        filterPanel.add(filter);
        //Поиск по имени фамилии
        filter.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                try{
                    int foundID = theBest.find(PlayerName.getText(), PlayerLastName.getText());
                    JOptionPane.showMessageDialog(playerList, "ID игрока: "+Integer.toString(foundID), 
                    "ID игрока", JOptionPane.INFORMATION_MESSAGE);
                }
                catch(NullPointerException ex){
                    JOptionPane.showMessageDialog(playerList, "Нет такого футболиста", "Каво", 
                    JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        // Размещение панели поиска внизу окна
        playerList.add(filterPanel, BorderLayout.SOUTH);
        // Визуализация экранной формы
        playerList.setVisible(true);
    }
}
