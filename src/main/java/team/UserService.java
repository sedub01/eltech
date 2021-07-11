package team;
import java.util.List;

public class UserService {

    private UserDao usersDao = new UserDao();

    public UserService() {}

    public Footballer findUser(int id) {
        return usersDao.findById(id);
    }

    public void saveUser(Footballer user) {
        usersDao.save(user);
    }

    public void deleteUser(Footballer user) {
        usersDao.delete(user);
    }

    public void updateUser(Footballer user) {
        usersDao.update(user);
    }

    public List<Footballer> findAllUsers() {
        return usersDao.findAll();
    }
}
