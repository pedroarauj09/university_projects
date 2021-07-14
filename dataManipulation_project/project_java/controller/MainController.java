package project_java.controller;

import java.io.IOException;
import java.io.Serializable;
import java.util.List;

import project_java.Testes;
import project_java.model.Estatistica;
import project_java.model.GestReviewModel;
import project_java.view.I0;

public class MainController implements Serializable{
    GestReviewModel model;
    I0 view;

    public MainController(){
        this.model = new GestReviewModel();
        this.view = new I0();
    }

    public GestReviewModel readByFileStruct(Testes t) throws ClassNotFoundException, IOException{
        GestReviewModel gM = new GestReviewModel();
        String path = "";
        if(view.ask("Deseja passar o paths do ficheiro lido?(Sim,Nao): ") == 1){
            path = view.getPath("Ficheiro de dados"); 
        }
        String pathFich = (path.equals(""))? "gestReviews.dat" : path;
        long tempoInicio = System.currentTimeMillis();
        gM = gM.readObject(pathFich);
        long totalTime = (System.currentTimeMillis()-tempoInicio)/1000;
        t.addWriteTime(totalTime);
        view.imprimeLoadFich(t.getWriteTime(), "leitura");
        return gM;
    }

    public GestReviewModel readAllFiles(Testes t) throws IOException{
        GestReviewModel gM = new GestReviewModel();
        DataLoader dL = new DataLoader();
        String pathB = "";
        String pathR = "";
        String pathU = "";
        if (view.ask("Deseja passar os paths dos ficheiros?(Sim,Nao): ") == 1){
            pathB = view.getPath("Business");
            pathR = view.getPath("Review");
            pathU = view.getPath("User");
        }
        view.printSomething("Carregando review...\n");
        dL.loadReview(gM, pathR, t);      
        view.printSomething("Review carregado!\n");
        view.imprimeLoadFich(t.getRevTime(), "review");
        
        view.printSomething("Carregando Users...\n");
        dL.loadUsers(gM, pathU,t);      
        view.printSomething("Users carregado\n");
        view.imprimeLoadFich(t.getUsTime(), "user");
        
        
        view.printSomething("Carregando Business...\n");
        dL.loadBusiness(gM, pathB,t);   
        view.printSomething("Business carregado!\n");
        view.imprimeLoadFich(t.getBusTime(), "bus");

        return gM;
    } 

    public void exec(Testes t) throws IOException, ClassNotFoundException{
        
        /** READ DATA */

        if(this.view.ask("Deseja carregar o último ficheiro carregado com os dados?(Sim,Nao): ") == 1){
            this.model = readByFileStruct(t);
        }

        else{
            this.model = readAllFiles(t);
        } 

        /** MENU */
        
        long tempoInicio;
        long totalTime;
        int op = 0;
        while(op != -1){
            op = this.view.menuPrincipal();
            if(op != -1){
                switch(op){
                    case 1:
                        String path = "";
                        if(view.ask("Deseja passar o path do ficheiro que quer gravar?(Sim,Nao): ") == 1){
                                path = view.getPath("Ficheiro de dados"); 
                        }
                        String pathFich = (path.equals(""))? "gestReviews.dat" : path;
                        tempoInicio = System.currentTimeMillis();
                        this.model.saveBinary(pathFich);
                        totalTime = (System.currentTimeMillis()-tempoInicio)/1000;
                        t.addWriteTime(totalTime);
                        view.imprimeLoadFich(t.getWriteTime(), "escrita");
                        break;
                    case 2:
                            this.model = readByFileStruct(t);
                            break;
                    case 3:
                        int opQ = this.view.queryMenu();
                        switch(opQ){
                            case 1:
                                  
                                List<String> lst = this.model.query1();
                                int total = lst.size(); 
                                this.view.showQ1(lst,total);
                                break;
                            case 2:
                                int ano = this.view.getAno_mes("Ano");
                                int mes = this.view.getAno_mes("Mes");
                                  
                                this.model.query2(mes, ano);
                                this.view.showQ2(this.model.getRevTot(), this.model.getDifusers());
                                break;
                        }
                        break;
                        
                    case 4:
                        int opS = view.menuStats();
                        Estatistica stat = new Estatistica();
                        switch(opS){
                            case 1:
                                  
                                List<String> lst = this.model.query1();
                                int totalNotRev = lst.size(); 
                                stat = this.model.getAllStats();
                                this.view.showGp1Stats(stat.getFiles(), stat.getNoImpact(), stat.getWrongRev(), stat.getBus_tot(), 
                                stat.getUs_Tot(), stat.getBusRev(), totalNotRev, this.model.doActiveUsers());
                                
                                break;
                            case 2:
                                  
                                stat = this.model.getAllStats();
                                this.view.showGp2Stats(stat.totalReviewsMes(), stat.mediaReviewsMes(), stat.getMediaGlob());
                                break;    
                        }
                        break;
                }
            }
        }
    }
    
}
