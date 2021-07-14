package project_java.model;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;

import java.util.Iterator;
import java.util.List;
import java.util.Map;
import project_java.model.business.MapBusiness;
import project_java.model.review.MapReview;
import project_java.model.review.Review;
import project_java.model.users.MapUsers;

public class GestReviewModel implements Serializable { 
    
    private int review_total; // Número total de reviews dado um ano e mês ( Query 2 )
    private int dif_users; // Número total de users diferentes que fez review dado um mes e ano ( Query 2 )
    private MapReview mR;
    private MapBusiness mB;
    private MapUsers mU;
    private Estatistica stats;
    
    
    public GestReviewModel(){
        
        this.mR = new MapReview();
        this.mB = new MapBusiness();
        this.mU = new MapUsers();
        this.stats = new Estatistica();
        this.dif_users = 0;
        this.review_total = 0;
    }
    public GestReviewModel(GestReviewModel gM){
        
        this.mR = gM.mR.clone();
        this.mB = gM.mB.clone();
        this.mU = gM.mU.clone();
        this.stats = gM.getAllStats();
        this.dif_users = gM.getDifusers();
        this.review_total = gM.getRevTot();
    }
    
    /** GETS */
    public Estatistica getAllStats(){
        return this.stats.clone();
    }
    public MapReview getMapReview(){
        return this.mR.clone();
    } 
    public MapBusiness getMapBus(){
        return this.mB.clone();
    }

    
    
    public int getDifusers(){
        return this.dif_users;
    }

    public int getRevTot(){
        return this.review_total;
    }
    
    // clone
    public GestReviewModel clone(){
        return new GestReviewModel(this);
    }

    /** FUNÇÕES AUXILIARES */

    // Adiciona nome do path para o stats
    public void addNameStat(String s){
        this.stats.addName(s);
    } 

    // Adiciona na stats quando um registro lido é incorreto 
    public void addWrongR(){
        this.stats.addWrongR();
    }

    public void addMapRev(MapReview mr){
        this.mR = mr.clone();
    }

    public void addMapBus(MapBusiness mb){
        this.mB = mb.clone();
    }
    
    public void addMapUser(MapUsers mu){
        this.mU = mu.clone();
    }

    public void addNoImpact(){
        this.stats.addNoImpact();
    }

    public void addBusiness_total(){
        this.stats.business_total();
    }
    public void addUsersTotal(){
        this.stats.users_total();
    }

    public void addmapDateR(int mes, Review rev){
        this.stats.addReviewMes(mes,rev);
    }

    public Map<Integer,Integer> getReviewsMes(){
        return this.stats.totalReviewsMes();
    }


    public int doActiveUsers(){
        return this.stats.activeUsers(this.mR.clone());
    }

    /** QUERYS */

    //query 1  , 
    
    public List<String> query1(){
        List<String> list = this.stats.bus_non_available(this.mR.clone(), this.mB.clone());
        return list;
    } 
    

    //query 2-----------------------------------------------------------------------------
    
    
    public void query2(int month,int year) {
        
        Iterator<Review> it = this.mR.val_reviews().iterator();
        List<String> rev = new ArrayList<String>();

        while(it.hasNext()){  
            Review id_atual = it.next();
            if((id_atual.getMes()== month) && (id_atual.getAno() == year)){
                this.review_total++;
                rev.add(id_atual.getUser_id());
            }
        }
        this.dif_users = (int)rev.stream()
                        .distinct()
                        .count(); 
    }

    //query 3--------------------------------------------------------------
    //Dá um user_id, determinar para cada mês : quantas reviews fez,
    //quantos negócios distintos avaliou e que nota média atribuiu.
    public void query3(String b_id){
        int tot_review = 0;
        int bus_dif = 0;
    

        Iterator<Review> it = mR.val_reviews().iterator();

        List<String> rev = new ArrayList<String>();
        

        while(it.hasNext()){                                
            Review id = it.next();
            if((id.getUser_id().equals(b_id))){
                rev.add(id.getUser_id());
            }
        }
        tot_review = (int) rev.stream().distinct().count();

    }
  
    
    //query 5----------------------------------------------------------
    // Dá um user_id e determinar a lista de negócios que mais avaliou( incluindo o nº total), 
    //ordenado por ordem decrescente, e se for quantidade igual ser por alfabética
    
    public void query5(String user_id){

        Iterator<Review> it = mR.val_reviews().iterator();

        List<String> review = new ArrayList<String>();
        
        while(it.hasNext()){
            Review id_atual = it.next();
            if((id_atual.getUser_id().equals(user_id))){
                review.add(id_atual.getBus_id());  
                }
            }
            Collections.sort(review,Collections.reverseOrder()); //precisa achar uma forma de incluir o nº total.
        }
    

    /** Salva-guarda a estrutura do model, e leitura do mesmo */


    public void saveBinary(String file) throws IOException {
        FileOutputStream f = new FileOutputStream(new File(file));
        ObjectOutputStream o = new ObjectOutputStream(f);
        o.writeObject(this);
        o.flush();
        o.close();
    }

    public GestReviewModel readObject(String f) throws IOException, ClassNotFoundException {
        ObjectInputStream i = new ObjectInputStream(new FileInputStream(f));
        GestReviewModel d = (GestReviewModel) i.readObject();
        i.close();
        return d;
    }

}
