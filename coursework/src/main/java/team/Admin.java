package team;

public class Admin extends Person{
    public Admin(String name, String last_name, int ID) {
        super(name, last_name, ID); 
    }
    public String info() {System.out.println("Админа зовут " + name + ' ' + last_name + "; " + ID); return "";}
    public int ID() {return ID;}
}