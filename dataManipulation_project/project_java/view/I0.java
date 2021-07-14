package project_java.view;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class I0 {

    /** Printar qualquer coisa */
    public void printSomething(String coisa){
        System.out.println(coisa);
    }
    
    /** Ler uma opção correta do usuário */
    public int lerOpcaoMenu(int nopcoes){
        int op;
        Scanner is = new Scanner(System.in);
        
        System.out.print("Opção: ");
        try {
            op = is.nextInt();
        }
        catch (InputMismatchException e) { // Não foi inscrito um int
            op = -1;
        }
        if (op<=0 || op > nopcoes) {
            System.out.println("Opção Inválida!!!");
            op = -1;
        }
        return op;
    }
    // ---------------------------- ----------------------------
    
    /**     I/o relacionado aos ficheiros  */

    public int ask(String question){
        System.out.println(question);
        Scanner is = new Scanner(System.in);
        String want = is.nextLine();
        if (want.toLowerCase().equals("sim")) return 1;
        else return 0;

    }
    public String getPath(String name){
        System.out.println("Digite o path para o ficheiro " + name+ ": ");
        Scanner is = new Scanner(System.in);
        String path;
        path = is.nextLine();
        return path;
    }

    // ---------------------------- ----------------------------
    //                      * MENUS *

    
    
    /** Menu principal */

    public int menuPrincipal(){
        int opcao = -1;
        showMenuPrincipal();
        while(opcao == -1){
            opcao = lerOpcaoMenu(5);
        }
        if(opcao == 5) opcao = -1;
        return opcao;
    }

    public void showMenuPrincipal(){
        StringBuilder sb = new StringBuilder();
        
        sb.append("\n O que deseja fazer agora? \n\n")
        .append("*Opções:\n")
        .append("-> 1. Gravar a estrutura de dados em um ficheiro\n")
        .append("-> 2. Carregar a ultima estrutura de dados gravada\n")
        .append("-> 3. Querys\n")
        .append("-> 4. Estatísticas\n")
        .append("-> 5. Sair\n\n");

        System.out.println(sb.toString());
    }

    // +++++++++++++++++++++++++++++++++++++++

    /** Menus Stats */

    public int menuStats(){
        int opcao = -1;
        showMenuStats();
        while(opcao == -1){
            opcao = lerOpcaoMenu(2);
        }
        return opcao;
    }
    


    public void showMenuStats(){
        StringBuilder sb = new StringBuilder();
        
        sb.append("\n Qual grupo de Stats desejas? \n\n")
        .append("*Opções:\n")
        .append("-> 1. Grupo 1\n")
        .append("-> 2. Grupo 2\n\n");
        System.out.println(sb.toString());
    }
    
    


    public void showGp1Stats(List<String> filesName, int noImpact, int wrongRev, int bus_tot, int user_tot, 
                int bus_review, int bus_not_review, int activeUsers){
        StringBuilder sb = new StringBuilder();
        
        sb.append("\n --- Estatísticas 1 ---\n\n")
        .append("Nomes dos ficheiros lidos:  ");
        for(String a : filesName){
            sb.append(a+" | ");
        }
        sb.append("\nNúmero de reviews sem impacto: ").append(noImpact + "\n");
        sb.append("\nNúmero de registos reviews errados: ").append(wrongRev + "\n");
        sb.append("\nNúmero total de negócios: ").append(bus_tot + "\n");
        sb.append("\nNúmero total de users: ").append(user_tot + "\n");
        sb.append("\nNúmero total de negócios diferentes avaliados: ").append(bus_review + "\n");
        sb.append("\nNúmero total de negócios não avaliados: ").append(bus_not_review + "\n\n");
        sb.append("\nNúmero total de users que fizeram avaliação: ").append(activeUsers + "\n\n");
        System.out.println(sb.toString());
    }


    public void showGp2Stats(Map<Integer,Integer> totRevMes, Map<Integer, Float> map, float f){
        StringBuilder sb = new StringBuilder();
        
        sb.append("\n --- Estatísticas 2 ---\n\n\n")
        .append(" --- * Numero total de reviews por mês * --- \n\n");
        sb.append(showReviewsMes(totRevMes));
        
        sb.append("\n\n\n --- * Media de stars por mês * --- \n\n");
        sb.append(showMediaMes(map));
        sb.append("\n Número global de stars: " + f + "\n\n");

        System.out.println(sb.toString());
    }


    // * PRINT STATS RESULTS *

    public String showMediaMes(Map<Integer,Float> m){
        StringBuilder sb = new StringBuilder();
        m.entrySet().forEach(a -> {
            sb.append("Mes: " + a.getKey() + "  Média de stars: " + a.getValue() + "\n");
        });
        return sb.toString();  
    }

    public String showReviewsMes(Map<Integer,Integer> m){
        StringBuilder sb = new StringBuilder();
        m.entrySet().forEach(a -> {
            sb.append("Mes: " + a.getKey() + "  total de reviews: " + a.getValue() + "\n");
        });
        return sb.toString();  
    }
    
    // +++++++++++++++++++++++++++++++++++++++

    /** Menu das Querys */

    public int queryMenu(){
        int opcao = -1;
        showQueryMenu();
        while(opcao == -1){
            opcao = lerOpcaoMenu(2);
        }
        return opcao;
    }
    


    public void showQueryMenu(){
        StringBuilder sb = new StringBuilder();
        
        sb.append("\n Querys disponíveis: \n\n")
        .append("*Opções:\n")
        .append("-> 1. Lista alfabética dos negócios nunca avaliados, e o número total destes\n")
        .append("-> 2. Dê um mês e ano (válidos), e veja o número total de reviews, e o número total de diferentes users que o fez \n\n");
        System.out.println(sb.toString());
    }

    // View Query 1
    public void showQ1(List<String> allbus, int nBus){
        StringBuilder sb = new StringBuilder();
        sb.append("Lista alfabética dos negócios:\n");
        for(String a : allbus){
            sb.append(a + "\n");
        }
        sb.append("\n\n Número total: " + nBus + "\n");
        System.out.println(sb.toString());
    }
    
    // View Query 2
    public int getAno_mes(String a){
        int op = -1;
        Scanner is = new Scanner(System.in);
        System.out.print("Digite um " + a + ":  ");
        while(op == -1){
            try {
                op = is.nextInt();
            }
            catch (InputMismatchException e) { // Não foi inscrito um int
                op = -1;
                System.out.print("Opção Inválida, tente novamente: ");
            } 
        }
        return op;   
    }
    public void showQ2(int totalRev, int userDif){
        StringBuilder sb = new StringBuilder();
        sb.append("\n\n Número total de reviews: " + totalRev + "\n");
        sb.append("\n\n Número total de users diferentes: " + userDif + "\n");
        System.out.println(sb.toString());
    }

    // ------------------------------------------------------
    //              * TESTES *

    public void imprimeLoadFich(long time, String tipo){
        System.out.println("Tempo de carregamento do ficheiro " + tipo + ": " + time + " sec\n");    
    }
    

    public void imprimeExecTime(long time){
        System.out.println("Tempo de execução: " + time + " sec\n");    
    }


}
