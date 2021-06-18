package team;

abstract class Person{
    Person() {}
    Person(String name, String last_name, int ID) {
        this.name = name; 
        this.last_name = last_name;
        this.ID = ID;
    }
    protected int ID;
    protected String name;
    protected String last_name;
    abstract String info();
}