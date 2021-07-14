package project_java;

import java.io.IOException;

import project_java.controller.MainController;

public class GestReviewApp {
    public static void main(String[] args) throws ClassNotFoundException, IOException {
        MainController mc = new MainController();
        Testes t = new Testes();
        mc.exec(t);
    }   

}
