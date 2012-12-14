package TestTry;

import java.awt.HeadlessException;
import java.io.File;
import java.io.IOException;
import java.util.Map;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.swing.JOptionPane;
import java.sql.*;

import jxl.Sheet;
import jxl.Workbook;
import jxl.read.biff.BiffException;
/**
 * Servlet implementation class controller
 */
public class ConnectJSP extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private String choiceId="";
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ConnectJSP() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String forward="";
		String department=request.getParameter("dep");
		String choice=request.getParameter("RadioGroup1");
		String id =request.getParameter("id");
		
		TestTry.ConnectSql consql=new TestTry.ConnectSql();
		  consql.OpenConnection();
		@SuppressWarnings("unchecked")
		Map parameters = request.getParameterMap();
		if(parameters.containsKey("login")){			
			String select= request.getParameter("select");
			String password= request.getParameter("password");
			if (id.length()==0){
				JOptionPane.showMessageDialog(null, "Please enter your id");
				forward = "/Login.jsp";
			}
			else if(password.length()==0){
				JOptionPane.showMessageDialog(null, "Please enter your password");
				forward = "/Login.jsp";
				}
			else if(id.length()!=0&&password.length()!=0){
			ResultSet rs=consql.SelectInfo(id);
			String real_password="";
			String identity="";
            String credit="";
			try{
			if(rs.next()){
				real_password=rs.getString("password");
				identity=rs.getString("identity");
				credit=rs.getString("credit");
			if(!password.equals(real_password)){
				JOptionPane.showMessageDialog(null,"Please input the right password");
				forward="/Login.jsp";
			}
			else if(!select.equalsIgnoreCase(identity)){
				JOptionPane.showMessageDialog(null,"Sorry, you can not login as a/an " +select);
				forward="/Login.jsp";
			}
			else if(Integer.parseInt(credit)<30){
				JOptionPane.showMessageDialog(null,"Sorry, you do not have enough credit!");
				forward="/Login.jsp";
			}
			else{
			if(select.equalsIgnoreCase("student")){
				forward="/First_Page.jsp?id="+id;
			}
			else if(select.equalsIgnoreCase("manager")){
				department=consql.SelectDepartment(id);
				forward="/Manager_first_page.jsp?dep="+department;
			}
			else if(select.equalsIgnoreCase("administrator")){
				forward="/Administrator_first_page.jsp?id="+id;
			}
		}}
			else {
				JOptionPane.showMessageDialog(null, "No such person!");
				forward = "/Login.jsp";
			}
			}catch(Exception e){
				  System.out.println("Close Fail."); 
			  }
			
		}
					
		}
		else if(parameters.containsKey("Enter")){
			
		    if(choice.equalsIgnoreCase("booking")){
			    forward="/Booking.jsp?id="+id;
			    }
			else if(choice.equalsIgnoreCase("myrecord")){
		    	forward="/Record.jsp?id="+id;
		    }
			else if(choice.equalsIgnoreCase("View_Modify")){
				ResultSet rs1 = consql.ShowEquipment(department);
				try {
					if(rs1.next()==false){
						JOptionPane.showMessageDialog(null,"No Equipment in your department.");
						forward="/Manager_first_page.jsp?dep="+department;
					}
					else
					forward="/View.jsp?dep="+department;
				} catch (HeadlessException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		    }

			else if(choice.equalsIgnoreCase("Add")){
		    	forward="/Add.jsp?dep="+department;
		    }
			else if(choice.equalsIgnoreCase("lending")){
		    	forward="/LendingRecord.jsp?dep="+department;
		    }
			else if(choice.equalsIgnoreCase("lent")){
				
				ResultSet rs1 = consql.SelectRecord2("returned",department);
				try {
					while(rs1.next()){
						if(rs1.wasNull()){
						JOptionPane.showMessageDialog(null,"No record in your department.");
						forward="/Manager_first_page.jsp?dep="+department;
						}					   	
						}
					forward="/OldRecord.jsp?dep="+department;	
					
				} catch (HeadlessException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		 
		    }

			else if(choice.equalsIgnoreCase("statistic")){
		    	forward="/Statistic.jsp?dep="+department;
		    }
		    
		}else if(parameters.containsKey("OK")){
			id=request.getParameter("id");
			String category=request.getParameter("category");
			String own="";
			own=request.getParameter("own");
			String type=request.getParameter("type");
			String start_date=request.getParameter("start_date");
			String end_date=request.getParameter("end_date");
			java.text.SimpleDateFormat formatter = new java.text.SimpleDateFormat("yyyy-MM-dd");
			java.util.Date currentTime = new java.util.Date();
			String str_date1 = formatter.format(currentTime); 
			
			if(end_date.compareTo(start_date)==-1||start_date.compareTo(str_date1)==-1){
				JOptionPane.showMessageDialog(null,"Choose the right date");
				forward="/Booking.jsp?id="+id;
			}
			else if(!own.equals("")){
				forward="/Search_Result1.jsp?id="+id+"&equipment="+own+"&start_date="+start_date+"&end_date="+end_date;
			}
			else  forward="/Search_Result.jsp?id="+id+"&category="+category+"&type="+type+"&start_date="+start_date+"&end_date="+end_date;
		}
		
		else if(parameters.containsKey("submit")){
			
			 if(choice.equalsIgnoreCase("addequipment")){
				
				String category=request.getParameter("category").toString();
				String type=request.getParameter("type").toString();
				String equipmentname=request.getParameter("equipmentname");
				String Amount=request.getParameter("Amount");
				String description=request.getParameter("Description");
				
				if (equipmentname==""){
					JOptionPane.showMessageDialog(null,"Error! Invalid Equipment Name!");
					forward="/Add.jsp?dep="+department;
			 	}
				else if (category.equals("SELECT CATEGORY")){
			 		JOptionPane.showMessageDialog(null,"Error! Please select a category!");
					forward="/Add.jsp?dep="+department;
			 	}
				else if (type.equals("SELECT TYPE")){
			 		JOptionPane.showMessageDialog(null,"Error! Please select a type!");
					forward="/Add.jsp?dep="+department;
			 	}else if (Amount==""){
			 		JOptionPane.showMessageDialog(null,"Error! Invalid Amount!");
					forward="/Add.jsp?dep="+department;
			 	}else if (description==""){
			 		JOptionPane.showMessageDialog(null,"Error! Invalid Description!");
					forward="/Add.jsp?dep="+department;
			 	}
			 	
				else{
			 
					String number=consql.JudgeExist(id, equipmentname, category, type);
					if(number.equals("")){
						consql.AddEquipment(category,type,equipmentname,description,Amount);
						JOptionPane.showMessageDialog(null,"Successful adding equipment!");
						forward="/Manager_first_page.jsp?dep="+department;
					}
					else{
						String a=request.getParameter("id");
						JOptionPane.showMessageDialog(null,"There is the same equipment record, you need to change the information!");
					
						forward="/Add.jsp?dep="+department;
					}
				
			}
			 }
			else if(choice.equalsIgnoreCase("addamount")){
				
				choiceId=request.getParameter("RadioGroup2");
				if(choiceId==null){
					JOptionPane.showMessageDialog(null,"No record selected!");
					forward="/View.jsp?dep="+department;
				}
				else
				forward="/Modify_amount.jsp?id="+choiceId+"&dep="+department;;
			}
			 

			 
	       else if(choice.equalsIgnoreCase("viewlending")){
				
				choiceId=request.getParameter("RadioGroup2");
				String checkbox=request.getParameter("checkbox");
				String checkbox2=request.getParameter("checkbox2");
				int credit=0;
				if(choiceId!=null){
					if(checkbox!=null)
						credit-=1;
					if(checkbox2!=null)
						credit-=1;
				
				consql.Return(choiceId,credit);
				JOptionPane.showMessageDialog(null,"Successful returned!");
				forward="/Manager_first_page.jsp?dep="+department;
				}
				else{
					JOptionPane.showMessageDialog(null,"No Record selected!");
					forward="/LendingRecord.jsp?dep="+department;
				}
			}
			 
           else if(choice.equalsIgnoreCase("addexcel")){
				
				try {
					ResultSet rs=consql.ShowEquipmentTemp();
					while(rs.next()){
						String category=rs.getString("category");
						String type=rs.getString("type");
						String name=rs.getString("equipment");
						String functionality=rs.getString("functionality");
						String allowed=rs.getString("allowed");
						consql.AddEquipment(category,type,name,functionality,allowed);
					}
					consql.truncateTemp();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				JOptionPane.showMessageDialog(null,"Successful adding equipment!");
				forward="/Manager_first_page.jsp?dep="+department;
			}
			 
           else if(choice.equalsIgnoreCase("ModifyAmount")){
				
   			
				String Amount=request.getParameter("Amount");
				String allowed=request.getParameter("allowed");
				String broken=request.getParameter("broken");
				if (Amount==""|| Integer.parseInt(Amount)<0){
					String a=request.getParameter("id");
			 		JOptionPane.showMessageDialog(null,"Error! Invalid Amount!");
					forward="/Modify_amount.jsp?id="+a+"&dep="+department;
			 	}
				
				else if (allowed==""||Integer.parseInt(allowed)<0){
					String a=request.getParameter("id");
			 		JOptionPane.showMessageDialog(null,"Error! Invalid allowed amount!");
					forward="/Modify_amount.jsp?id="+a+"&dep="+department;
			 	}
				
				else if (broken==""||Integer.parseInt(broken)<0){
					String a=request.getParameter("id");
			 		JOptionPane.showMessageDialog(null,"Error! Invalid broken amount!");
					forward="/Modify_amount.jsp?id="+a+"&dep="+department;
			 	}
				else if(Integer.parseInt(Amount)<Integer.parseInt(allowed)){
					if(Integer.parseInt(Amount)<(Integer.parseInt(broken)+Integer.parseInt(allowed))){
						String a=request.getParameter("id");
				 		JOptionPane.showMessageDialog(null,"Error! The broken and allowed amount should not be larger than the total amount!");
						forward="/Modify_amount.jsp?id="+a+"&dep="+department;
					}
					else{
					String a=request.getParameter("id");
			 		JOptionPane.showMessageDialog(null,"Error! The allowed amount should not be larger than the total amount!");
					forward="/Modify_amount.jsp?id="+a+"&dep="+department;
				}
				}
				
				else	if(Integer.parseInt(Amount)<Integer.parseInt(broken)){
					if(Integer.parseInt(Amount)<(Integer.parseInt(broken)+Integer.parseInt(allowed))){
						String a=request.getParameter("id");
				 		JOptionPane.showMessageDialog(null,"Error! The broken and allowed amount should not be larger than the total amount!");
						forward="/Modify_amount.jsp?id="+a+"&dep="+department;
					}
					else{
					String a=request.getParameter("id");
			 		JOptionPane.showMessageDialog(null,"Error! The broken amount should not be larger than the total amount!");
					forward="/Modify_amount.jsp?id="+a+"&dep="+department;
				}
				}
				
				
				
				else{
				consql.ModifyAmount(choiceId, Integer.parseInt(Amount), Integer.parseInt(allowed), Integer.parseInt(broken));
				JOptionPane.showMessageDialog(null,"Successful! You have modify the amount!");
				forward="/View.jsp?dep="+department;
				}
			}
			 
           else if(choice.equalsIgnoreCase("ModifyInfo")){
				
      			
				String equipment=request.getParameter("equipment");
				String functionality=request.getParameter("functionality");
				String category=request.getParameter("category");
				String type=request.getParameter("type");
				
				if (equipment==""){
					String a=request.getParameter("id");
			 		JOptionPane.showMessageDialog(null,"Error! Invalid Name!");
					forward="/Modify_info.jsp?id="+a+"&dep="+department;
			 	}
				
				else{
				String number=consql.JudgeExist(id,equipment, category, type);
				if(number.equals("")){
					consql.ModifyInfo2(id,equipment,functionality);
					JOptionPane.showMessageDialog(null,"Successful! You have modify the amount!");
					forward="/View.jsp?dep="+department;
				}
				else{
					String a=request.getParameter("id");
					JOptionPane.showMessageDialog(null,"There is the same equipment record, you need to modify to other name or functionality!");
				
				forward="/Modify_info.jsp?id="+a+"&dep="+department;
				}
				}
			}
			 
           else if(choice.equalsIgnoreCase("delete")){
				String choiceId=request.getParameter("RadioGroup2");
				if(choiceId==null){
					JOptionPane.showMessageDialog(null,"No record selected!");
					forward="/View.jsp?dep="+department;
				}
				else
				forward="/Delete_equip.jsp?id="+choiceId+"&dep="+department;
			}
			 
           else if(choice.equalsIgnoreCase("info")){
				String choiceId=request.getParameter("RadioGroup2");
				if(choiceId==null){
					JOptionPane.showMessageDialog(null,"No record selected!");
					forward="/View.jsp?dep="+department;
				}
				else
				forward="/Modify_info.jsp?id="+choiceId+"&dep="+department;
			}
			 
			 
			
		      else if(choice.equalsIgnoreCase("excel")){
		    	  String path=request.getParameter("file1");
              	   if(path.indexOf(".xls")<0){
              		   JOptionPane.showMessageDialog(null,"The file type must be .xls");
                   	forward="/Add.jsp?dep="+department;
              	   }
              	   else{
           	  try {
           		
           		  TestTry.ConnectSql consql2=new TestTry.ConnectSql();
           		  consql2.OpenConnection();
           		  consql2.truncateTemp();
           		Workbook workbook = Workbook.getWorkbook(new File(path));
           		Sheet sheet = workbook.getSheet(0);
           		if(sheet.getColumns()!=5){
           			JOptionPane.showMessageDialog(null,"The format in the excel file is not correct!!!");
           			forward="/Add.jsp?dep="+department;
           		}
           		else{
           		for(int i=0;i<sheet.getRows();i++){
           		String a0 = sheet.getCell(0,i).getContents(); 
           		String a1 = sheet.getCell(1,i).getContents();
           		String a2 = sheet.getCell(2,i).getContents();
           		String a3 = sheet.getCell(3,i).getContents();
           		String a4 = sheet.getCell(4,i).getContents();
           		
           		
           		consql2.insertTemp(a0,a1,a2,a3,a4);
           		}
           		forward="/AddExcel.jsp?dep="+department;
           		}
           	} catch (BiffException e) {
           		// TODO Auto-generated catch block
           		e.printStackTrace();
           	} 
           	
           	
           }
		      }
           }
		else if(parameters.containsKey("submit1")){			
				String category=request.getParameter("category").toString();
				String type=request.getParameter("type").toString();
				id=request.getParameter("id");
				String name=request.getParameter("Name");		
				String major=request.getParameter("Major");
				String equipment=request.getParameter("equipment");
				String start_date=request.getParameter("start_date");
				String end_date=request.getParameter("end_date");
				String E_mail=request.getParameter("E-mail");
				String Telephone=request.getParameter("Telephone");
				String Amount=request.getParameter("Amount");
				String amount_allowed=request.getParameter("amount_allowed");
				String Reasons=request.getParameter("Reasons");
				String credit=request.getParameter("credit");
				String EquipmentID =request.getParameter("EquipmentID");
				if(Amount.length()==0){
					JOptionPane.showMessageDialog(null,"Please input how many you want to borrow");
					forward="/User_Info_back.jsp?id="+id+"&category="+category+"&type="+type+"&Name="+name+"&Major="+major+"&equipment="+equipment+"&start_date="+start_date+"&end_date="
					        +end_date+"&E_mail="+E_mail+"&Telephone="+Telephone+"&Amount="+Amount+"&amount_allowed="+amount_allowed+"&Reasons="+Reasons+"&credit="+credit+"&EquipmentID="+EquipmentID;
				}
				else if (Amount.length()!=0){
			if(Integer.parseInt(amount_allowed)<Integer.parseInt(Amount)){
				JOptionPane.showMessageDialog(null,"Sorry, we do not have that many equipment");
				forward="/User_Info_back.jsp?id="+id+"&category="+category+"&type="+type+"&Name="+name+"&Major="+major+"&equipment="+equipment+"&start_date="+start_date+"&end_date="
		        +end_date+"&E_mail="+E_mail+"&Telephone="+Telephone+"&Amount="+Amount+"&amount_allowed="+amount_allowed+"&Reasons="+Reasons+"&credit="+credit+"&EquipmentID="+EquipmentID;
			}
			else if(Integer.parseInt(credit)<=0){
				JOptionPane.showMessageDialog(null,"Sorry, your credit is not enough! Please treat our equipment as your own!");
				forward="/First_Page.jsp?id="+id;
			}			
			else if(Integer.parseInt(amount_allowed)>=Integer.parseInt(Amount)&&Integer.parseInt(credit)>0){
			consql.UpdateUserInfo(id,EquipmentID, name, major, E_mail, Telephone, equipment, Amount, start_date, end_date, Reasons,"lending",category);
			consql.AddStatistic(EquipmentID, Amount);
			JOptionPane.showMessageDialog(null,"Successful! Remember to get your equipment on time!");
			consql.SubstractEquip(category,type,equipment,Integer.parseInt(Amount),Integer.parseInt(amount_allowed));
	
			forward="/First_Page.jsp?id="+id;
		}}
			}else if(parameters.containsKey("search")){
				
				id=request.getParameter("id");
				String manager=request.getParameter("manager");
				String student=request.getParameter("student");
				String RadioGroup1=request.getParameter("RadioGroup1");
				String RadioGroup2=request.getParameter("RadioGroup2");
				if(RadioGroup1.equalsIgnoreCase("all")){
					if(!manager.isEmpty()||!student.isEmpty()){
						JOptionPane.showMessageDialog(null,"Please choose which one you want to see!");
						forward="/Administrator_first_page.jsp?id="+id;
					}
					else if(RadioGroup2.equalsIgnoreCase("")){ 
						JOptionPane.showMessageDialog(null,"Please choose an ID!");
						forward="/Administrator_first_page.jsp?id="+id;
					}
					else{
						forward="/Search_Info.jsp?id="+id+"&radio="+RadioGroup2+"&manager="+""+"&student="+"";
					}
				}
				else if(RadioGroup1.equalsIgnoreCase("single")){				
					 if(manager.isEmpty()&&student.isEmpty()){
						JOptionPane.showMessageDialog(null,"Please input an ID!");
						forward="/Administrator_first_page.jsp?id="+id;
					}
					 else if(!manager.isEmpty()&&!student.isEmpty()){
						 JOptionPane.showMessageDialog(null,"Please input an ID!");
							forward="/Administrator_first_page.jsp?id="+id;
					 }
				else if(!student.isEmpty()){
					
					forward="/Search_Info.jsp?id="+id+"&student="+student+"&manager="+"";
				}
				else if(!manager.isEmpty()){
					forward="/Search_Info.jsp?id="+id+"&manager="+manager+"&student="+"";
				}
			}
			}else if(parameters.containsKey("modify")){
				 id=request.getParameter("id");
				String old_id=request.getParameter("old_id");
			      String old_name=request.getParameter("old_name");
			      String old_authority=request.getParameter("old_authority");
			      String manager=request.getParameter("manager");
				  String student=request.getParameter("student");
			      String radio =request.getParameter("radio");
				if(old_id.isEmpty()){
					JOptionPane.showMessageDialog(null,"Please choose one to modify!");
					forward="/Search_Info.jsp?id="+id+"&radio="+radio+"&manager="+manager+"&student="+student;
				}
				else forward="/ModifyInfo.jsp?id="+id+"&old_id="+old_id+"&old_name="+old_name+"&old_authority="+old_authority;
			}else if(parameters.containsKey("save")){
				id=request.getParameter("id");
				String old_id=request.getParameter("old_id");
				String old_name=request.getParameter("old_name");
				String old_authority=request.getParameter("old_authority");
				String new_id=request.getParameter("new_id");
				String new_name=request.getParameter("new_name");
				String new_authority=request.getParameter("new_authority");
				if(new_id.equals("")||new_name.equals("")||new_authority.equals("")){
					JOptionPane.showMessageDialog(null,"You forget to input ID or name or authority!");
					forward="/ModifyInfo.jsp?id="+id+"&old_id="+old_id+"&old_name="+old_name+"&old_authority="+old_authority;
				}
				else{
				consql.ModifyInfo(old_id, new_id, new_name, new_authority);
				forward="/Administrator_first_page.jsp?id="+id;
			}
			}
			else if(parameters.containsKey("searchresult")){
				id=request.getParameter("id");
			    String category=request.getParameter("category");
			    String type=request.getParameter("type");
			    String start_date=request.getParameter("start_date");
			    String end_date=request.getParameter("end_date"); 
				String equipment=request.getParameter("equipment");
				String amount_allowed=request.getParameter("amount_allowed");
				String EquipmentID =request.getParameter("EquipmentID");
			    if(equipment.isEmpty()){
			    	JOptionPane.showMessageDialog(null,"Please choose one item in the table");
					forward="/Search_Result.jsp?id="+id+"&category="+category+"&type="+type+"&end_date="+end_date+"&start_date="+start_date;
			    }
			    else{
			    	forward="/User_Info.jsp?id="+id+"&category="+category+"&type="+type+"&end_date="+end_date+"&start_date="+start_date+"&EquipmentID="+EquipmentID+"&equipment="+equipment+"&amount_allowed="+amount_allowed;
			    }
			    
			}else if(parameters.containsKey("searchresults")){
				id=request.getParameter("id");
			    String category=request.getParameter("category");
			    String type=request.getParameter("type");
			    String start_date=request.getParameter("start_date");
			    String end_date=request.getParameter("end_date"); 
				String equipment=request.getParameter("equipment");
				
				String amount_allowed=request.getParameter("amount_allowed");
				String EquipmentID =request.getParameter("EquipmentID");
			    if(EquipmentID.isEmpty()){		    	
			    	JOptionPane.showMessageDialog(null,"Please choose one item in the table");
					forward="/Search_Result1.jsp?id="+id+"&equipment="+equipment+"&end_date="+end_date+"&start_date="+start_date;
			    }
			    else{
			    	forward="/User_Info.jsp?id="+id+"&category="+category+"&type="+type+"&end_date="+end_date+"&start_date="+start_date+"&EquipmentID="+EquipmentID+"&equipment="+equipment+"&amount_allowed="+amount_allowed;
			    }
			    
			}else if(parameters.containsKey("submit2")){
				consql.SelectDeleteInfo(id);
			
				
				forward="/View.jsp?dep="+department;
					}

		response.sendRedirect("."+forward);
				}
				

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}
	

}
