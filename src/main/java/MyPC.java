import team.*;
import design.*;

public class MyPC{//не забудьте прописать в консоли команду chcp 1251
    public static void main(String[] args) {
        Team theBest = new Team(); 
        PlayerList GUI = new PlayerList();
        @SuppressWarnings("unused")
        Admin John = new Admin("Семён", "Дубенков", theBest.getBossID());
        GUI.show(theBest);
    }
}