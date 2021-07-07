import team.*;
import design.*;

public class MyPC{//не забудьте прописать в консоли команду chcp 1251
    public static void main(String[] args) {
        Team theBest = new Team(5); 
        PlayerList GUI = new PlayerList();
        GUI.show(theBest);
    }
}