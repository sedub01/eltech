package com.mySampleApplication.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.user.cellview.client.CellTable;
import com.google.gwt.user.cellview.client.HasKeyboardSelectionPolicy;
import com.google.gwt.user.cellview.client.TextColumn;
import com.google.gwt.user.client.ui.*;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.DOM;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.view.client.ListDataProvider;

import java.util.List;

/**
 * Entry point classes define <code>onModuleLoad()</code>
 */
public class MySampleApplication implements EntryPoint {
    private final MySampleApplicationServiceAsync myService =
            MySampleApplicationService.App.getInstance();
    @SuppressWarnings("deprecation")
    /** Список футболистов */
    final ListBox footballersListBox = new ListBox(false);
    /** Место для вывода ошибки */
    final Label errorLabel = new Label();

    /** Точка входа в приложение - аналог main */
    public void onModuleLoad() {
        final Button button = new Button("Получить список");
        final Label label = new Label();

        footballersListBox.setFocus(true);
        refreshFootballersList();

        //final CellTable<Footballer> mainTable = createCellTable();

        //создание и заполнение таблицы
        final CellTable<Footballer> mainTable = createCellTable();
        final ListDataProvider<Footballer> mainDataProvider = new ListDataProvider<Footballer>();
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

        final VerticalPanel addPanel = new VerticalPanel();
        addPanel.setHorizontalAlignment(VerticalPanel.ALIGN_RIGHT);
        addPanel.setVisible(true);

        button.addClickHandler(new ClickHandler() {
            public void onClick(ClickEvent event) {
                if (label.getText().equals("")) {
                    //MySampleApplicationService.App.getInstance().getMessage("Hello, World!", new MyAsyncCallback(label));
                } else {
                    label.setText("");
                }
            }
        });
    }

    private CellTable<Footballer> createCellTable(){
        final CellTable<Footballer> table = new CellTable<Footballer>();
        //без этой строчки ничего не будет видно
        table.setKeyboardSelectionPolicy(HasKeyboardSelectionPolicy.KeyboardSelectionPolicy.ENABLED);

        TextColumn<Footballer> nameColumn = new TextColumn<Footballer>() {
            @Override
            public String getValue(Footballer object) {
                return object.getName();
            }
        };
        table.addColumn(nameColumn);
        //...
        TextColumn<Footballer> specColumn = new TextColumn<Footballer>() {
            @Override
            public String getValue(Footballer object) {
                return String.valueOf(object.getSpec());
            }
        };
        table.addColumn(specColumn);

        TextColumn<Footballer> cityColumn = new TextColumn<Footballer>() {
            @Override
            public String getValue(Footballer object) {
                return object.getCity();
            }
        };
        table.addColumn(cityColumn);

        TextColumn<Footballer> salaryColumn = new TextColumn<Footballer>() {
            @Override
            public String getValue(Footballer object) {
                return String.valueOf(object.getSalary());
            }
        };
        table.addColumn(salaryColumn);

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

    private static class MyAsyncCallback implements AsyncCallback<String> {
        private Label label;

        MyAsyncCallback(Label label) {
            this.label = label;
        }

        public void onSuccess(String result) {
            label.getElement().setInnerHTML(result);
        }

        public void onFailure(Throwable throwable) {
            label.setText("Failed to receive answer from server!");
        }
    }
}
