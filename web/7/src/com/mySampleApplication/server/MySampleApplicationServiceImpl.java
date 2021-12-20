package com.mySampleApplication.server;

import com.google.gwt.user.server.rpc.RemoteServiceServlet;
import com.mySampleApplication.client.Footballer;
import com.mySampleApplication.client.MySampleApplicationService;

import java.util.ArrayList;
import java.util.List;

/** Реализация логики сервера */
public class MySampleApplicationServiceImpl extends RemoteServiceServlet implements MySampleApplicationService {

    private static List<Footballer> footballers = null;
    static {
        footballers = new ArrayList<>();
        footballers.add(new Footballer("Билли Херрингтон", 0, "Калуга", 19000));
        footballers.add(new Footballer("Антон Чехов", 1, "Санкт-Петербург", 30000));
        footballers.add(new Footballer("Илья Антонов", 2, "Екатеринбург", 25000));
        footballers.add(new Footballer("Андрей Сачков", 3, "Вологда", 19000));
    }

    @Override
    public List<Footballer> getFootballerList() {
        return footballers;
    }

    @Override
    public void addFootballer(Footballer footballer) {
        if(footballer != null) footballers.add(footballer);
    }
}