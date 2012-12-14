package TestTry;

import java.sql.ResultSet;
import java.sql.SQLException;

import junit.framework.TestCase;

public class ConnectSqlTest extends TestCase {
	ConnectSql connectsql=new ConnectSql();
	private ResultSet rs=null;
    private String test="";
    
	public void testOpenConnection() {
		connectsql.OpenConnection();
		try {
			rs=connectsql.SelectInfo("1");
			while(rs.next()){
				test=rs.getString("Name");
			}
			ConnectSqlTest.assertEquals("Dr.Feng",test);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void testCloseConnection() {
		
	}

	public void testUpdateUserInfo() {
		
	}

	public void testSelectInfo() {
		connectsql.OpenConnection();
		
		try {
			rs=connectsql.SelectInfo("1");
			while(rs.next()){
				test=rs.getString("Name");
			}
			ConnectSqlTest.assertEquals("Dr.Feng",test);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public void testSelectRecord() {
		connectsql.OpenConnection();
		
		try {
			rs=connectsql.SelectInfo("3");
			while(rs.next()){
				test=rs.getString("Major");
			}
			ConnectSqlTest.assertEquals("CTV",test);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void testSelectEquipmentString() {
	      connectsql.OpenConnection();
		
		try {
			rs=connectsql.SelectEquipment("2");
			while(rs.next()){
				test=rs.getString("equipment");
			}
			ConnectSqlTest.assertEquals("B",test);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public void testSearchEquipment() {
	      connectsql.OpenConnection();
		
		try {
			rs=connectsql.SearchEquipment("A");
			while(rs.next()){
				test=rs.getString("equipment");
			}
			ConnectSqlTest.assertEquals("A",test);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void testSubstractEquipStringStringStringIntInt() {
		
	}

	public void testModifyInfo() {
		
	}

	public void testSelectMID() {
        connectsql.OpenConnection();
		
		try {
			
			rs=connectsql.SelectMID("1");
			while(rs.next()){
				test=rs.getString("identity");
			}
			
			ConnectSqlTest.assertEquals("manager",test);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void testSelectSID() {
        connectsql.OpenConnection();
		
		try {
			rs=connectsql.SelectSID("3");
			while(rs.next()){
				test=rs.getString("identity");
			}			
			ConnectSqlTest.assertEquals("student",test);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void testSelectid() {
        connectsql.OpenConnection();
		
		try {
			rs=connectsql.Selectid("administrator");
			while(rs.next()){
				test=rs.getString("Name");
			}
			
			ConnectSqlTest.assertEquals("Kathy",test);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void testSelectAll() {
		
	}

	public void testAddEquipment() {
		
	}

	public void testInsertTemp() {
		
	}

	public void testTruncateTemp() {
		
	}

	public void testSelectEquipmentStringString() {
		
	}

	public void testShowEquipment() {
		
	}

	public void testShowEquipmentTemp() {
		
	}

	public void testSelectCredit() {
		 connectsql.OpenConnection();
			
			try {
				rs=connectsql.SelectCredit("4");
				while(rs.next()){
					test=rs.getString("credit");
				}
				ConnectSqlTest.assertEquals("0",test);
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	}



	public void testSelectRecord2() {
		
	}

	public void testReturn() {
		
	}

	public void testSelectEquipment1() {
		 connectsql.OpenConnection();
			
			try {
				rs=connectsql.SelectEquipment1("3");
				while(rs.next()){
					test=rs.getString("equipment");
				}
				ConnectSqlTest.assertEquals("C",test);
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	}

	public void testSelectDepartment() {
		 connectsql.OpenConnection();
			
			ConnectSqlTest.assertEquals("CTV",connectsql.SelectDepartment("3"));
	}

	public void testSubstractEquipStringStringStringInt() {
		
	}

	public void testModifyAmount() {
		
	}
	
	public void testModifyInfo2() {
		
	}


	public void testDeleteEquipment() {
		
	}
	
	public void testSelectDeleteInfo() {
		
	}
	
	
	public void testDeleteBookingInfo() {
		
	}
	

    public void testJudgeExist() {
    	 connectsql.OpenConnection();
    	 String number=connectsql.JudgeExist("1","A","CTV","Tripod_Digital");
    	 ConnectSqlTest.assertEquals("",number);
	}

}
