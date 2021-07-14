package project_java.model.review;

import java.util.Collection;
import java.util.Map;

public interface MapRevInterface {
    Map<String,Review> getMap();
    Collection<Review> val_reviews();
    void addStruct(Review r);
    int size();
}
