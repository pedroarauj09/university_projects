package project_java.model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.stream.Collectors;


import project_java.model.business.MapBusiness;
import project_java.model.review.MapReview;
import project_java.model.review.Review;

public class Estatistica implements Serializable , StatInteface{
    private List<String> filesName;
    
    private int noImpact; // total de reviews sem impacto
    private int wrongRev; // total de review invalidos
    private int bus_tot; // total de negocios
    private int user_tot; // total de usuários
    private int bus_review; // business com avaliação  
    private float mediaRevGlobal;
    private Map<Integer,MapReview> reviewMes;

    public Estatistica(){
        this.filesName = new ArrayList<>();
        this.wrongRev = 0;
        this.mediaRevGlobal = 0;
        this.bus_tot = 0;
        this.user_tot = 0;
        this.noImpact = 0;
        this.bus_review = 0;
        this.reviewMes = new TreeMap<>();
    }

    public Estatistica(Estatistica e){
        this.filesName = e.getFiles();
        this.noImpact = e.getNoImpact();
        this.wrongRev = e.getWrongRev();
        this.bus_tot = e.getBus_tot();
        this.user_tot = e.getUs_Tot();
        this.bus_review = e.getBusRev();
        this.mediaRevGlobal = e.getMediaGlob();
        this.reviewMes = e.getRevMes();


    }

    /** GET AND SETTERS */

    
    public Map<Integer,MapReview> getRevMes(){
        Map<Integer,MapReview> novo = new TreeMap<>();
        novo = this.reviewMes.entrySet().stream().collect(Collectors.toMap(e-> e.getKey(),e->e.getValue().clone()));
        return novo;
    }

    public float getMediaGlob(){
        return this.mediaRevGlobal;
    }

    public int getBusRev(){
        return this.bus_review;
    }
    
    

    public int getUs_Tot(){
        return this.user_tot;
    }

    public int getBus_tot(){
      return this.bus_tot;  
    }

    public int getWrongRev(){
        return this.wrongRev;
    }

    public int getNoImpact(){
        return this.noImpact;
    }

    public ArrayList<String> getFiles() {
        return new ArrayList<>(filesName);
    }


    public void addReviewMes(int mes, Review rev){
        if(this.reviewMes.containsKey(mes)){
            this.reviewMes.get(mes).addStruct(rev);
        }
        else{
            this.reviewMes.put(mes, new MapReview());
            this.reviewMes.get(mes).addStruct(rev);
        }
    }

    public void addWrongR(){
        this.wrongRev++;
    }
    
    public void business_total(){
        this.bus_tot++;
    }

    public void users_total(){
        this.user_tot++;
    }

    public Estatistica clone(){
        return new Estatistica(this);
    }

    public void add_bus_reviwed(int valor ){
        this.bus_review = valor;
    }
    
    public List<String> bus_non_available(MapReview rev,MapBusiness bus){
        Set<String> setBus = bus.get_key();
        List<String> streamRevBus = rev.val_reviews().stream().map(r -> r.getBus_id()).distinct().collect(Collectors.toList());
        int total = streamRevBus.size();
        add_bus_reviwed(total);
        List<String> neverAvail = streamRevBus.stream().filter(b -> !(setBus.contains(b))).sorted().collect(Collectors.toList());
        return neverAvail;     
    }


    public void addName(String s){
        
        this.filesName.add(s);
    }

    public void addNoImpact(){  //reviews sem impacto
        this.noImpact++;
    } 
    public int activeUsers(MapReview rev){
        return (int) rev.val_reviews().stream().map(r -> r.getUser_id()).distinct().count();
        
    }
    

    
    //stats a) return : Total de reviews em cada mês
    public Map<Integer,Integer> totalReviewsMes()
    {
        Map<Integer,Integer> result = new TreeMap<>();
        this.reviewMes.entrySet().forEach(a -> result.put(a.getKey(),a.getValue().size()));
        return result; 
    
    }

    //stats b) return : Média de estrelas em cada mês
    public Map<Integer,Float> mediaReviewsMes()
    {
        Map<Integer, Float> mediasR = new TreeMap<>();
        this.reviewMes.entrySet().forEach(m -> mediasR.put(m.getKey(),m.getValue().val_reviews()
                                                                                 .stream()
                                                                                 .map(r -> r.getStars()).reduce((float) 0, Float::sum)));
                                                                                 
        
        this.mediaRevGlobal = mediasR.values().stream().reduce((float) 0, Float::sum);

        mediasR.replaceAll((k,v)-> v / (this.reviewMes.get(k).size()));

        this.mediaRevGlobal /= this.reviewMes.values().stream().map(mr -> mr.size()).reduce((int) 0, Integer::sum);


        return mediasR;
    }
    
    
    
    

    

}