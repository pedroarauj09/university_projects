package project_java.controller;
import project_java.Testes;
import project_java.model.GestReviewModel;
import project_java.model.business.Business;
import project_java.model.business.MapBusiness;
import project_java.model.review.MapReview;
import project_java.model.review.Review;
import project_java.model.users.MapUsers;
import project_java.model.users.User;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;  
import java.io.IOException;
import java.util.ArrayList;  
import java.util.Arrays;



public class DataLoader{
    
// ---------------------------- * READ REVIEW *

    public ArrayList <Integer> getDataInts(String s){
        String s2[] = s.split("-|:| ");
        ArrayList <Integer> dataI = new ArrayList<Integer>(Arrays.asList(Integer.parseInt(s2[0]),
                                                                        Integer.parseInt(s2[1]),
                                                                        Integer.parseInt(s2[2])
                                                                        ));
        return dataI;
    }

// ------ BufferedReader    
 
public void loadReview(GestReviewModel gM, String path, Testes t) throws IOException{
        

    MapReview mr = new MapReview();
    // Rafa: String readPath = (path.equals(""))? "C:/Users/rafael/Documents/li3/input_files/reviews_1M.csv" : path;
    String readPath = (path.equals(""))? "input-files/reviews_1M.csv" : path;
    gM.addNameStat(readPath);
    String[] reviewLine = null;
    long tempoInicio = System.currentTimeMillis();
    

    File f = new File(readPath);
    try (BufferedReader b = new BufferedReader(new FileReader(f))) { 
        String line = "";
        int firstLine = 0;
        while ((line = b.readLine()) != null) { 
            if(firstLine!=0){
                reviewLine = line.split(";");
                if (reviewLine.length != 9) gM.addWrongR();
                else{
                    String rev_id = reviewLine[0];
                    String user_id = reviewLine[1];
                    String bus_id = reviewLine[2];
                    float stars = Float.parseFloat(reviewLine[3]);
                    int useful = Integer.parseInt(reviewLine[4]);
                    int funny = Integer.parseInt(reviewLine[5]);
                    int cool = Integer.parseInt(reviewLine[6]);
                    if((useful+funny+cool)==0) gM.addNoImpact();
                    ArrayList <Integer> data = this.getDataInts(reviewLine[7]);
                    Review review = new Review(rev_id,user_id,bus_id,stars,useful,funny,cool,data);
                    int mes = data.get(1);
                    gM.addmapDateR(mes,review);
                    mr.addStruct(review);
                }
            }
            else firstLine++;
        }        
    }
    
    catch(IOException exc) { 
        System.out.println("Erro na lida do arquivo" + exc.getMessage());
    }

    
    long totalTime = (System.currentTimeMillis()-tempoInicio)/1000;
    t.addReviewTime(totalTime);

    gM.addMapRev(mr);
    }
    


// ------ READ ALL LINES
 
/*
    public void loadReview(GestReviewModel gM, String path, Testes t) throws IOException{
        

        MapReview mr = new MapReview();
        // Rafa: String readPath = (path.equals(""))? "C:/Users/rafael/Documents/li3/input_files/reviews_1M.csv" : path;
        String readPath = (path.equals(""))? "input-files/reviews_1M.csv" : path;
        gM.addNameStat(readPath);
        String[] reviewLine = null;
        long tempoInicio = System.currentTimeMillis();
        

        List<String> lines;
        try { 
            lines = Files.readAllLines(Paths.get(readPath), StandardCharsets.UTF_8); 
            int firstLine = 0;
            for(String line : lines) {          
                if(firstLine!=0){
                    reviewLine = line.split(";");
                    if (reviewLine.length != 9) gM.addWrongR();
                    else{
                        String rev_id = reviewLine[0];
                        String user_id = reviewLine[1];
                        String bus_id = reviewLine[2];
                        float stars = Float.parseFloat(reviewLine[3]);
                        int useful = Integer.parseInt(reviewLine[4]);
                        int funny = Integer.parseInt(reviewLine[5]);
                        int cool = Integer.parseInt(reviewLine[6]);
                        if((stars+funny+cool)==0) gM.addNoImpact();
                        ArrayList <Integer> data = this.getDataInts(reviewLine[7]);
                        Review review = new Review(rev_id,user_id,bus_id,stars,useful,funny,cool,data);
                        int mes = data.get(1);
                        gM.addmapDateR(mes,review);
                        mr.addStruct(review);
                    //i++;
                    }
                }
                else firstLine++;
            }
        }
        
        catch(IOException exc) { 
            System.out.println("Erro na lida do arquivo" + exc.getMessage());
            lines = new ArrayList<>(); }

        
        long totalTime = (System.currentTimeMillis()-tempoInicio)/1000;
        t.addReviewTime(totalTime);
    
        gM.addMapRev(mr);
        }
*/

// ------ SCANNER
    /* 
    public void loadReview(GestReviewModel gM, String path, Testes t) throws IOException{
        String line = "";  

        MapReview mr = new MapReview();
        // Rafa: String readPath = (path.equals(""))? "C:/Users/rafael/Documents/li3/input_files/reviews_1M.csv" : path;
        String readPath = (path.equals(""))? "input-files/reviews_1M.csv" : path;
        gM.addNameStat(readPath);
        FileInputStream inputStream = null;
        Scanner sc = null;
        //int invalid = 0;
        String[] reviewLine = null;
        long tempoInicio = System.currentTimeMillis();
        try {
            inputStream = new FileInputStream(readPath);
            sc = new Scanner(inputStream, "UTF-8");
            line = sc.nextLine();
            //int i = 0;
            //int j = 0;
            while (sc.hasNextLine()){
                line = sc.nextLine();
                reviewLine = line.split(";");
                if (reviewLine.length != 9) gM.addWrongR();
                else{
                    String rev_id = reviewLine[0];
                    String user_id = reviewLine[1];
                    String bus_id = reviewLine[2];
                    float stars = Float.parseFloat(reviewLine[3]);
                    int useful = Integer.parseInt(reviewLine[4]);
                    int funny = Integer.parseInt(reviewLine[5]);
                    int cool = Integer.parseInt(reviewLine[6]);
                    if((stars+funny+cool)==0) gM.addNoImpact();
                    ArrayList <Integer> data = this.getDataInts(reviewLine[7]);
                    Review review = new Review(rev_id,user_id,bus_id,stars,useful,funny,cool,data);
                    int mes = data.get(1);
                    gM.addmapDateR(mes,review);
                    mr.addStruct(review);
                //i++;
                }
                //stat.add_bus_not_reviwed();
                //j++;
            }
            //System.out.println(i);
            //System.out.println(j);
            // note that Scanner suppresses exceptions
            if (sc.ioException() != null) {
                throw sc.ioException();
            }
            long totalTime = (System.currentTimeMillis()-tempoInicio)/1000;
            t.addReviewTime(totalTime);


        } 
        finally {
            if (inputStream != null) {
                inputStream.close();
            }
            if (sc != null) {
                sc.close();
                }
        }
        

        gM.addMapRev(mr);
        }
        */
// ------------------------------------------------------------------------------------------
//                             * READ BUSINESS *


// ----- BufferedReader
public void loadBusiness(GestReviewModel gM, String path, Testes t) throws IOException{
    String line = "";

    MapBusiness mb = new MapBusiness();
    String readPath = (path.equals(""))? "input-files/business_full.csv" : path;
    gM.addNameStat(readPath);
    String[] busLine = null;
    long tempoInicio = System.currentTimeMillis();


    File f = new File(readPath);
    try (BufferedReader b = new BufferedReader(new FileReader(f))) { 
        int firstLine = 0;
        while ((line = b.readLine()) != null) { 
            if(firstLine!=0){
                busLine = line.split(";");
                if(busLine.length == 5){
                    String busId = busLine[0];
                    String busName = busLine[1];
                    String busCity = busLine[2];
                    String busState = busLine[3];
                    String busCat = busLine[4];  
                    Business mBus = new Business(busId,busName,busCity,busState,busCat);
                    mb.addS(mBus);
                    gM.addBusiness_total();   
                }
            }
            else firstLine++;
        }
    }
    catch(IOException exc) { 
        System.out.println("Erro na lida do arquivo" + exc.getMessage());
    }
      
    long totalTime = (System.currentTimeMillis()-tempoInicio);
    t.addBusTime(totalTime);
    
    
    gM.addMapBus(mb); 
}

//----- SCANNER
/*
    public void loadBusiness(GestReviewModel gM, String path, Testes t) throws IOException{
        String line = "";

        MapBusiness mb = new MapBusiness();
        String readPath = (path.equals(""))? "input-files/business_full.csv" : path;
        gM.addNameStat(readPath);
        FileInputStream inputStream = null;
        Scanner sc = null;
        //int invalid = 0;
        String[] busLine = null;
        long tempoInicio = System.currentTimeMillis();

        try{
            inputStream = new FileInputStream(readPath);
            sc = new Scanner(inputStream, "UTF-8");
            line = sc.nextLine();
            while(sc.hasNextLine()){
                line = sc.nextLine();
                busLine = line.split(";");
                if(busLine.length == 5){
                    String busId = busLine[0];
                    String busName = busLine[1];
                    String busCity = busLine[2];
                    String busState = busLine[3];
                    String busCat = busLine[4];  
                    Business mBus = new Business(busId,busName,busCity,busState,busCat);
                    mb.addS(mBus);
                    gM.addBusiness_total();   
                }
                
            }

            if (sc.ioException() != null) {
                throw sc.ioException();
            }
            long totalTime = (System.currentTimeMillis()-tempoInicio)/1000;
            t.addBusTime(totalTime);

        } 
        finally {
            if (inputStream != null) {
                inputStream.close();
            }
            if (sc != null) {
                sc.close();
                }
        }
        
        
        gM.addMapBus(mb); 
    }
*/
// ------------------------------------------------------------------------------------------
//                              * READ USERS *     
    // -------- BufferedReader

    public void loadUsers(GestReviewModel gM, String path, Testes t) throws IOException{
        String line = "";

        MapUsers mu = new MapUsers();
        String readPath = (path.equals(""))? "input-files/users_full.csv" : path;
        gM.addNameStat(readPath);
        String[] userLine = null;
        long tempoInicio = System.currentTimeMillis();
       

        File f = new File(readPath);
        try (BufferedReader b = new BufferedReader(new FileReader(f))) { 
            int firstLine = 0;
            while ((line = b.readLine()) != null) { 
                if(firstLine!=0){    
                    userLine = line.split(";");
                    if (userLine.length == 3){
                        String user_id = userLine[0];
                        String user_name = userLine[1];
                        User mUser = new User(user_id,user_name);
                        mu.addStruct(mUser);
                        gM.addUsersTotal();
                        //count++;
                    }
                }
                else firstLine++;
                
            }
        } 
        catch(IOException exc) { 
            System.out.println("Erro na lida do arquivo" + exc.getMessage());
        }
        
        long totalTime = (System.currentTimeMillis()-tempoInicio)/1000;
        t.addUserTime(totalTime);
        
        gM.addMapUser(mu);
    }    
}

    
    // ------ SCANNER
    /*
    public void loadUsers(GestReviewModel gM, String path, Testes t) throws IOException{
        String line = "";

        MapUsers mu = new MapUsers();
        String readPath = (path.equals(""))? "input-files/users_full.csv" : path;
        gM.addNameStat(readPath);
        FileInputStream inputStream = null;
        Scanner sc = null;
        String[] userLine = null;
        //int invalid = 0;
        //int count = 0;
        long tempoInicio = System.currentTimeMillis();
       
        try{
            inputStream = new FileInputStream(readPath);
            sc = new Scanner(inputStream, "UTF-8");
            line = sc.nextLine();
            while (sc.hasNextLine()) {
                line = sc.nextLine();
                userLine = line.split(";");
                if (userLine.length == 3){
                    String user_id = userLine[0];
                    String user_name = userLine[1];
                    User mUser = new User(user_id,user_name);
                    mu.addStruct(mUser);
                    gM.addUsersTotal();
                    //count++;
                }
                
            }
            //System.out.println(invalid);
            //System.out.println(count);
            long totalTime = (System.currentTimeMillis()-tempoInicio)/1000;
            t.addUserTime(totalTime);

            if (sc.ioException() != null) {
                throw sc.ioException();
            }
        } 
        finally {
            if (inputStream != null) {
                inputStream.close();
            }
            if (sc != null) {
                sc.close();
                }
        }
        
        gM.addMapUser(mu);
    }    
}
    */