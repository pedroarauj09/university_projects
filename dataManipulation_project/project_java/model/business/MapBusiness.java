package project_java.model.business;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MapBusiness implements Serializable,  MapBusInterface{
    private Map<String,Business> MapBus; 
    
    public MapBusiness(){
        this.MapBus = new HashMap<>();
    }

    public MapBusiness(Business b){
        this.MapBus.put(b.getBus_id(), b.clone());
    }

    public MapBusiness(MapBusiness b){
        this.MapBus = b.getMap();
    }

    public Map<String,Business> getMap(){
        Map<String, Business> aux = new HashMap<>();
        for (Business b : this.MapBus.values()) {
            aux.put(b.getBus_id(), b.clone());
        }
        return aux;
    }

    public Set<String> get_key(){
        return this.MapBus.keySet();
    }

    public void addS(Business b){
        this.MapBus.put(b.getBus_id(), b.clone());
    }

    public String toString(){
        StringBuilder s = new StringBuilder();
        for (Map.Entry<String,Business> busEntry : this.MapBus.entrySet()){
            s.append(busEntry.toString());
        }
        return s.toString();
    }

    public MapBusiness clone(){
        return new MapBusiness(this);
    }

   
}
