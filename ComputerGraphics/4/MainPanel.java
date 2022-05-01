import java.awt.*;
import java.util.List;
import java.util.Random;

import javax.swing.JPanel;
public class MainPanel extends JPanel{
    private final Point rPoint = new Point(70, 100);
    private final int rWidth = 650, rHeight = 400;
    private Random random = new Random();
    private List<Point> lineList;
    private boolean isChecked = false;
    MainPanel(List<Point> lineList){
        setBackground(Color.black);
        setBounds(0, 0, 1080, 720);
        this.lineList = lineList;
    }
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawRect(g);
        for (int i = 0; i < lineList.size() / 2; i++){
            if (!isChecked)
                setRandomColor(g);
            else g.setColor(Color.WHITE);
            drawLine(g, lineList.get(2*i), lineList.get(2*i + 1));
        }
        g.setColor(Color.WHITE);
        if (isChecked)
            g.drawString("Белым помечены линии, полностью или частично входящие в окно", 50, 650);
    }

    private void drawRect(Graphics g){
        Graphics2D gr = (Graphics2D)g;
        gr.setStroke(new BasicStroke(3));
        gr.setColor(Color.CYAN);
        gr.drawRect(rPoint.x, rPoint.y, rWidth, rHeight);
        gr.setStroke(new BasicStroke());
    }
    private void setRandomColor(Graphics g) {
        g.setColor(new Color((random.nextInt() % 255 + 255) % 215 + 40, 
            (random.nextInt() % 255 + 255) % 215 + 40, 
            (random.nextInt() % 255 + 255) % 215 + 40));
    }
    private void drawLine(Graphics g, Point p1, Point p2){
        g.drawLine(p1.x, p1.y, p2.x, p2.y);
    }
    public Point getRPoint(){
        return rPoint;
    }
    public int getRWidth(){
        return rWidth;
    }
    public int getRHeight(){
        return rHeight;
    }
    public void setChecked(boolean b) {
        isChecked = b;
    }
    public void setLineList(List<Point> list){
        lineList.clear();
        for (Point p : list)
            lineList.add(p);
    }
}
