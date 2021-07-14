package project_java.model.business;

import java.util.Map;
import java.util.Set;

public interface MapBusInterface {
    Map<String,Business> getMap();
    Set<String> get_key();
    void addS(Business b);
}
