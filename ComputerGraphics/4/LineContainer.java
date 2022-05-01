import java.awt.Point;
import java.util.ArrayList;
import java.util.List;

import java.security.SecureRandom;
/**Класс, делающий всю обработку массива линий */
public class LineContainer {
    public final int lineCount = 36;
    /**Четные номера - начало отрезка, нечетные - его конец */
    private List<Point> lineList = new ArrayList<>();
    private SecureRandom random = new SecureRandom();
    LineContainer(){
        for (int i = 0; i < lineCount * 2; i++)
            lineList.add(new Point((random.nextInt() % 1080 + 1080) % 1080, (random.nextInt() % 720 + 720) % 720));
    }
    //если a == b == 0, то начало и конец в поле видимости - он весь в поле видимости, с ним ничего делать не надо
    //если a * b != 0 (битовое И), отрезок лежит вне поля видимости - он отбрасывается 
    //если a * b == 0 (битовое И), отрезок может частично лежать внутри поля видимости - его надо обработать
    //деление на 0 - очень редкое исключение, я решил его не обрабатывать
    public void CohenSutherlandAlgorithm(MainPanel mainPanel){
        Point rPoint = mainPanel.getRPoint();
        int rWidth = mainPanel.getRWidth(), rHeight = mainPanel.getRHeight();
        List<Integer> codeList = convertToCodes(rPoint, rWidth, rHeight);
        List<Point> tempList = new ArrayList<>();
        for (int i = 0; i < lineCount; i++){
            int a = codeList.get(2*i), b = codeList.get(2*i + 1);
            if (a == 0 && b == 0){
                //do nothing
            }
            //у не_равно приоритет больше, чем у побитового И
            else if ((a & b) != 0) //он не добавляется в итоговый список
                continue;
            else{
                Point p1 = new Point(lineList.get(2*i)), p2 = new Point(lineList.get(2*i + 1));
                //для дополнительной проверки в конце
                Point tempP1 = new Point(p1), tempP2 = new Point(p2);
                //пересечение с верхней гранью
                int x = p1.x + (rPoint.y - p1.y)*(p2.x - p1.x)/(p2.y - p1.y);
                // y нет, потому что мы знаем y_координату верхней грани окна
                if (x >= rPoint.x && x <= rPoint.x + rWidth && (rPoint.y > p1.y || rPoint.y > p2.y)){
                    if (p1.y > p2.y)
                        lineList.set(2*i + 1, new Point(x, rPoint.y));
                    else lineList.set(2*i, new Point(x, rPoint.y));
                }
                //пересечение с левой гранью
                int y = p1.y + (rPoint.x - p1.x)*(p2.y - p1.y)/(p2.x - p1.x);
                if (y >= rPoint.y && y <= rPoint.y + rHeight && (rPoint.x > p1.x || rPoint.x > p2.x)){
                    if (p1.x > p2.x)
                        lineList.set(2*i + 1, new Point(rPoint.x, y));
                    else lineList.set(2*i, new Point(rPoint.x, y));
                }
                //пересечение с нижней гранью
                x = p1.x + (rPoint.y + rHeight - p1.y)*(p2.x - p1.x)/(p2.y - p1.y);
                if (x >= rPoint.x && x <= rPoint.x + rWidth && (rPoint.y + rHeight < p1.y || rPoint.y + rHeight < p2.y)){
                    if (p1.y < p2.y)
                        lineList.set(2*i + 1, new Point(x, rPoint.y + rHeight));
                    else lineList.set(2*i, new Point(x, rPoint.y + rHeight));
                }
                //пересечение с правой гранью
                y = p1.y + (rPoint.x + rWidth - p1.x)*(p2.y - p1.y)/(p2.x - p1.x);
                if (y >= rPoint.y && y <= rPoint.y + rHeight && (rPoint.x + rWidth < p1.x || rPoint.x + rWidth < p2.x)){
                    if (p1.x < p2.x)
                        lineList.set(2*i + 1, new Point(rPoint.x + rWidth, y));
                    else lineList.set(2*i, new Point(rPoint.x + rWidth, y));
                }
                //это вместо стандартной проверки кодов пересечений граней с отрезком
                if (tempP1.equals(lineList.get(2*i)) && tempP2.equals(lineList.get(2*i+1))) continue;
            }
            tempList.add(lineList.get(2*i));
            tempList.add(lineList.get(2*i + 1)); 
        }
        setPointList(tempList);
        mainPanel.setLineList(getPointList());
    }

    /**Возвращается именно копия */
    public List<Point> getPointList(){
        List<Point> newPointsList = new ArrayList<>();
        for (Point p : lineList)
            newPointsList.add((Point)p.clone());
        return newPointsList;
    }
    /**Устанавливается не ссылку, а новый лист! */
    public void setPointList(List<Point> pointsList_){
        lineList.clear();
        for (Point p : pointsList_)
            lineList.add(p);
    }
    
    private List<Integer> convertToCodes(Point rPoint, int rWidth, int rHeight){
        List<Integer> codeList = new ArrayList<>();
        String str = "";
        for (Point p : lineList){
            str += ((p.x < rPoint.x)? "1" : "0");
            str += ((p.x > rPoint.x + rWidth)? "1" : "0");
            str += ((p.y > rPoint.y + rHeight)? "1" : "0");
            str += ((p.y < rPoint.y)? "1" : "0");
            codeList.add(Integer.parseInt(str, 2));
            str = "";
        }
        return codeList;
    }
}
