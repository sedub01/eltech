import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class figuresConfigPanel extends JPanel{
    JLabel title = new JLabel("Параметры фигур");
    JTextField xField, yField, radiusField;
    JTextField xPointField, yPointField;
    private AxisPanel AXISPANEL;
    figuresConfigPanel(AxisPanel axisPanel){
        AXISPANEL = axisPanel;
        setLayout(null);
        title.setBounds(60, 5, 130, 20);
        add(title);

        addCirclePanel();
        addPointPanel();

        JButton draw = new JButton("Рисовать");
        draw.setBounds(65, 160, 90, 30);
        draw.setFocusPainted(false);
        add(draw);

        draw.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e) {
                AXISPANEL.repaint();
                AXISPANEL.setCircleX(Integer.parseInt(xField.getText()));
                AXISPANEL.setCircleY(Integer.parseInt(yField.getText()));
                AXISPANEL.setRadius(Integer.parseInt(radiusField.getText()));

                AXISPANEL.setFirstX(Integer.parseInt(xPointField.getText()));
                AXISPANEL.setFirstY(Integer.parseInt(yPointField.getText()));
            }
        });

        setBackground(Color.LIGHT_GRAY);
        setBounds(710, 250, 230, 200);
    }
    
    private void addCirclePanel() {
        JLabel circle = new JLabel("Круг");
        circle.setBounds(5, 30, 130, 20);
        add(circle);

        xField = new JTextField(); yField = new JTextField(); radiusField = new JTextField();
        JLabel xLabel = new JLabel("x"), yLabel = new JLabel("y"), radiusLabel = new JLabel("радиус");
        xLabel.setBounds(15, 50, 30, 15);
        xField.setBounds(5, 65, 30, 20);
        add(xField);
        add(xLabel);

        yLabel.setBounds(50, 50, 30, 15);
        yField.setBounds(40, 65, 30, 20);
        add(yField);
        add(yLabel);

        radiusLabel.setBounds(85, 50, 60, 15);
        radiusField.setBounds(75, 65, 60, 20);
        add(radiusField);
        add(radiusLabel);
    }

    private void addPointPanel() {
        JLabel point = new JLabel("Точка");
        point.setBounds(5, 100, 130, 20);
        add(point);
        xPointField = new JTextField(); yPointField = new JTextField();
        JLabel xPointLabel = new JLabel("x"), yPointLabel = new JLabel("y");
        xPointLabel.setBounds(15, 115, 30, 15);
        xPointField.setBounds(5, 130, 30, 20);
        add(xPointField);
        add(xPointLabel);

        yPointLabel.setBounds(50, 115, 30, 15);
        yPointField.setBounds(40, 130, 30, 20);
        add(yPointField);
        add(yPointLabel);
    }
}
