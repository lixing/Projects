<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Shopping Cart</title>
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
    <%
 	float sum=0;
    try{ Class.forName(drv);
    Connection conn = DriverManager.getConnection(url1,user,passwd);
    Statement sta=conn.createStatement();
    String isbn=request.getParameter("isbn");
    ResultSet r1= sta.executeQuery
    ("select isbn,title,author,price,amount"
  		  +" from cart");
		

	%> 
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Shopping Cart</font>
    </strong></font></td>
</table>
<br><br>
	    <table width="600" border="0" align="center" >
 		<tr bgcolor="#D9E7FF">
		<td width="80"><div align="center" ><b>ISBN</b></div></td>
		<td width="120"><div align="center" ><b>Title</b></div></td>
		<td width="120"><div align="center" ><b>Author</b></div></td>
		<td width="70"><div align="center" ><b>Price</b></div></td>
		<td width="70"><div align="center" ><b>Purchase amount</b></div></td>
		<td width="140"><div align="center" ><b>Cart control</b></div></td>
		</tr>
<% 	
	while(r1.next()){
	    float price=r1.getFloat(4);
	    sum = sum+(r1.getInt(5)*price);	
%>	
        <tr> 
		<td height="20" width="80"><div align="center" class="style1"><%=r1.getLong(1)%></div></td>
		<td width="120"><div align="center" class="style1"><%=r1.getString(2)%></div></td>
		<td width="120"><div align="center" class="style1"><%=r1.getString(3)%></div></td>
		<td width="70"><div align="center" class="style1"><%=r1.getFloat(4)%></div></td>
		<td width="70"><div align="center" class="style1"><%=r1.getInt(5)%></div></td>
		<td width="140"><div align="center" class="style1"><input type="button" Value="Take this book out" onClick="location.href='takeout.jsp?isbn=<%=r1.getLong(1)%>'" /></div></td>
		</tr>
		<%
		}	
	%>
    </table> 
    <br/>
    <table align = "center" >
    		<tr><td align ="right">Total cost</td></tr>	
		<tr><td align ="right"><%out.println("$" +sum);%></td></tr>
	</table>	
 <% 	
	        r1.close();
			sta.close();
			conn.close();
            }catch(SQLException ex){
		    out.println("SQL error : " +ex);
	         }    
%>
<br><br><br><br>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/pay.jpg "onClick="location.href='customerinfo.jsp'" /><font size="4px">Pay the Bill&nbsp; &nbsp; &nbsp;</font></p></td> 
</tr></table>       
    </div>
    </div>
<%@include file="footer.jsp"  %>
</body>
</html>