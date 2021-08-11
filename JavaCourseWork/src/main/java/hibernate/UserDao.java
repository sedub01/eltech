package hibernate;
import org.hibernate.Session;
import org.hibernate.Transaction;
import java.util.List;
import team.*;

public class UserDao {
    public Footballer findFootballerById(int id) {
        return HibernateSessionFactoryUtil.getSessionFactory().openSession().get(Footballer.class, id);
    }

    public void save(Footballer user) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx1 = session.beginTransaction();
        session.save(user);
        tx1.commit();
        session.close();
    }

    public void delete(Footballer user) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx1 = session.beginTransaction();
        session.delete(user);
        tx1.commit();
        session.close();
    }

    public List<Footballer> findFootballers() {
        @SuppressWarnings("unchecked")
        List<Footballer> users = (List<Footballer>)HibernateSessionFactoryUtil.getSessionFactory().openSession().createQuery("From Footballer").list();
        return users;
    }

    public Team findTeam(){
        @SuppressWarnings("unchecked")
        List<Team> teams = (List<Team>)HibernateSessionFactoryUtil.getSessionFactory().openSession().createQuery("From Team").list();
        return teams.get(0);
    }

    //можно было сделать через шаблоны
    public List<Calendar> findCalendar() {
        @SuppressWarnings("unchecked")
        List<Calendar> cals = (List<Calendar>)HibernateSessionFactoryUtil.getSessionFactory().openSession().createQuery("From Calendar").list();
        return cals;
    }
    public void delete(Calendar cal) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx1 = session.beginTransaction();
        session.delete(cal);
        tx1.commit();
        session.close();
    }
    public void save(Calendar cal) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx1 = session.beginTransaction();
        session.save(cal);
        tx1.commit();
        session.close();
    }
}
