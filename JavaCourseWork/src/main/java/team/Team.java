package team;
import java.util.*;
import hibernate.*;

import javax.swing.table.DefaultTableModel;
import javax.persistence.*;
import com.itextpdf.text.Font;
import com.itextpdf.text.Phrase;
import com.itextpdf.text.pdf.PdfPCell;
import com.itextpdf.text.pdf.PdfPTable;

import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;



/**
 * Сама команда
 * @param list Список футболистов
 * @param calendar Список дат матчей
 */
@Entity
@Table(name = "team")
public class Team implements IRoles{ // класс-агрегатор
    private static final Logger Tlog = LogManager.getLogger(Team.class);
    @OneToMany(cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Footballer> list = new ArrayList<Footballer>();
    @OneToMany(cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Calendar> calendar =  new ArrayList <Calendar>();
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    @Column(name="id")
    private int bossID;
    @Column(name="wins")
    private int wins;
    //можно не указывать Column name, если оно совпадает с названием столбца в таблице
    private int losses;
    private int games;
    private String DBlock = new String();
    /**
     * @param ID админа команды (для связки)
     * @param wins Кол-во победных матчей
     * @param losses Кол-во проигранных матчей
     * @param games Кол-во игр всего (для подсчета ничей)
     */
    public Team(int ID, int wins, int losses, int games){
        bossID = ID;
        this.wins = wins;
        this.losses = losses;
        this.games = games;
    }
    public Team(){}
    /**Конструктор для ввода информации из файла*/
    public Team(int fict){
        UserService userService = new UserService();
        wins=0; losses=0; games=0; bossID = 222663;
        try{//Ввод инфы из трех файлов
            Tlog.info("Team is ready to construct");
            synchronized(DBlock){//блок может выполняться только одним потоком одновременно
                Tlog.info("Info about team");
                //ниче делать не надо)))
                Tlog.info("Info about team is ready");
            }
            synchronized(DBlock){//в начале все клонируется одинаково
                UserService.tempList = userService.findAllFootballers();
                
                for (Footballer boy : UserService.tempList) addFootballer(boy);
            }
            synchronized(DBlock){
                Tlog.info("Info about calendar");
                UserService.tempCals = userService.findAllCalendar();
                for(Calendar cal : UserService.tempCals) addDate(cal);
                Tlog.info("Info about calendar is ready");
            }
            Tlog.info("Team constructed");
        }
        catch(Exception ex){ ex.printStackTrace(); Tlog.error("One of inner filer (team, gamers, dates) is ruined");}
    }
    
    public int getBossID(){
        return bossID;
    }
    public int getSizeTeam(){
        return list.size();
    }
    public List<Calendar> getCal(){
        return calendar;
    }
    /**
     * Использую только для тестов!!!
     * @return Лист футболистов
     */
    public List<Footballer> getFootballers(){
        return list;
    }
    public void addFootballer(Footballer boy) {list.add(boy);}
    /**Удаление игрока по ID*/
    public void delete(int id) {
        for (Footballer boy : list){
            if (boy.getID() == id){
                list.remove(boy);
                //for (int i = id+1; i <= lastID(); ++i)
                    //find(i).setID(i-1);
                break;
            }
        }
    } 
    /**
     * Поиск игрока по ID
     * @param id
     * @return объект найденного футболиста
     * @throws NullPointerException Выбрасывает исключение, если игрок отсутствует
     */
    public Footballer find(int id) throws NullPointerException {
        Tlog.info("Finding needed gamer with ID");
        for (Footballer boy : list){
            if (boy.getID() == id){
                Tlog.info("Gamer found");
                return boy;
            }
        }
        Tlog.error("Gamer not found");
        throw new NullPointerException();
    }
    /**
     * Поиск игрока по имени и фамилии (находит первого попавшегося или не находит вовсе)
     * @param name Имя футболиста
     * @param lastName Его фамилия
     * @return ID найденного футболиста
     * @throws NullPointerException Игрок не найден
     */
    public List<Integer> find(String name, String lastName) throws NullPointerException {
        Tlog.info("Finding needed gamer with his name");
        List<Integer> IDs = new ArrayList<>();
        for (Footballer boy:list)
            if (boy.getName().equals(name) && boy.getLastName().equals(lastName)){
                Tlog.info("Gamer found");
                IDs.add(boy.getID());
            }
        if (IDs.size() == 0){
            Tlog.error("Gamer not found");
            throw new NullPointerException(); //ничего не нашлось
        }
        return IDs;
        
    }
    public int firstID(){
        return list.get(0).getID();
    }
    public int lastID(){
        int max = 0;
        for (Footballer boy : list)
            if (boy.getID() > max) max = boy.getID();
        return max;
    }
    
    public void addDate(Calendar cal){
        int index = 0;
        for (Calendar tempCal : calendar)
            if (Calendar.howMuchDays(cal.getDate()) > Calendar.howMuchDays(tempCal.getDate())) 
                index++;
            else break;
        calendar.add(index, cal);
        if (cal.getWins()>cal.getLosses()) wins++;
        else if (cal.getWins()<cal.getLosses()) losses++;
        games++;
    }

    public void addDate(String date, int win, int loss){
        addDate(new Calendar(date, win, loss));
    }

    public void deleteDate(int selected){
        Calendar temp = calendar.remove(selected);
        games--;
        if (temp.getWins()>temp.getLosses())
            wins--;
        else if (temp.getWins()<temp.getLosses())
            losses--;
    }

    public void addDates(DefaultTableModel newModel){
        for (Calendar cal:calendar) {
            String buf[] = new String[3];
            buf[0] = cal.getDate();
            buf[1] = Integer.toString(cal.getWins());
            buf[2] = Integer.toString(cal.getLosses());
            newModel.addRow(buf);
        }
    }
    /**Сохранение изменений в файлы*/
    public void saveChanges(){
        try{
            Tlog.info("Saving all changes");
            UserService userService = new UserService();
            synchronized(DBlock){
                Tlog.info("Saving calendar");
                for (Calendar cal : UserService.tempCals) userService.deleteCal(cal);
                for (Calendar cal : calendar) userService.saveCal(cal);
                Tlog.info("Calendar saved");
            }
            
            synchronized(DBlock){
                Tlog.info("Saving footballers");
                for (Footballer boy : UserService.tempList) userService.deleteFootballer(boy);
                for (Footballer boy : list) userService.saveFootballer(boy);
                Tlog.info("Footballers saved");
            }
            
            synchronized(DBlock){
                Tlog.info("Saving team info");
                //ниче делать не надо)))
                Tlog.info("Team info saved");
            }
            Tlog.info("Changes were saved");
        }
        catch(Exception ex){ex.getStackTrace(); Tlog.error("One of inner filer (team, gamers, dates) is ruined");}
    }
    /**
     * Вывод информации о команде
     * @return Строку информации для вывода в окошке
     */
    public String msg(){
        String[] buf = new String[5];
        //buf[0] = "ID Админа: "+Integer.toString(bossID)+"\n";
        buf[1] = "Кол-во игроков: "+Integer.toString(list.size())+"\n";
        buf[2] = "Кол-во побед: "+Integer.toString(wins)+"\n";
        buf[3] = "Кол-во поражений: "+Integer.toString(losses)+"\n";
        buf[4] = "Кол-во ничей: "+Integer.toString(games - wins - losses)+"\n";
        return /*buf[0] + */buf[1]+buf[2]+buf[3]+buf[4];
    }

    /**
     * Добавление информации об игроках в таблицу (для класса {@link #PDFGenerator})
     * @param table Таблица в PDF файле
     * @param font Шрифт выводимого текста (для кириллицы)
     */
    public void addCells(PdfPTable table, Font font){
        Tlog.info("Adding info in table");
        for(Footballer boy : list)
        {
            PdfPCell pfpc;
            table.addCell(""+boy.getID());
            pfpc = new PdfPCell(new Phrase(boy.getName(), font));
            //table.addCell(boy.getName());
            table.addCell(pfpc);
            pfpc = new PdfPCell(new Phrase(boy.getLastName(), font));
            table.addCell(pfpc);
            pfpc = new PdfPCell(new Phrase(roles[boy.getRole()], font));
            table.addCell(pfpc);
            pfpc = new PdfPCell(new Phrase(boy.getClub(), font));
            table.addCell(pfpc);
            pfpc = new PdfPCell(new Phrase(boy.getCity(), font));
            table.addCell(pfpc);
            table.addCell(""+boy.getGoals());
            table.addCell(""+boy.getSalary());
        }
        Tlog.info("Everything was added");
    }

}