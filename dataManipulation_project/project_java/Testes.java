package project_java;

public class Testes {
    private long loadReviewTime; // Scanner(FileInputStream) { 27 sec} | ReadAllLines(File) { 13 sec } | BufferedReader { 15 sec }
    private long loadBusTime; // Scanner { 1 sec } | BufferedReader { 0.4 sec }
    private long loadUserTime; // Scanner(FileInputStream) 5 min | BufferedReader { 41 sec }
    private long escreveFichTime; // 3 min 
    private long lerFichTime; // nop
    /** STATS 1 :  3 sec */
    /** STATS 2 : 0.5 sec */
    /** QUERY 1 : 3 sec*/
    /** QUERY 2 : 0.2 sec*/

    public Testes(){
        this.loadUserTime = 0;        
        this.loadBusTime = 0;
        this.loadReviewTime = 0;
        this.escreveFichTime = 0;
        this.lerFichTime = 0;
    }

    public void addWriteTime(long time){
        this.escreveFichTime = time;
    }

    public void addReadTime(long time){
        this.lerFichTime = time;
    }


    public void addBusTime(long time){
        this.loadBusTime = time;
    }
    public void addReviewTime(long time){
        this.loadReviewTime = time;

    }
    public void addUserTime(long time){
        this.loadUserTime = time;

    }
    
    public long getBusTime(){
        return this.loadBusTime;
    }
    public long getRevTime(){
        return this.loadReviewTime;
    }
    public long getUsTime(){
        return this.loadUserTime;
    }

    public long getReadTime(){
        return this.lerFichTime;
    }
    public long getWriteTime(){
        return this.escreveFichTime;
    }


}
