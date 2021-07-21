package team;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import javax.persistence.*;

/**
 * Класс, хранящий дату со счетом
 * @param date Дата в формате {@code String}
*  @param win Счет сборной 
 * @param lose Счет противника
 */
@Entity
@Table(name = "calendar")
public class Calendar{
    private static final Logger Clog = LogManager.getLogger(Footballer.class);
    @Id
	@GeneratedValue(strategy=GenerationType.IDENTITY)
	@Column(name="id")
    private int ID;
    private String date;
    private int wins;
    private int losses;
    /**
     * @param date Дата в формате {@code String}
     * @param win Счет сборной 
     * @param lose Счет противника
     */
    public Calendar(){}
    public Calendar(String date, int win, int lose){
        this.date = date;
        wins = win;
        losses = lose;
    }
    public int getID(){
        return ID;
    }
    public String getDate(){
        return date;
    }
    public int getWins(){
        return wins;
    }
    public int getLosses(){
        return losses;
    }

    public void setID(int ID){
        this.ID = ID;
    }
    public void setDate(String date){
        this.date = date;
    }
    public void setWins(int wins){
        this.wins = wins;
    }
    public void setLosses(int losses){
        this.losses = losses;
    }
    /**
     * Проверка даты на правильность
     * @throws IllegalArgumentException Неправильный формат даты
     * @throws NumberFormatException Вместо чисел введены буквы
     * @throws ArrayIndexOutOfBoundsException Функция {@code split} не разделила дату по точкам 
     */
    public void isDateRight() throws IllegalArgumentException, NumberFormatException, ArrayIndexOutOfBoundsException{
        Clog.info("Checking object in calendar");
        if (date.equals("")) throw new IllegalArgumentException();
        String[] strings = date.split("\\.");
        int[] nums = new int[3];
        for (int i=0; i<3; i++) 
            nums[i] = Integer.parseInt(strings[i]);
        if (nums[2]<0){
            Clog.error("Year value is below zero");
            throw new IllegalArgumentException();
        }
        
        switch(nums[1])
        {
            case 1:  //JANUARY
            case 3:  //MARCH
            case 5:  //MAY
            case 7:  //JULY
            case 8:  //AUGUST
            case 10: //OCTOBER
            case 12: //DECEMBER
                IsRange(nums[0], 1, 31);
                break;
            case 2:
                if (nums[2] % 4 == 0)
                    IsRange(nums[0], 1, 29);
                else
                    IsRange(nums[0], 1, 28);
                break;
            case 4:  //APRIL
            case 6:  //JUNE
            case 9:  //SEPTEMBER
            case 11: //NOVEMBER
                IsRange(nums[0], 1, 30);
                break;
            default:
                Clog.error("Wrong month value");
                throw new IllegalArgumentException();
        }
        if (wins<0 || losses<0){
            Clog.error("Wins or losses values are below zero");
            throw new NumberFormatException();
        }
        Clog.info("This object is correct!");
    }
    /**
     * Проверка диапозона чисел
     * @param value Значение
     * @param min Минимальное значение
     * @param max Максимальное значение
     * @throws IllegalArgumentException Неверное значение
     */
    private void IsRange(int value, int min, int max) throws IllegalArgumentException
    {
        if (value < min || value > max){
            Clog.error("Day value is out of range");
            throw new IllegalArgumentException();
        }
    }
    //сделать статический класс подсчета кол-ва дней
    public static int howMuchDays(String date){
        final int[] months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        String[] strings = date.split("\\.");
        int[] nums = new int[3];
        for (int i=0; i<3; i++) 
            nums[i] = Integer.parseInt(strings[i]);
        int days = 0;
        //прибавили годы
        days += nums[2] * 365 + nums[2]%4;
        //прибавили месяцы
        days += nums[1]*months[nums[1]];
        // прибавили дни
        days += nums[0];
        return days;
    }
}