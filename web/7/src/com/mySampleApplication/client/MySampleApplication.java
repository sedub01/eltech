package com.mySampleApplication.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.user.cellview.client.CellTable;
import com.google.gwt.user.cellview.client.HasKeyboardSelectionPolicy;
import com.google.gwt.user.cellview.client.TextColumn;
import com.google.gwt.user.client.ui.*;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.view.client.ListDataProvider;

import java.util.ArrayList;
import java.util.List;

/**Entry point classes define <code>onModuleLoad()</code>*/
public class MySampleApplication implements EntryPoint {
    private final MySampleApplicationServiceAsync myService =
            MySampleApplicationService.App.getInstance();
    /** Список футболистов */
    @SuppressWarnings("deprecation")
    final ListBox footballersListBox = new ListBox(false);
    final String[] roles = {"Вратарь", "Нападающий", "Полузащитник", "Защитник"};

    /** Точка входа в приложение - аналог main */
    public void onModuleLoad() {
        footballersListBox.setFocus(true);
        refreshFootballersList();

        //создание и заполнение таблицы
        final CellTable<Footballer> mainTable = createCellTable();
        final ListDataProvider<Footballer> mainDataProvider = new ListDataProvider<>();
        mainDataProvider.addDataDisplay(mainTable);
        RootPanel.get("PanelContainer").add(mainTable);
        myService.getFootballerList(
                new AsyncCallback<List<Footballer>>() {
                    @Override
                    public void onFailure(Throwable caught) {

                    }

                    @Override
                    public void onSuccess(List<Footballer> result) {
                        mainDataProvider.setList(result);
                    }
                }
        );

        final VerticalPanel salaryPanel = new VerticalPanel();
        salaryPanel.setHorizontalAlignment(VerticalPanel.ALIGN_CENTER);
        salaryPanel.setVisible(true);
        final Label salaryLabel = new Label("Введите минимальную зарплату");
        final Label errorLabel = new Label("Неверно введенная зарплата");
        final Button button = new Button("Получить список");
        final TextBox salaryField = new TextBox();
        salaryField.getElement().setPropertyString("placeholder", "Зарплата");
        errorLabel.setVisible(false);
        salaryPanel.add(salaryLabel);
        salaryPanel.add(errorLabel);
        salaryPanel.add(salaryField);
        salaryPanel.add(button);

        button.addClickHandler(event -> {
            int salary;
            try{
                salary = Integer.parseInt(salaryField.getText());
                List<Footballer> tempList = new ArrayList<>(mainDataProvider.getList());
                tempList.removeIf(boy -> boy.getSalary() < salary);
                mainDataProvider.setList(tempList);
                mainDataProvider.refresh();
                refreshFootballersList();
                salaryField.setText("");
                errorLabel.setVisible(false);
            }
            catch (Exception e){
                errorLabel.setVisible(true);
            }
        });

        RootPanel.get("salaryForm").add(salaryPanel);
    }

    private CellTable<Footballer> createCellTable(){
        final CellTable<Footballer> table = new CellTable<>();
        //без этой строчки ничего не будет видно
        table.setKeyboardSelectionPolicy(HasKeyboardSelectionPolicy.KeyboardSelectionPolicy.ENABLED);

        TextColumn<Footballer> nameColumn = new TextColumn<Footballer>() {
            @Override
            public String getValue(Footballer object) {
                return object.getName();
            }
        };
        table.addColumn(nameColumn, "Имя");//колонка, ее название

        TextColumn<Footballer> specColumn = new TextColumn<Footballer>() {
            @Override
            public String getValue(Footballer object) {
                return roles[object.getSpec()];
            }
        };
        table.addColumn(specColumn, "Специализация");

        TextColumn<Footballer> cityColumn = new TextColumn<Footballer>() {
            @Override
            public String getValue(Footballer object) {
                return object.getCity();
            }
        };
        table.addColumn(cityColumn, "Город");

        TextColumn<Footballer> salaryColumn = new TextColumn<Footballer>() {
            @Override
            public String getValue(Footballer object) {
                return String.valueOf(object.getSalary());
            }
        };
        table.addColumn(salaryColumn, "Зарплата");

        return table;
    }

    private void refreshFootballersList(){
        myService.getFootballerList(new AsyncCallback<List<Footballer>>() {
            @Override
            public void onFailure(Throwable caught) {

            }

            @Override
            public void onSuccess(List<Footballer> result) {
                footballersListBox.clear();
                for (Footballer boy : result)
                    footballersListBox.addItem(boy.getName());
            }
        });
    }
}
