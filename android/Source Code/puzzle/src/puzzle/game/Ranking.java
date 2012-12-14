package puzzle.game;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.database.Cursor;
import android.os.Bundle;
import android.app.ListActivity;
import android.content.Intent;

import android.widget.SimpleAdapter;

public class Ranking extends ListActivity {

	private DataAccess data;

	SimpleAdapter adapter = null;
	List<Map<String, Object>> list = null;
	private int Level;
	public String table;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		   Intent intent = Ranking.this.getIntent();

	        Bundle bl= intent.getExtras(); 
	    	Level=bl.getInt("Level");
	    	if(Level==4){
				table="level4";
			}
		   if(Level==5){
				table="level5";
			}
			if(Level==6){
				table="level6";
				
			}
		data = new DataAccess(this);
		startService(new Intent("puzzle.game.Android.MUSIC"));
		adapter = new SimpleAdapter(this, getData(), R.layout.ranking,
				new String[] { "ranklist" }, new int[] { R.id.ranklist });
		setListAdapter(adapter);
		
	}

	public List<Map<String, Object>> getData() {
		
		list = new ArrayList<Map<String, Object>>();
		Map<String, Object> rank = null;
	
		try {
			//table="level4";
			rank = new HashMap<String, Object>();
			rank.put("ranklist","Ranking of "+table);
			list.add(rank);
			Cursor cur = data.loadRanking(table,1);
			rank = new HashMap<String, Object>();
			
			rank.put("ranklist", "Rank: "+cur.getString(2) + "     Player: " + cur.getString(0) + "     Time: "
					+ cur.getString(1));
			list.add(rank);
			data.close();
		} catch (Exception e) {
           rank = new HashMap<String, Object>();
			
			rank.put("ranklist","No relative record.");
			list.add(rank);
		}

		try {
			Cursor cur = data.loadRanking(table,2);
			rank = new HashMap<String, Object>();
			rank.put("ranklist", "Rank: "+cur.getString(2) + "     Player: " + cur.getString(0) + "     Time: "
					+ cur.getString(1));
			list.add(rank);
			data.close();
		} catch (Exception e) {
		}

		try {
			Cursor cur = data.loadRanking(table,3);
			rank = new HashMap<String, Object>();
			rank.put("ranklist", "Rank: "+cur.getString(2) + "     Player: " + cur.getString(0) + "     Time: "
					+ cur.getString(1));
			list.add(rank);
			data.close();
		} catch (Exception e) {
		}
		try {
			Cursor cur = data.loadRanking(table,4);
			rank = new HashMap<String, Object>();
			rank.put("ranklist", "Rank: "+cur.getString(2) + "     Player: " + cur.getString(0) + "     Time: "
					+ cur.getString(1));
			list.add(rank);
			data.close();
		} catch (Exception e) {
		}
		try {
			Cursor cur = data.loadRanking(table,5);
			rank = new HashMap<String, Object>();
			rank.put("ranklist", "Rank: "+cur.getString(2) + "     Player: " + cur.getString(0) + "     Time: "
					+ cur.getString(1));
			list.add(rank);
			data.close();
		} catch (Exception e) {
		}
		return list;
	}

}
