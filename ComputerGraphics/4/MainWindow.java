
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
public class MainWindow extends JFrame {
    private LineContainer lineContainer = new LineContainer();
    private MainPanel mainPanel = new MainPanel(lineContainer.getPointList()); 
    private JButton button = new JButton("Показать отрезки");
    MainWindow(){
        add(mainPanel);
        add(button);
        setTitle("Четвёртая лаба");
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1080, 720);
        setLocationRelativeTo(null);
        setVisible(true);
        setResizable(false);

        button.setBounds(925, 650, 140, 35);
        button.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e) {
                lineContainer.CohenSutherlandAlgorithm(mainPanel);
                mainPanel.setChecked(true);
                button.setEnabled(false);
                mainPanel.repaint();
            }
        });
    }
}
