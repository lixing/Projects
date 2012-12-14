<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Shopping Cart Put in</title>
</head>
<body>
<div id="container">
　　<div id="Header">
  　</div>
</div>
<table width="960" >
</table> 
　　<div id="PageBody" >
　　　　<div id="Sidebar" align="left">
<%@include file="sider.jsp"  %>
　　　　</div><div id="MainBody">

		<%		
  try{ Class.forName(drv);
  Connection conn = DriverManager.getConnection(url1,user,passwd);
  Statement sta=conn.createStatement();
  String isbn=request.getParameter("isbn");
  String purchase = new String(request.getParameter("purchase"));
  ResultSet result= sta.executeQuery
  ("select isbn,title,author,price,number,cover"
		  +" from books where isbn='"+isbn+"'");
  result.next();
  int buy = Integer.parseInt(purchase);  
  int num = result.getInt(5);
  if(buy > num )
		  {%>

<table align="center" width="650" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center"><font size="5px"><strong><font color=white ><br>Sorry, we don't have so many storage! <br>This purchase didn't deal, please try again. <br>Or you may contact the staff.
    </font></strong></font></td></tr>
    <tr align="center"><td>
    <br><br><br><br><br><br><br>
    <img src="./images/bg/bback.jpg " onclick ="javascript:history.go(-1);"/><font size="4px">Backward</font></td></tr>
</table>
		  <%}
  else{%>
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Put in successfully!</font>
    </strong></font></td>
</table><%
  Statement sta2=conn.createStatement();
  sta2.executeUpdate
  (
		  " INSERT INTO cart VALUES " +
		  " ('"+result.getString(1)+"','"+result.getString(2)+"','"+result.getString(3)+"','"+result.getString(4)+"','"+purchase+"','"+result.getString(6)+"' ) "); 
  sta.close();
  sta2.close();
  conn.close();
  }}catch(SQLException ex){
  	out.println("SQL fail to be connected");
  }
  %>
  <br>
  <br>  <br>  <br>  <br>  <br>  
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/cart.jpg "onClick="location.href='cart.jsp'" /><font size="4px">View my cart&nbsp; &nbsp; &nbsp;</font></p></td> 
<td><p align="center"><img src="./images/bg/back.jpg "onClick="location.href='index.jsp'" /><font size="4px">Back to index</font></p></td></tr></table>       
</div>
　　　　</div>
<%@include file="footer.jsp"  %>
</body>
</html>