package team;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import javax.persistence.*;

import exceptions.*;
/**Класс футболиста*/
@Entity
@Table(name = "footballers")
public class Footballer implements IRoles{
    private static final Logger Flog = LogManager.getLogger(Footballer.class);
    @Id
	@GeneratedValue(strategy=GenerationType.IDENTITY)
	@Column(name="id")
    private int ID;
    @Column(name = "name")
    private String name;
    @Column(name = "lastname")
    private String last_name;
    @Column(name = "roleid")
    private int RoleID;//см. IRoles
    private String club; //принадлежность к клубу
    private String city; //город прибывшего футболиста
    private int goals; // кол-во забитых голов
    private int salary; //зарплата в долларах в месяц
    @ManyToOne(optional = true)
    @JoinColumn(name = "bossid")
    private Team team;
    /**
     * @param ID футболиста
     * @param name Имя футболиста
     * @param last_name Его фамилия
     * @param club Название клуба
     * @param city Город
     * @param goals Кол-во голов
     * @param salary Зарплата в год
     * @param RoleID Код специализации
     */
    public Footballer(int ID, String name, String last_name, String club, String city, int goals, int salary, int RoleID) {
        this.ID = ID;
        this.name = name;
        this.last_name = last_name;
        this.club = club;
        this.city = city;
        this.goals = goals;
        this.salary = salary;
        this.RoleID = RoleID;
    }
    /** Вывод подробной информации о футболисте для окошка*/
    public String info() {
        String[] buf = new String[6];
        buf[0] = "\n---Информация об игроке " + name + ' ' + last_name+"---\n";
        buf[1] = "Специальность: " + roles[RoleID]+"\n";
        buf[2] = "Клуб: "+club+"\n";
        buf[3] = "Город: "+city+"\n";
        buf[4] = "Кол-во голов: "+Integer.toString(goals)+"\n";
        buf[5] = "Зарплата в год: "+Integer.toString(salary)+"$\n";
        /*
        System.out.println("\n---Информация об игроке " + name + ' ' + last_name+"---");
        System.out.println("Специальность: " + roles[RoleID]);
        System.out.println("Клуб: "+club);
        System.out.println("Город: "+city);
        System.out.println("Кол-во голов: "+goals);
        System.out.println("Зарплата в год: "+salary+'$');
        */
        return buf[0]+buf[1]+buf[2]+buf[3]+buf[4]+buf[5];
    }

    public void setID(int ID){
        this.ID = ID;
    }
    public void setName(String name){
        this.name = name;
    }
    public void setLastName(String last_name){
        this.last_name = last_name;
    }
    public void setRole(int RoleID){
        this.RoleID = RoleID;
    }
    public void setClub(String club){
        this.club = club;
    }
    public void setCity(String city){
        this.city = city;
    }
    public void setGoals(int goals){
        this.goals = goals;
    }
    public void setSalary(int salary){
        this.salary = salary;
    }

    public int getID(){
        return ID;
    }
    public String getName(){
        return name;
    }
    public String getLastName(){
        return last_name;
    }
    public int getRole(){
        return RoleID;
    }
    public String getClub(){
        return club;
    }
    public String getCity(){
        return city;
    }
    public int getGoals(){
        return goals;
    }
    public int getSalary(){
        return salary;
    }
    /**
     * Проверка на корректность вводимых данных
     * @throws IllegalArgumentException Неверное наименование города или клуба
     * @throws WrongNameException Некорректное имя
     * @throws WrongLastNameException Некорректная фамилия
     */
    public void isAllRight() throws IllegalArgumentException, WrongNameException, WrongLastNameException, ArithmeticException{
        Flog.info("Checking footballer");
        if (name.equals("") || last_name.equals("") || city.equals("") || club.equals("")){
            Flog.error("Empty spaces");
            throw new IllegalArgumentException("Нельзя оставлять пустые поля!!!");
        }
        for (int i = 0; i<name.length(); ++i)
            if ((int)name.charAt(i)<192){ //до буквы А
                Flog.error("Wrong name");
                throw new WrongNameException("Некорректно введенное имя");
            }
                
        for (int i = 0; i<last_name.length(); ++i)
            if ((int)last_name.charAt(i)<192){
                Flog.error("Wrong last name");
                throw new WrongLastNameException("Некорректно введенная фамилия");
            }
                
        for (int i = 0; i<city.length(); ++i)
            if ((int)city.charAt(i) < 192 && (int)city.charAt(i) != 32 && (int)city.charAt(i) != 45){
                Flog.error("Wrong city");
                throw new IllegalArgumentException("Неверно введенный город");
            }
                
        for (int i = 0; i<club.length(); ++i)
            if ((int)club.charAt(i) < 192 && (int)club.charAt(i) != 32 && (int)club.charAt(i) != 45){
                if ((int)club.charAt(i) < 48 || (int)club.charAt(i) > 57){
                    Flog.error("Wrong club");
                    throw new ArithmeticException("Неправильное название клуба");
                }
            }
        Flog.info("Footballer is correct");
    }
}