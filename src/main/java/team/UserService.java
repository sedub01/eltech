package team;
import java.util.ArrayList;
import java.util.List;

public class UserService {

    private UserDao usersDao = new UserDao();
    static List<Footballer> tempList = new ArrayList<Footballer>();

    public UserService() {}

    public Footballer findFootballer(int id) {
        return usersDao.findFootballerById(id);
    }

    public void saveFootballer(Footballer user) {
        usersDao.save(user);
    }

    public void deleteFootballer(Footballer user) {
        usersDao.delete(user);
    }

    public void updateFootballer(Footballer user) {
        usersDao.update(user);
    }

    public List<Footballer> findAllFootballers() {
        return usersDao.findFootballers();
    }
    public void cloneFList(List<Footballer> list){
        for (Footballer boy : list) tempList.add(boy);
    }

    public Team findTeam(){
        return usersDao.findTeam();
    }

    public List<Calendar> findAllCalendar() {
        return usersDao.findCalendar();
    }
}
