import javax.swing.JFrame;
import java.awt.Color;
public class MainWindow extends JFrame{
    private AxisPanel axisPanel = new AxisPanel();
    private ConfigPanel configPanel = new ConfigPanel(axisPanel);
    MainWindow(){
        add(axisPanel);
        add(configPanel);
        setTitle("Вторая лаба");
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1100, 800);
        setLocationRelativeTo(null);
        setBackground(Color.DARK_GRAY);
        setVisible(true);
    }
}
