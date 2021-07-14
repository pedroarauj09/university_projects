package project_java.model.users;

import java.io.Serializable;

public class User implements Serializable{
    
    private String user_id;
    private String name;
    //private String friends; 

    /*----------------------------------*/
    
    /*CONSTRUTORES*/

    public User(){
        this.user_id = "";
    	this.name = "";
    }

    public User(String nid, String nname){
        this.user_id = nid;
        this.name = nname;
    }

    public User(User us){
        this.user_id = us.getUser_id();
        this.name = us.getName();
    }
    /*--------------------------------*/

    /*FUNCOES GET*/

    public String getUser_id(){
        return this.user_id;
    }

    public String getName(){
        return this.name;
    }

    /*-------------------------------*/

    /*OUTRAS FUNCOES*/

    public User clone(){
        return new User(this);
    }

    public String toString(){
        StringBuilder s = new StringBuilder();
        s.append("ID: "+this.getUser_id()+"\nNome: "+this.getName());

        return s.toString();
    }

}
