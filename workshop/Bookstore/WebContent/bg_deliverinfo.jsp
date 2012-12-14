<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Deliver books</title>
</head>
<body>
<div id="container">
　　<div id="Header">
  　</div></div>   
　　<div id="PageBody" >
<div id="Sidebar" align="left">
<%@include file="bgsider.jsp"  %>
　　　　</div>
<div id="MainBody">
    <%
    float sum=0;

	   String orderno=request.getParameter("orderno");
     
	
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
	   	r1= sta.executeQuery("select isbn, title, author, price, amount, (price*amount)from orderbk where orderno ='"+orderno+"'");
	   	r2= sta1.executeQuery("select C.name,phone,createddate,delivereddate,delivery,address,zip "
				+"from customers as C,orders as O where C.customerid=O.customerid and O.orderno='"+orderno+"'");
	   	String Deliver="--";  
	   	while(r2.next()){
			if(r2.getString(4)!= null) {
				Deliver=r2.getString(4);}
	   %>	
	       <table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Here are the detailed delivery information</font>
    </strong></font></td>
</table>
	       <h3>Order number :<%=orderno %></h3>
	       <table>    
	       <tr><td width = "100"><font size="3px">Name:<%=r2.getString(1)%></font></td></tr>
	       <tr><td width = "100"><font size="3px">Address:<%=r2.getString(6)%></font></td></tr>
	       <tr><td width = "150"><font size="3px">Zip Code:<%=r2.getString(7)%></font></td></tr>
	       <tr><td width = "100"><font size="3px">Phone:<%=r2.getString(2)%></font></td></tr>
	       <tr><td width = "300"><font size="3px">Ordered Date:<%=r2.getString(3)%></font></td></tr>
	       <tr><td width = "300"><font size="3px">Delivered Date:<%=Deliver%></font></td></tr>
	       <tr><td width = "100"><font size="3px">Delivery:<%=r2.getString(5)%></font></td></tr>
	       </table>
	       
	       

	   	    <table width="800" border="0" align="center">
	    		<tr bgcolor="#D9E7FF">
	    		<td height="20" width="70"><div align="center" ><b>ISBN</b></div></td>
	   		<td width="90"><div align="center" ><b>Title</b></div></td>
	   		<td width="80"><div align="center" ><b>Author</b></div></td>
	   		<td width="70"><div align="center" ><b>Price</b></div></td>
	   		<td width="70"><div align="center" ><b>Amount</b></div></td>
	   		<td width="70"><div align="center" ><b>Subtotal amount</b></div></td>
	   		</tr>
	   <% 	
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
	       <p align="center"><img src="./images/bg/bback.jpg "onClick="location.href='bg_deliver.jsp'" />
	         <%       
	         if(r2.getString(5).equals("NO")) { %>
	       <img src="./images/bg/express.jpg "onClick="location.href='bg_deliverok.jsp?orderno=<%=orderno%>'" /></p>
	    <% 	}
	         } //end of r2 while
	    
	   	        r1.close();
	   			sta.close();
	   			r2.close();
	   			sta1.close();
	   			conn.close();
	               }catch(SQLException ex){
	   		    out.println("SQL error : " +ex);
	   	         }
   
%>
    </div>　　　　</div>
<%@include file="footer.jsp"  %>
</body>
</html>