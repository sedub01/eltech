package team;
/** Содержит названия специализаций*/
public interface IRoles{
    public String[] roles = {"Вратарь", "Нападающий", "Полузащитник", "Защитник"};
    public int GOALKEEPER = 0;
    public int STRIKER = 1;
    public int HALFBACK = 2;
    public int FULLBACK = 3;
}