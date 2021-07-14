package project_java.model.review;

import java.io.Serializable;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;



public class MapReview implements Serializable , MapRevInterface{
    private Map<String,Review> mReview; 
    
    public MapReview(){
        this.mReview = new HashMap<>();
    }
    public MapReview(Review r){
        this.mReview.put(r.getRev_id(), r.clone());
    }

    public MapReview(MapReview mr){
        this.mReview = mr.getMap();
    }

    public Map<String,Review> getMap(){
        Map<String, Review> aux = new HashMap<>();
        for (Review v : this.mReview.values()) {
            aux.put(v.getRev_id(), v.clone());
        }
        return aux;
    }

    public Collection<Review> val_reviews(){
        return this.mReview.values();
    }

    public void addStruct(Review r){
        this.mReview.put(r.getRev_id(), r.clone());
    }

    public int size(){
        return this.mReview.size();
    }

    public String toString(){
        StringBuilder s = new StringBuilder();
        Iterator<Review> it = this.mReview.values().iterator();
        while(it.hasNext() /* && i < 50*/){
            s.append(it.next().toString());
            
        }
        return s.toString();
    }

    public MapReview clone(){
        return new MapReview(this);
    }
}
