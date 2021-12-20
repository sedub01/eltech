package com.mySampleApplication.client;

import java.io.Serializable;

public class Footballer implements Serializable {
    private static final long serialVersionUID = 1L;
    private String name;
    private int spec;
    private String city;
    private int salary;

    public Footballer(String name, int spec, String city, int salary) {
        this.name = name;
        this.spec = spec;
        this.city = city;
        this.salary = salary;
    }

    public Footballer(){}

    public String getName() {
        return name;
    }

    public int getSpec() {
        return spec;
    }

    public String getCity() {
        return city;
    }

    public int getSalary() {
        return salary;
    }
}
