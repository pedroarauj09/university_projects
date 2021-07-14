package project_java.model;

import java.util.List;
import java.util.Map;

import project_java.model.business.MapBusiness;
import project_java.model.review.MapReview;
import project_java.model.review.Review;

public interface StatInteface {
    void addReviewMes(int mes, Review rev);
    void addWrongR();
    void business_total();
    void users_total();
    List<String> bus_non_available(MapReview rev,MapBusiness bus);
    void addName(String s);
    void addNoImpact();
    Map<Integer,Integer> totalReviewsMes();
    Map<Integer,Float> mediaReviewsMes();
}
