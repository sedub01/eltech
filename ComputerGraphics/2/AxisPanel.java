import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.util.ArrayList;
import java.util.List;

public class AxisPanel extends JPanel {
    private final int SIZE = 755;
    private final int axisIndent = 50;
    private final int dashLength = 10;
    private List<Point> pointsList = new ArrayList<>();
    AxisPanel(){
        setBackground(Color.BLACK);
        setBounds(5, 5, SIZE, SIZE);
        pointsList.add(new Point(20, 30));
        pointsList.add(new Point(400, 60));
        pointsList.add(new Point(50, 270));
        pointsList.add(new Point(400, 150));
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawAxis(g);
        drawDashedBrokenLine(g);
        drawPoints(g);
        drawCurve(g);
    }

    private void drawAxis(Graphics g) {
        Graphics2D gr = (Graphics2D)g;
        gr.setStroke(new BasicStroke(3));
        gr.setColor(Color.WHITE);
        gr.drawLine(0, SIZE - axisIndent, SIZE, SIZE - axisIndent);
        gr.drawLine(axisIndent, 0, axisIndent, SIZE);

        for (int dashLocation = SIZE - axisIndent; dashLocation > 0; dashLocation -= axisIndent)
            g.drawLine(axisIndent, dashLocation, axisIndent + dashLength, dashLocation);
        for (int dashLocation = axisIndent; dashLocation < SIZE; dashLocation += axisIndent)
            g.drawLine(axisIndent + dashLocation, SIZE - axisIndent, axisIndent + dashLocation, SIZE - axisIndent - dashLength);

        g.setFont(new Font("Verdana", Font.BOLD, 14));
        g.drawString("50", axisIndent - 25, SIZE - axisIndent - 50);
        g.drawString("50", axisIndent + 40, SIZE - axisIndent + 15);
    }

    private void drawDashedBrokenLine(Graphics g) {
        Graphics2D f = (Graphics2D) g;
        f.setStroke(new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1, new float[]{10f, 5f}, 0f));
        f.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        for (int i = 0; i < pointsList.size() - 1; i++)
            f.drawLine(pointsList.get(i).x + axisIndent, -pointsList.get(i).y + SIZE - axisIndent, 
            pointsList.get(i + 1).x + axisIndent, -pointsList.get(i + 1).y + SIZE - axisIndent);
        f.setStroke(new BasicStroke()); //устанавливаю по умолчанию
    }

    private void drawPoints(Graphics g){
        for (Point p : pointsList)
        drawPoint(g, p.x + axisIndent, -p.y + SIZE - axisIndent, 7);
    }

    private void drawCurve(Graphics g) {
        g.setColor(Color.RED);
        Graphics2D g2 = (Graphics2D) g;
        int clarity = 400;
        double x[] = new double[clarity], y[] = new double[clarity], t = 0;
        if (pointsList.size() == 3)
            for (int i = 0; i < clarity; i++, t += (double)1 / clarity){
                x[i] = (1 - t)*(1-t)*pointsList.get(0).x + 2*t*(1-t)*pointsList.get(1).x + t*t*pointsList.get(2).x;
                y[i] = (1 - t)*(1-t)*pointsList.get(0).y + 2*t*(1-t)*pointsList.get(1).y + t*t*pointsList.get(2).y;
                g2.draw(new Line2D.Double(x[i] + axisIndent, -y[i] + SIZE - axisIndent,
                                        x[i] + axisIndent, -y[i] + SIZE - axisIndent));
            }
        else if (pointsList.size() == 4)
            for (int i = 0; i < clarity; i++, t += (double)1 / clarity){
                x[i] = (1-t)*(1-t)*(1-t)*pointsList.get(0).x + 3*t*(1-t)*(1-t)*pointsList.get(1).x 
                    + 3*t*t*(1-t)*pointsList.get(2).x + t*t*t*pointsList.get(3).x;
                y[i] = (1-t)*(1-t)*(1-t)*pointsList.get(0).y + 3*t*(1-t)*(1-t)*pointsList.get(1).y 
                    + 3*t*t*(1-t)*pointsList.get(2).y + t*t*t*pointsList.get(3).y;
                g2.draw(new Line2D.Double(x[i] + axisIndent, -y[i] + SIZE - axisIndent,
                    x[i] + axisIndent, -y[i] + SIZE - axisIndent));
            }
        else if (pointsList.size() == 5)
            for (int i = 0; i < clarity; i++, t += (double)1 / clarity){
                x[i] = (1-t)*(1-t)*(1-t)*(1-t)*pointsList.get(0).x + 4*t*(1-t)*(1-t)*(1-t)*pointsList.get(1).x
                    + 6*t*t*(1-t)*(1-t)*pointsList.get(2).x + 4*t*t*t*(1-t)*pointsList.get(3).x + t*t*t*t*pointsList.get(4).x;
                y[i] = (1-t)*(1-t)*(1-t)*(1-t)*pointsList.get(0).y + 4*t*(1-t)*(1-t)*(1-t)*pointsList.get(1).y
                    + 6*t*t*(1-t)*(1-t)*pointsList.get(2).y + 4*t*t*t*(1-t)*pointsList.get(3).y + t*t*t*t*pointsList.get(4).y;
                g2.draw(new Line2D.Double(x[i] + axisIndent, -y[i] + SIZE - axisIndent,
                    x[i] + axisIndent, -y[i] + SIZE - axisIndent));
            }
    }

    private void drawPoint(Graphics g, int x, int y, int thickness){
        g.setColor(Color.GREEN);
        g.fillOval(x - thickness / 2, y - thickness / 2, thickness, thickness);
    }

    public List<Point> getPointList(){
        List<Point> newPointsList = new ArrayList<>();
        for (Point p : pointsList)
            newPointsList.add((Point)p.clone());
        return newPointsList;
    }
    public void setPointList(List<Point> pointsList_){
        pointsList.clear();
        for (Point p : pointsList_)
            pointsList.add(p);
        pointsList_.clear();
    }
}
