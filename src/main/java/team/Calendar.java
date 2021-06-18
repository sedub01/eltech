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
    
    public void isDateRight() throws IllegalArgumentException, NumberFormatException{
        String[] strings = date.split("\\.");
        int[] nums = new int[3];
        for (int i=0; i<3; i++) 
            nums[i] = Integer.parseInt(strings[i]);
        if (nums[2]<0) throw new IllegalArgumentException();
        
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
                throw new IllegalArgumentException();
            
        }
        if (wins<0 || losses<0) throw new NumberFormatException();
    }

    private void IsRange(int value, int min, int max) throws IllegalArgumentException
    {
        if (value < min) throw new IllegalArgumentException();
        if (value > max) throw new IllegalArgumentException();
    }
}