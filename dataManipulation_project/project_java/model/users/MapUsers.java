package project_java.model.users;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class MapUsers implements Serializable, MapUsInterface{
	private Map<String,User> mapUs;

	public MapUsers(){
		this.mapUs = new HashMap<>();
	}

	public MapUsers(User u){
		this.mapUs.put(u.getUser_id(), u.clone());
	}

    public MapUsers(MapUsers u){
        this.mapUs = u.getMap();
    }

	public void addStruct(User u){
        this.mapUs.put(u.getUser_id(), u.clone());
    }

    public Map<String,User> getMap(){
        Map<String, User> aux = new HashMap<>();
        for (User v : this.mapUs.values()) {
            aux.put(v.getUser_id(), v.clone());
        }
        return aux;
    }
/*
    public String toString(){
        StringBuilder s = new StringBuilder();
        for (User u : this.mapUs.values()){
            s.append(u.toString());
        }
        return s.toString();
    }
*/
    public String toString(){
        int i = 0;
        StringBuilder s = new StringBuilder();
        Iterator<User> it = this.mapUs.values().iterator();
        while(it.hasNext()  && i < 50){
            s.append(it.next().toString());
            i++;
        }
        return s.toString();
    }

    public MapUsers clone(){
        return new MapUsers(this);
    }

}