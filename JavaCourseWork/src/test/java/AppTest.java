import java.util.List;
import java.util.ArrayList;

import team.*;

import static org.junit.Assert.*;

import org.junit.*;
/**
 * Unit test for simple App.
 */
public class AppTest 
{
    private static int testNUM;

    @BeforeClass
    public static void init()
    {
        testNUM = 0;
    }

    @Test
    public void allLoaded_notNull()
    {
        Team theBest = new Team();
        List<Footballer> list = theBest.getFootballers();
        List<Calendar> cals = theBest.getCal();

        assertNotNull(list);
        assertNotNull(cals);

        for(Footballer boy : list)
            assertNotNull(boy.getName());

        for(Calendar cal : cals)
            assertNotNull(cal.getDate());
    }

    private Footballer boy1;
    private Footballer boy2;

    private Calendar cal1;
    private Calendar cal2;

    private List<Footballer> list1 = new ArrayList<Footballer>();
    private List<Calendar> cals1;
    private Team MyTeam1= new Team(100000, 3, 4, 10);
    private Team MyTeam2;

    @Before
    public void newEntities()
    {
        ++testNUM;
        
        cals1 = new ArrayList<Calendar>();

        //======== Иниц. ========

        MyTeam2 = new Team(666000, 7, 18, 40);

        boy1 = new Footballer(666, "Антон", "Иванов", "Клуб любителей", "Махачкала", 17, 32190, 2);
        boy2 = new Footballer(667, "Семен", "Спиваков", "Кожаный мяч", "Воркута", 14, 28000, 1);
        cal1 = new Calendar("17.02.1963", 2, 1);
        cal2 = new Calendar("19.02.1963", 0, 2);

        //======== Добавление ========
        
        list1.add(boy1);
        list1.add(boy2);
        MyTeam1.addFootballer(boy1);
        MyTeam1.addFootballer(boy2);

        cals1.add(cal1);
        cals1.add(cal2);
        MyTeam2.addDate(cal1);
        MyTeam2.addDate(cal2);
    }

    @Test
    public void correctlyAdded()
    {
        assertEquals(list1, MyTeam1.getFootballers());
        assertEquals(cals1, MyTeam2.getCal());
    }

    @Test
    public void isDeleted()
    {
        Team MyTeam3 = new Team(33, 3, 7, 12);
        List<Footballer> list3 = new ArrayList<>();
        Footballer first = new Footballer(666, "Антон", "Иванов", "Клуб любителей", "Махачкала", 17, 32190, 2),
        second = new Footballer(667, "Семен", "Спиваков", "Кожаный мяч", "Воркута", 14, 28000, 1),
        third = new Footballer(668, "Кирилл", "Рыгалов", "Динамо", "Дагестан", 18, 32000, 3);

        MyTeam3.addFootballer(first);
        MyTeam3.addFootballer(second);
        MyTeam3.addFootballer(third);

        list3.add(first);
        list3.add(third);

        MyTeam3.delete(667);
        assertEquals(third.getID(), MyTeam3.getFootballers().get(1).getID());
    }

    @After
    public void testEnds()
    {
        System.out.println("Test " + AppTest.testNUM + " finished");
    }

    @AfterClass
    public static void allTestEnds()
    {
        System.out.println("All test finished");
    }
}
