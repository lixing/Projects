package TestTry;

import java.awt.HeadlessException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.swing.JOptionPane;

public class ConnectSql {
	Connection conn = null;
	  ResultSet  rs = null;
	  Statement st = null;
	  Statement st2 = null;
	  
		public void OpenConnection(){
			try { 
			Class.forName("com.mysql.jdbc.Driver"); 
			String user = "root";  
			//String passwd = "123456"; 
			String passwd="admin";
			String strDBname = "equipment_booking"; 
			String url="jdbc:mysql://localhost:3306/"+strDBname+"?useUnicode=true&;characterEncoding=utf-8";
			conn = DriverManager.getConnection(url,user,passwd);
		
		  }catch(Exception e){
			  System.out.println("ConnectFail."); 
		  }
		 // return conn;
		}
		
		public void CloseConnection()
		{	
			try { 
				conn.close();
				System.out.println("CloseConnection:OK"); 		
			}catch(Exception e){
				  System.out.println("Close Fail."); 
			  }		
		}
	
	public void UpdateUserInfo(String id,String EquipmentID,String name,String major,String e_mail,String telephone,String equipment,String amount,String start_time,String end_time,String reasons,String Status,String category)
	{	
		try {
	    int BookingNumber=1;
	    String  statistic="null";
		st = conn.createStatement(); 
		rs=st.executeQuery("select * from booking_info");
		while(rs.next()){
			BookingNumber=Integer.parseInt(rs.getString("BookingNumber"))+1;
		}
		String sql2="select * from equip_info where Id='"+EquipmentID+"'";
		rs=st.executeQuery(sql2);
		while(rs.next()){
		 statistic=String.valueOf((Integer.parseInt(rs.getString("statistic"))+Integer.parseInt(amount)));
		}
	   
	   String sql="insert into booking_info values ("+BookingNumber+",'"+id+"','"+EquipmentID+"','"+name+"','"+major+"','"+e_mail+"','"+telephone+"','"+equipment+"','"+amount+"','"+start_time+"','"+end_time+"','"+reasons+"','"+Status+"','"+category+"')";
	   st.executeUpdate(sql);
	   String sql1="update equip_info set statistic='"+statistic+"' where Id='"+EquipmentID+"'";
	   
	   st.executeUpdate(sql1);
		}catch(Exception e){
			e.printStackTrace();
			//System.out.println("Close Fail."); 
		  }		 
	}

	public ResultSet SelectInfo(String id)
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from user_info where Id='"+id+"'";
		 rs= st.executeQuery(sql);
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}
	public ResultSet SelectRecord(String id)
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from booking_info where UserID='"+id+"'";
		 rs= st.executeQuery(sql);
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}
	public ResultSet SelectEquipment(String id)
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from equip_info where Id='"+id+"'";
		 rs= st.executeQuery(sql);
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}
	
	public void SubstractEquip(String category,String type,String equipment,int i,int j)
	{    
		try { 
		 String amount_left=String.valueOf(j-i);
		 String sql="update equip_info set amount_allowed='"+amount_left+"' where category='"+category+"' and type='"+type+"' and equipment='"+equipment+"'";		 
		 st.executeUpdate(sql);
		 st.close(); 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
	}
	
	
	
	public void ModifyInfo(String old_id,String new_id,String name,String identity)
	{    
		try { 
		 st = conn.createStatement(); 
		 String sql="update user_info set Id='"+new_id+"',name='"+name+"',identity='"+identity+"' where Id='"+old_id+"'";
		 st.executeUpdate(sql);
		
		 st.close(); 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
	}
	public ResultSet SelectMID(String id)
	{    
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from user_info where Id='"+id+"' and identity='manager'";
		 rs= st.executeQuery(sql); 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }
		return rs;
	}
	public ResultSet SelectSID(String id)
	{    
		System.out.println(id); 
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from user_info where Id='"+id+"' and identity='student'";
		 rs= st.executeQuery(sql); 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }
		return rs;
	}
	public ResultSet Selectid(String identity)
	{    
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from user_info where identity='"+identity+"'";
		 rs= st.executeQuery(sql); 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }
		return rs;
	}
	public ResultSet SelectAll()
	{    
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from user_info where identity='manager' or identity='student'";
		 rs= st.executeQuery(sql);
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }
		return rs;
	}
	public void AddEquipment(String category,String type,String name,String description,String amount)
	{
		try { 
		st = conn.createStatement(); 
	  st.executeUpdate("insert into equip_info values (default,'"+category+"','"+type+"','"+name+"','"+description+"','"+amount+"','0','"+amount+"','0')"); 
	  
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }		 
	}
	
	public void insertTemp(String category,String type,String name,String description,String amount)
	{
		try { 
		st = conn.createStatement(); 
	
	  st.executeUpdate("insert into temp values ('"+category+"','"+type+"','"+name+"','"+description+"','"+amount+"')"); 
	 
		}catch(Exception e){
			  System.out.println("Close Fail!!!!!!!!."); 
		  }		 
	}
	
	public void truncateTemp()
	{
		try { 
		st = conn.createStatement(); 
		st.executeUpdate("truncate table temp");
	 
		}catch(Exception e){
			  System.out.println("Close Fail!!!!!!!!."); 
		  }		 
	}
	
	public ResultSet SelectEquipment(String category,String type)
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from equip_info where category='"+category+"'"+"and type='"+type+"'";
		 rs= st.executeQuery(sql);
         
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}

	public ResultSet SearchEquipment(String equipment)
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from equip_info where equipment='"+equipment+"'";
		 rs= st.executeQuery(sql);
         
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}
	public void AddStatistic(String EquipmentID,String number)
	{
		try {
		 st = conn.createStatement();
		 int a=0;
		 String sql="select statistic from equip_info where Id='"+EquipmentID+"'";
		 rs= st.executeQuery(sql);
		 while(rs.next()){
			 a=Integer.parseInt(number)+Integer.parseInt(rs.getString("statistic"));
		 }
		 String statistic=String.valueOf(a);
		 sql="update equip_info set statistic='"+statistic+"' where Id='"+EquipmentID+"'";
		 st.executeUpdate(sql);
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		
	}
	
	public ResultSet ShowEquipment(String dep)
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from equip_info where category='"+dep+"'";
		 rs= st.executeQuery(sql);
         
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}
	
	public ResultSet ShowEquipmentTemp()
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from temp";
		 rs= st.executeQuery(sql);
         
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}
	
	public ResultSet SelectCredit(String id)
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from user_info where Id='"+id+"'";
		 rs= st.executeQuery(sql);
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}

	public ResultSet SelectRecord2(String status,String dep)
	{
	
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from booking_info where status='"+status+"' and category='"+dep+"'";
		 rs= st.executeQuery(sql);
		}catch(Exception e){
			  
			  e.printStackTrace();
		  }	
		return rs;
	}
	
	public void Return(String number, int score)
	{
		
		try { 
			String id="";
			int credit=0;
			String equipment="";
			int amount=0;
			int statistic=0;
			st = conn.createStatement();
			st2 = conn.createStatement();
			 String sql="update booking_info set status='returned' where BookingNumber="+number;
			 st.executeUpdate(sql);
			 sql="select * from booking_info where BookingNumber="+number;
			 ResultSet rs=st.executeQuery(sql);
			 while(rs.next()){
				 id=rs.getString("UserID");
				 equipment=rs.getString("EquipmentID");
				 amount=Integer.parseInt(rs.getString("amount"));
			 }
			
			 ResultSet rs2=st2.executeQuery("select * from user_info where Id='"+id+"'");
			 while(rs2.next()){
				 credit=Integer.parseInt(rs2.getString("credit"));
			 }
			 if(score==0)
			 credit=credit+1;
			 else
				 credit=credit+score;
			 st2.close();
			
				st2 = conn.createStatement();
			 sql="update user_info set credit='"+credit+"' where Id="+id;
			 st2.executeUpdate(sql);
			 st2.close();
				st2 = conn.createStatement();
			 ResultSet rs3=st2.executeQuery("select * from equip_info where Id="+equipment);
			 while(rs3.next()){
				 amount=Integer.parseInt(rs3.getString("amount_allowed"))+amount;
			 }
			 
			 sql="update equip_info set amount_allowed='"+amount+"' where Id='"+equipment+"'";
			 st.executeUpdate(sql);
			  st.close(); 
			  st2.close();
			  
		}catch(Exception e){
			e.printStackTrace();
		  }	
	}
	
	public ResultSet SelectEquipment1(String id)
	{
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from equip_info where Id='"+id+"'";
		 rs= st.executeQuery(sql);
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return rs;
	}
	public String SelectDepartment(String id)
	{
		String dep="";
		try { 
		 st = conn.createStatement(); 
		 String sql="select Major from user_info where Id='"+id+"'";
		 rs= st.executeQuery(sql);
		 while(rs.next()){
			 dep=rs.getString("Major");
		 }
		 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		return dep;
	}
	


	
	public void SubstractEquip(String category,String type,String equipment,int i)
	{    
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from equip_info where category='"+category+"' and type='"+type+"' and equipment='"+equipment+"'";
		 rs= st.executeQuery(sql);
		 String amount="";
		 while(rs.next()){
			 int a=(Integer.parseInt(rs.getString("allowed")));
		
			 amount=String.valueOf((Integer.parseInt(rs.getString("allowed")))-i);
		 } 
		 
		 sql="update equip_info set allowed='"+amount+"' where category='"+category+"' and type='"+type+"' and equipment='"+equipment+"'";
		
		 st.executeUpdate(sql);
		  
		  st.close(); 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
	}
	
	public void ModifyAmount(String id,int i,int j,int k)
	{    
		
		
		 try {
			st = conn.createStatement();
			 String sql="update equip_info set Total="+i+", amount_allowed="+j+", broken="+k+" where Id='"+id+"'";
			 st.executeUpdate(sql);
			  st.close(); 
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	
		
	}
	
	public void ModifyInfo2(String id,String name,String functionality)
	{    
		
		
		 try {
			st = conn.createStatement();
			 String sql="update equip_info set equipment='"+name+"', functionality='"+functionality+"' where Id='"+id+"'";
			 st.executeUpdate(sql);
			  st.close(); 
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	
		
	}
	
	public void DeleteEquipment(String id)
	{    
		try { 
		 st = conn.createStatement(); 
		 String sql="delete from equip_info where Id="+id;
		 st.executeUpdate(sql);
		  st.close(); 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
	}
	
	
	
	public void SelectDeleteInfo(String id)
	{    
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from booking_info where EquipmentID="+id+" limit 1";
		 rs=st.executeQuery(sql);
				while(rs.next()){
						int answer=JOptionPane.showConfirmDialog(null, "Warning! Some of the equipment have lent out. If you delete this equipment, the related booking info will be deleted. Click Yes to detele.", null ,JOptionPane.YES_NO_OPTION);
						if(answer==JOptionPane.YES_OPTION)								
							DeleteBookingInfo(id);								   	
					}
				DeleteEquipment(id);
				JOptionPane.showMessageDialog(null,"You have delete the Equipment!");
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
		
	}
	
	public void DeleteBookingInfo(String id)
	{    
		try { 
		 st = conn.createStatement(); 
		 String sql="delete from booking_info where EquipmentID="+id;
		 st.executeUpdate(sql);
		  st.close(); 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	
	}
	
	
	
	public String JudgeExist(String id, String name,String category,String type)
	{
		String number="";
		try { 
		 st = conn.createStatement(); 
		 String sql="select * from equip_info where equipment='"+name+"' and type='"+type+"' and category='"+category+"' and Id!='"+id+"'";
		 rs= st.executeQuery(sql);
		 while(rs.next()){
			 number=rs.getString("Id");
		 }
		 
		}catch(Exception e){
			  System.out.println("Close Fail."); 
		  }	

		return number;
	}
}