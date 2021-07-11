package team;
import org.hibernate.Session;
import org.hibernate.Transaction;
import java.util.List;

public class UserDao {
    public Footballer findById(int id) {
        return HibernateSessionFactoryUtil.getSessionFactory().openSession().get(Footballer.class, id);
    }

    public void save(Footballer user) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx1 = session.beginTransaction();
        session.save(user);
        tx1.commit();
        session.close();
    }

    public void update(Footballer user) {
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx1 = session.beginTransaction();
        session.update(user);
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

    public List<Footballer> findAll() {
        List<Footballer> users = (List<Footballer>)HibernateSessionFactoryUtil.getSessionFactory().openSession().createQuery("From Footballer").list();
        return users;
    }
}
