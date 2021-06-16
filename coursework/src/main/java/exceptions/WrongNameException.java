package exceptions;

public class WrongNameException extends Exception {
    private String str;
    public WrongNameException(String str){
        super(str);
        this.str = str;
    }
    public String getMessage(){return str;}
}
