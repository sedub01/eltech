package team;
import java.util.*;

import com.itextpdf.text.Font;
import com.itextpdf.text.Phrase;
import com.itextpdf.text.pdf.PdfPCell;
import com.itextpdf.text.pdf.PdfPTable;

import java.io.*;
/**
 * Сама команда
 * @param list Список футболистов
 * @param calendar Список дат матчей
 */
public class Team implements IRoles{ // класс-агрегатор
    private List<Footballer> list = null;
    private List<Calendar> calendar = null;
    private int bossID;
    private int wins;
    private int losses;
    private int games;
    /**
     * 
     * @param ID админа команды (для связки)
     * @param wins Кол-во победных матчей
     * @param losses Кол-во проигранных матчей
     * @param games Кол-во игр всего (для подсчета ничей)
     */
    public Team(int ID, int wins, int losses, int games){
        calendar = new ArrayList <Calendar>();
        list = new ArrayList<Footballer>();
        bossID = ID;
        this.wins = wins;
        this.losses = losses;
        this.games = games;
    }
    /**
     * Конструктор для ввода информации из файла
     */
    public Team(){
        calendar = new ArrayList <Calendar>();
        list = new ArrayList<Footballer>();
        wins=0; losses=0; games=0; bossID = 100000;
        try{//Ввод инфы из трех файлов
            BufferedReader buf = new BufferedReader(new FileReader(new File("./src/main/resources/data/Команда.txt")));//"./src/main/resources/data/Команда.txt"
            String s[] = buf.readLine().split(";");
            bossID = Integer.parseInt(s[0]);
            wins = Integer.parseInt(s[1]);
            losses = Integer.parseInt(s[2]);
            games =  Integer.parseInt(s[3]);
            buf.close();
            buf = new BufferedReader(new FileReader(new File("./src/main/resources/data/Игроки.txt")));
            while (buf.ready()){
                String v[] = buf.readLine().split(";");
                addFootballer(new Footballer(Integer.parseInt(v[0]), v[1], v[2], v[3], v[4], 
                Integer.parseInt(v[5]), Integer.parseInt(v[6]), Integer.parseInt(v[7])));
            }
            buf.close();
            buf = new BufferedReader(new FileReader(new File("./src/main/resources/data/Даты.txt")));
            while(buf.ready()){
                String v[] = buf.readLine().split(";");
                addDate(v[0], Integer.parseInt(v[1]), Integer.parseInt(v[2]));
            }
            buf.close();
        }
        catch(Exception ex){ ex.printStackTrace(); }
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
    public void addDate(Calendar date) {calendar.add(date);}
    /**
     * Удаление игрока по ID
     */
    public void delete(int id) {
        for (Footballer boy : list){
            if (boy.getID() == id){
                list.remove(boy);
                for (int i = id+1; i <= lastID(); ++i)
                    find(i).setID(i-1);
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
        Footballer nes = new Footballer();
        for (Footballer boy : list){
            if (boy.getID() == id){
                nes = boy;
            }
        }
        if (nes.name == null) throw new NullPointerException();
        return nes;
    }
    /**
     * Поиск игрока по имени и фамилии (находит первого попавшегося или не находит вовсе)
     * @param name Имя футболиста
     * @param lastName Его фамилия
     * @return ID найденного футболиста
     * @throws NullPointerException Игрок не найден
     */
    public int find(String name, String lastName) throws NullPointerException {
        for (Footballer boy:list)
            if (boy.getName().equals(name) && boy.getLastName().equals(lastName))
                return boy.getID();
        throw new NullPointerException(); //ничего не нашлось
    }
    public int firstID(){
        return list.get(0).ID;
    }
    public int lastID(){
        int max = 0;
        for (Footballer boy : list){
            if (boy.getID() > max) max = boy.getID();
        }
        return max;
    }
    void Win() {wins++; games++; }
    void Loss() {losses++; games++; } 
    
    public void addDate(String date, int win, int loss){
        Calendar day = new Calendar(date, win, loss);
        calendar.add(day);
        if (win > loss) Win();
        else if (loss > win) Loss();
        else games++; //ничья
    }

    /**
     * Сохранение изменений в файл
     */
    public void saveChanges(){
        try{
            FileWriter writer1 = new FileWriter("./src/main/resources/data/Даты.txt");
            for (Calendar cal: calendar){
                writer1.write(cal.getDate()+';'+cal.getWins()+';'+cal.getLosses()+'\n');
            }
            writer1.flush();
            writer1.close();

            FileWriter writer2 = new FileWriter("./src/main/resources/data/Игроки.txt");
            for (Footballer boy: list){
                writer2.write(boy.getID()+";"+boy.getName()+';'+boy.getLastName()+
                ';'+boy.getClub()+';'+boy.getCity()+';'+boy.getGoals()+';'+boy.getSalary()+
                ';'+boy.getRole()+'\n');
            }
            writer2.flush();
            writer2.close();

            FileWriter writer3 = new FileWriter("./src/main/resources/data/Команда.txt");
            writer3.write(bossID+";"+wins+";"+losses+";"+games);
            writer3.flush();
            writer3.close();
        }
        catch(Exception ex){ex.getStackTrace();}
    }
    /**
     * Вывод информации о команде
     * @return Строку информации для вывода в окошке
     */
    public String msg(){
        String[] buf = new String[5];
        buf[0] = "ID Админа: "+Integer.toString(bossID)+"\n";
        buf[1] = "Кол-во игроков: "+Integer.toString(list.size())+"\n";
        buf[2] = "Кол-во побед: "+Integer.toString(wins)+"\n";
        buf[3] = "Кол-во поражений: "+Integer.toString(losses)+"\n";
        buf[4] = "Кол-во ничей: "+Integer.toString(games - wins - losses)+"\n";
        /*
        System.out.println("ID Админа: " + bossID);
        System.out.println("Кол-во побед: "+ wins);
        System.out.println("Кол-во поражений: "+ losses);
        System.out.println("Кол-во ничей: "+ (games - wins - losses));
        */
        return buf[0] + buf[1]+buf[2]+buf[3]+buf[4];
    }

    /**
     * Добавление информации об игроках в таблицу (для класса {@link #PDFGenerator})
     * @param table Таблица в PDF файле
     * @param font Шрифт выводимого текста (для кириллицы)
     */
    public void addCells(PdfPTable table, Font font){
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
    }
}