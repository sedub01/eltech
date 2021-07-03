/**Пакет со всеми графическими принадлежностями */
package design;
import team.*;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.*;
import java.awt.event.*;

import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

/**
 * Весь графический интерфейс
 * @author sedub01
 */
public class PlayerList implements IRoles {
    /**Логгер для окна PLayerList */
    private static final Logger PLlog = LogManager.getLogger(PlayerList.class);
    /**Окно с основным интерфейсом */
    private JFrame playerList;
    /**Модель таблицы (данные внутри) */
    private MyModel model;
    /** Кнопка сохранения изменений */
    private JButton save;
    /**Кнопка добавления нового игрока */
    private JButton add; 
    /**Кнопка удаления игрока */
    private JButton delete;
    /**Кнопка печати информации в PDF отчете */
    private JButton print;
    /**Кнопка вывода информации о футболисте */
    private JButton fout;
    /**Кнопка вывода таблицы календаря */
    private JButton cal;
    /**Кнопка вывода информации о команде */
    private JButton info;
    /**Кнопка изменения информации о футболисте */
    private JButton edit;
    /**Кнопка туториала по программе */
    private JButton help;

    /** Панель инструментов*/
    private JToolBar toolBar;
    /** Скролл для движения вниз*/
    private JScrollPane scroll;
    /** Сама таблица с игроками*/
    private JTable players;
    /** Текстовое поле для имени внизу окна*/
    private JTextField PlayerName;
    /** Текстовое поле для фамилии там же*/
    private JTextField PlayerLastName;
    /** Кнопка для поиска по имени и фамилии*/
    private JButton filter;
    /**Добавление компонентов в панель */
    JPanel filterPanel;
    
    /**PDF отчет */
    private PDFGenerator report;
    /**
     * Отображение интерфейса
     * @param theBest команда
     */
    public void show(Team theBest) {
        PLlog.info("Main menu is preparing");
        // Создание окна
        playerList = new JFrame("Список футболистов");
        playerList.setSize(750, 400);
        playerList.setLocation(150, 150);
        playerList.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        playerList.setIconImage(new ImageIcon("./src/main/resources/img/football_icon.png").getImage());
        // Создание кнопок и прикрепление иконок
        save = new JButton(new ImageIcon("./src/main/resources/img/save.png"));
        add = new JButton(new ImageIcon("./src/main/resources/img/add.png"));
        delete = new JButton(new ImageIcon("./src/main/resources/img/delete.png"));
        edit = new JButton(new ImageIcon("./src/main/resources/img/edit.png"));
        print = new JButton(new ImageIcon("./src/main/resources/img/print.png"));
        fout = new JButton(new ImageIcon("./src/main/resources/img/fout.png"));
        cal = new JButton(new ImageIcon("./src/main/resources/img/calendar.png"));
        info = new JButton(new ImageIcon("./src/main/resources/img/info.png"));
        help = new JButton(new ImageIcon("./src/main/resources/img/help.png"));
        // Настройка подсказок для кнопок
        save.setToolTipText("Сохранить изменения");
        add.setToolTipText("Добавить игрока");
        delete.setToolTipText("Выгнать игрока");
        edit.setToolTipText("Изменить информацию об игроке");
        fout.setToolTipText("Информация о футболисте");
        print.setToolTipText("Распечатать список?");
        cal.setToolTipText("Календарь игр");
        info.setToolTipText("Информация о сборной");
        help.setToolTipText("Как пользоваться программой");
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
        toolBar.add(help);
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
        Thread pLThread = new Thread(new Runnable(){
            public void run(){
                model.showTable(theBest);
            }
        });
        pLThread.start();
        
        // Размещение таблицы с данными
        save.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                PLlog.info("User is going to save his changes");
                theBest.saveChanges();
                JOptionPane.showMessageDialog(playerList, "Данные сохранены", "", 
                JOptionPane.INFORMATION_MESSAGE);
                PLlog.info("Data saved successfully!");
            }
        });
        print.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                PLlog.info("User is going to print his report");
                Thread pdfThread = new Thread(new Runnable(){
                    public void run(){
                        report = new PDFGenerator("Report.pdf", theBest.msg());
                        report.addFootballers(theBest);
                        report.addCals(theBest.getCal());
                        report.doClose();
                        JOptionPane.showMessageDialog(playerList, "Отчет сохранен в корневой папке", 
                        "Report.pdf", JOptionPane.INFORMATION_MESSAGE);
                        PLlog.info("Report printed successfully!");
                    } 
                });
                pdfThread.start();
                
            }
        });
        info.setActionCommand("Кнопка info нажата");
        info.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                JOptionPane.showMessageDialog(playerList, theBest.msg(), "Информация о сборной", 
                JOptionPane.INFORMATION_MESSAGE);
            }
        });
        delete.addActionListener(new deleteButton(model, theBest, playerList));
        fout.addActionListener(new foutButton(theBest, playerList)); //в функцию передается ссылка, а из нее возвращается копия!!!
        cal.addActionListener(new calButton(theBest, playerList)); //передал playerList, чтобы сделать окно модальным через JDialog
        add.addActionListener(new addButton(playerList, theBest, model));
        edit.addActionListener(new editButton(playerList, theBest, model));
        help.addActionListener(new helpButton(playerList));
        
        playerList.add(scroll, BorderLayout.CENTER);
        // Подготовка компонентов поиска
        PlayerName = new JTextField("Имя");
        PlayerLastName = new JTextField("Фамилия");
        filter = new JButton("Поиск");
        PlayerName.setPreferredSize(new Dimension(100, 20));
        PlayerLastName.setPreferredSize(new Dimension(100, 20));
        
        filterPanel = new JPanel();
        filterPanel.add(PlayerName);
        filterPanel.add(PlayerLastName);
        filterPanel.add(filter);
        //Поиск по имени фамилии
        filter.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                PLlog.info("User is going to find player with ID");
                try{
                    int foundID = theBest.find(PlayerName.getText(), PlayerLastName.getText());
                    JOptionPane.showMessageDialog(playerList, "ID игрока: "+Integer.toString(foundID), 
                    "ID игрока", JOptionPane.INFORMATION_MESSAGE);
                    PLlog.info("Player has been found!");
                }
                catch(NullPointerException ex){
                    PLlog.error("No player with this ID!");
                    JOptionPane.showMessageDialog(playerList, "Нет такого футболиста", "Каво", 
                    JOptionPane.ERROR_MESSAGE);
                }
                
            }
        });
        // Размещение панели поиска внизу окна
        playerList.add(filterPanel, BorderLayout.SOUTH);
        // Визуализация экранной формы
        playerList.setVisible(true);
        PLlog.info("Main menu has been created");
    }
}
