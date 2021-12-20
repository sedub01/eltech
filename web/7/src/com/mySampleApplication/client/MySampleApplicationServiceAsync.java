package com.mySampleApplication.client;

import com.google.gwt.user.client.rpc.AsyncCallback;

import java.util.List;
/** интерфейс для асинхронного обращения для каждого футболиста*/
public interface MySampleApplicationServiceAsync {
    void getFootballerList(AsyncCallback<List<Footballer>> callback);
    void addFootballer(Footballer footballer, AsyncCallback<Void> asyncCallback);
}
