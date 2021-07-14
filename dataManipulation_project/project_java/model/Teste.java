package project_java.model;

import java.util.Comparator;
import java.util.Map;
import java.util.TreeMap;

public class Teste {
    public static void main(String[] args) {
        Map<Integer,Integer > dates = new TreeMap<>();
        
        dates.put(1, 0);
        dates.put(22, 1);
        dates.put(4, 2);
        dates.put(9, 3);
        dates.put(10, 4);

        dates.entrySet().forEach(System.out::println);

        
    }
}
