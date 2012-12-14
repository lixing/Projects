package puzzle.game;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;


public class DataAccess {

	public static final String USERNAME = "username";
	public static final String TIME = "time";
	public static final String RANK = "rank";

	

	private static final String DATABASE_NAME = "kamy.db";
	SQLiteDatabase db;
	Context context;

	DataAccess(Context _context) {
		context = _context;

		db = context.openOrCreateDatabase(DATABASE_NAME, Context.MODE_PRIVATE,
				null);
		CreateTable4();
		CreateTable5();
		CreateTable6();
	
		close();
	}
	

	public void CreateTable4() {
		try {
			db.execSQL("CREATE TABLE IF NOT EXISTS level4 (" + "USERNAME TEXT,"
					+ "TIME TEXT," + "RANK TEXT" + ");");
			
		} catch (Exception e) {
	
		}

	}

	public void CreateTable5() {
		try {
			db.execSQL("CREATE TABLE IF NOT EXISTS level5 (" + "USERNAME TEXT,"
					+ "TIME TEXT" + "RANK TEXT" + ");");
			
		} catch (Exception e) {
		
		}
	}

	public void CreateTable6() {
		try {
			db.execSQL("CREATE TABLE IF NOT EXISTS level6 (" + "USERNAME TEXT,"
					+ "TIME TEXT" + "RANK TEXT" + ");");
			
		} catch (Exception e) {
		
		}
	}

	public boolean save(String table,String username, int time, int i) {
		db = context.openOrCreateDatabase(DATABASE_NAME, Context.MODE_PRIVATE,
				null);
		String sql = "";
		try {
			sql = "insert into "+table+" values('" + username + "',  '" + time
					+ "', '" + i + "')";
			db.execSQL(sql);
			
			close();
			return true;

		} catch (Exception e) {
			
			close();
			return false;
		}
	}

	

	

	public Cursor loadRanking(String table,int i) {
		
		db = context.openOrCreateDatabase(DATABASE_NAME, Context.MODE_PRIVATE,
				null);
		
		Cursor cur = db.query(table, new String[] { "USERNAME", "TIME",
				"RANK" }, RANK + "=" + i, null, null, null, null, null);
		
		
		cur.moveToFirst();
		
		return cur;
	}

	

	public void deleteRecord(String table,int i) {
		db = context.openOrCreateDatabase(DATABASE_NAME, Context.MODE_PRIVATE,
				null);
		db.delete(table, RANK + "=" + i, null);

	}

	

	public void close() {
		db.close();
	}

}