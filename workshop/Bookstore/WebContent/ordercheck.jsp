<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.sql.*,java.text.DecimalFormat" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Check submitted order</title>
</head>
<body>
<div id="container">
　　<div id="Header">
  　</div>
</div>   
　　<div id="PageBody" >
　　　　<div id="Sidebar" align="left">
<%@include file="sider.jsp"  %>
　　　　</div>
<div id="MainBody">
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Order Check</font>
    </strong></font></td>
</table>
<%

	   float sum=0;

	   String order=request.getParameter("findorder");
        
	
	   Connection conn;
	   Statement sta;
	   Statement sta1;
	   ResultSet r1; 
	   ResultSet r2;
	   try{
	   	Class.forName(drv);
	   	conn = DriverManager.getConnection(url1,user,passwd);
	   	sta=conn.createStatement();	
	   	sta1=conn.createStatement();	
	   	r1= sta.executeQuery("select isbn, title, author, price, amount, (price*amount)from orderbk where orderno ='"+order+"'");
	   	r2= sta1.executeQuery("select C.name,phone,createddate,delivereddate,delivery "
				+"from customers as C,orders as O where C.customerid=O.customerid and O.orderno='"+order+"'");
	   	String Deliver="--";  	   	
	   	while(r2.next()){
			if(r2.getString(4)!= null) {
				Deliver=r2.getString(4);}
	   %>	
	       <br><h2 align="left" >The customer's information are listed here</h2>
	       <table>    
	       <tr><td width = "100"><font size="3px">Name:<%=r2.getString(1)%></font></td></tr>
	       <tr><td width = "100"><font size="3px">Phone:<%=r2.getString(2)%></font></td></tr>
	       <tr><td width = "300"><font size="3px">Ordered Date:<%=r2.getString(3)%></font></td></tr>
	       <tr><td width = "300"><font size="3px">Delivered Date:<%=Deliver%></font></td></tr>
	       <tr><td width = "100"><font size="3px">Delivery:<%=r2.getString(5)%></font></td></tr>
	       </table>
	       <h3>Please confirm that your information it's right, or you can contact the staff</h3><br/>
	       
	       
	       	<br><h2 align="center" >Your order results are listed here</h2>
	       	<h3>&nbsp; &nbsp; &nbsp; &nbsp;Your order number :<%=order %></h3>
	   	    <table width="800" border="0" align="center">
	    		<tr bgcolor="#D9E7FF">
	    		<td height="20" width="70"><div align="center" ><b>ISBN</b></div></td>
	   		<td width="90"><div align="center" ><b>Title</b></div></td>
	   		<td width="80"><div align="center" ><b>Author</b></div></td>
	   		<td width="70"><div align="center" ><b>Price</b></div></td>
	   		<td width="70"><div align="center" ><b>Amount</b></div></td>
	   		<td width="70"><div align="center" ><b>Subtotal amount</b></div></td>
	   		</tr>
	   <% 	}
	   	while(r1.next()){
		    sum = sum+(r1.getInt(6));	
	   %>	
	           <tr> 
	   		<td height="20" width="70"><div align="center" class="style1"><%=r1.getLong(1)%></div></td>
	   		<td width="90"><div align="center" class="style1"><%=r1.getString(2)%></div></td>
	   		<td width="80"><div align="center" class="style1"><%=r1.getString(3)%></div></td>
	   		<td width="70"><div align="center" class="style1"><%=r1.getFloat(4)%></div></td>
	   		<td width="70"><div align="center" class="style1"><%=r1.getInt(5)%></div></td>
	   		<td width="70"><div align="center" class="style1"><%=r1.getInt(6)%></div></td>
	   		</tr>
	   		<%} %>
	       </table>	
	       <br/><br/>
    <table align = "center">
    		<tr><td align ="right">Total cost</td></tr>	
		<tr><td align ="right"><%out.println("$" +sum);%></td></tr>
		<tr></tr>
	</table>
<br><br><br><br>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/back.jpg "onClick="location.href='index.jsp'" /><font size="4px">Back to Index&nbsp; &nbsp; &nbsp;</font></p></td> 
</tr></table>     
	    <% 	
	   	        r1.close();
	   			sta.close();
	   			conn.close();
	               }catch(SQLException ex){
	   		    out.println("SQL error : " +ex);
	   	         }
      
%>

    
  </div> 

    </div>
<%@include file="footer.jsp"  %>
</body>
</html>