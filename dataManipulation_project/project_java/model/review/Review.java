package project_java.model.review;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Review implements RevInterface, Serializable{
	private String rev_id;
	private String user_id;
	private String bus_id;
	private float stars; 
	private int useful;
	private int funny;
	private int cool;
	private List<Integer> date;//ano;mes;dia;hora;minuto;segundo
	//private String text;

	/*----------------------------------*/
    
    /*CONSTRUTORES*/

	public Review(){
		this.rev_id = "";
		this.user_id = "";
		this.bus_id = "";
		this.date = new ArrayList<>();
		//this.text = "";

	}

	public Review(String nrev_id,String nuser_id, String nbus_id, float nstars, int nuseful, int nfunny, int ncool,ArrayList<Integer> ndate) {
		this.rev_id = nrev_id;
		this.user_id = nuser_id;
		this.bus_id = nbus_id;
		this.stars = nstars;
		this.useful = nuseful;
		this.funny = nfunny;
		this.cool = ncool;
		this.date = new ArrayList<>(ndate);
	}

	public Review(Review rv){
		this.rev_id = rv.getRev_id();
		this.user_id = rv.getUser_id();
		this.bus_id = rv.getBus_id();
		this.stars = rv.getStars();
		this.useful = rv.getUseful();
		this.funny = rv.getFunny();
		this.cool = rv.getCool();
		this.date = rv.getDate();
	}

	/*--------------------------------*/

    /*FUNCOES GET*/

	public String getRev_id(){
		return this.rev_id;
	}

	public String getUser_id(){
		return this.user_id;
	}

	public String getBus_id(){
		return this.bus_id;
	}

	public float getStars(){
		return this.stars;
	}

	public int getUseful(){
		return this.useful;
	}

	public int getFunny(){
		return this.funny;
	}

	public int getCool(){
		return this.cool;
	}

	public Review clone(){
        return new Review(this);
    }

	public ArrayList<Integer> getDate(){
		return new ArrayList<>(this.date);
	}

	public int getMes(){
		
		return (this.date.size() > 1)? this.date.get(1) : -1;
	}
	public int getAno(){
		return this.date.get(0);
	
	}
	public int getDia(){
		return (this.date.size() > 2)? this.date.get(2) : -1;
	}

	/*-------------------------------*/

    /*OUTRAS FUNCOES*/
	
	/*
	public int compare(ArrayList<Integer> a1, ArrayList<Integer> a2){
		int result,i,flag;
		flag = 0; result = 1;
		for(i=0; i < a1.size() && i < a2.size() && flag == 0 ; i++){
			result = Integer.compare(a1.get(i), a2.get(i));
			if(result != 0){
				flag++;
			}
		}
		return result;
	 }
	 */
	public String dateToString(){
        StringBuilder s = new StringBuilder();
		for (Integer i : this.date){
			s.append(i).append("/");
		}
		return s.toString();
	}


	public String toString(){
        StringBuilder s = new StringBuilder();
        s.append("Data: ").append(this.dateToString()).append("\n");
        return s.toString(); 
    }
}
