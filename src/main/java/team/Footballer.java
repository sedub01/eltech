package team;
import exceptions.*;

public class Footballer extends Person implements IRoles{
    private int RoleID;//см. IRoles
    private String club; //принадлежность к клубу
    private String city; //город прибывшего футболиста
    private int goals; // кол-во забитых голов
    private int salary; //зарплата в долларах в месяц
    public Footballer() {}
    public Footballer(int ID, String name, String last_name, String club, String city, int goals, int salary, int RoleID) {
        super(name, last_name, ID);
        this.club = club;
        this.city = city;
        this.goals = goals;
        this.salary = salary;
        this.RoleID = RoleID;
    }
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

    public void isAllRight() throws IllegalArgumentException, WrongNameException, WrongLastNameException{
        for (int i = 0; i<name.length(); ++i)
            if (Character.isDigit(name.charAt(i)))
                throw new WrongNameException("Некорректно введенное имя");

        for (int i = 0; i<last_name.length(); ++i)
            if (Character.isDigit(last_name.charAt(i)))
                throw new WrongLastNameException("Некорректно введенная фамилия");

        for (int i = 0; i<city.length(); ++i)
            if (Character.isDigit(city.charAt(i)))
                throw new IllegalArgumentException();

        for (int i = 0; i<club.length(); ++i)
            if (Character.isDigit(club.charAt(i)))
                throw new IllegalArgumentException();
    }
}