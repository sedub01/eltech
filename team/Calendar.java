package team;

public class Calendar{
    private String date;
    private int wins;
    private int losses;
    public Calendar(String date, int win, int lose){
        this.date = date;
        wins = win;
        losses = lose;
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

    public void setDate(String date){
        this.date = date;
    }
    public void setWins(int wins){
        this.wins = wins;
    }
    public void setLosses(int losses){
        this.losses = losses;
    }
}