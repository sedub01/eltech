package hibernate;
import java.util.ArrayList;
import java.util.List;
import team.*;

public class UserService {

    private UserDao usersDao = new UserDao();
    public static List<Footballer> tempList = new ArrayList<Footballer>();
    public static List<Calendar> tempCals = new ArrayList<Calendar>();

    public UserService() {}

    public void saveFootballer(Footballer user) {
        usersDao.save(user);
    }

    public void deleteFootballer(Footballer user) {
        usersDao.delete(user);
    }

    public List<Footballer> findAllFootballers() {
        return usersDao.findFootballers();
    }
    public void cloneFList(List<Footballer> list){
        for (Footballer boy : list) tempList.add(boy);
    }
    public void cloneCList(List<Calendar> cals){
        for (Calendar cal : cals) tempCals.add(cal);
    }

    public Team findTeam(){
        return usersDao.findTeam();
    }

    public List<Calendar> findAllCalendar() {
        return usersDao.findCalendar();
    }
    public void deleteCal(Calendar cal) {
        usersDao.delete(cal);
    }
    public void saveCal(Calendar cal) {
        usersDao.save(cal);
    }

}
