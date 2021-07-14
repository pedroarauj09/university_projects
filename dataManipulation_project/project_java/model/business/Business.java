package project_java.model.business;

import java.io.Serializable;

public class Business implements Serializable{
    private String bus_id;
    private String name;
    private String city;
    private String state;
    private String categories;

    /*----------------------------------*/
    
    /*CONSTRUTORES*/

    public Business(){
        this.bus_id = "";
    	this.name = "";
    	this.city = "";
    	this.state = "";
    	this.categories = ""; //acho q tem ser uma lista
    }

    public Business(String nbus_id,String nname, String ncity, String nstate, String ncategories){
        this.bus_id = nbus_id;
        this.name = nname;
        this.city = ncity;
        this.state = nstate;
        this.categories = ncategories;
    }

    public Business(Business bs){
        this.bus_id = bs.getBus_id();
        this.name = bs.getName();
        this.city = bs.getCity();
        this.state = bs.getState();
        this.categories = bs.getCategories();
    }

    /*--------------------------------*/

    /*FUNCOES GET*/

    public String getBus_id(){
        return this.bus_id;
    }

    public String getName(){
        return this.name;
    }

    public String getCity(){
        return this.city;
    }

    public String getState(){
        return this.state;
    }

    public String getCategories(){
        return this.categories;
    }

    /*-------------------------------*/

    /*OUTRAS FUNCOES*/

    public Business clone(){
        return new Business(this);
    }

    
}
