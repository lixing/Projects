<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Book info</title>
</head>
<body>
<div id="container">
　　<div id="Header">
  　</div>
</div>   
　　<div id="PageBody" >
<div id="Sidebar" align="left">
<%@include file="bgsider.jsp"  %>
　　　　</div>
<div id="MainBody">
<%
  try{ Class.forName(drv);
  Connection conn = DriverManager.getConnection(url1,user,passwd);
  Statement sta=conn.createStatement();
  String isbn=request.getParameter("isbn");
  ResultSet result= sta.executeQuery
  ("select isbn,title,author,price,number,cover,info"
		  +" from books where isbn='"+isbn+"'");
  result.next();%>
    <form name="search"  method="post" action="putin.jsp?isbn=<%=result.getLong(1)%>"> 
<br><h2 align="center" >Book Information for BackGround</h2>
<table width="500" border="1" align="center">
  <tr>
    <td width="200" rowspan="5"><img src="./images/cover/<%=result.getString(6)%>" width="240" height="320"></td>
    <td width="149" height="30" bgcolor="#CCCC99"><div align="center">ISBN</div></td>
    <td width="233"><%=result.getString(1)%></td>
  </tr>
  <tr>
    <td height="30" bgcolor="#CCCC99"><div align="center">Title</div></td>
    <td><%=result.getString(2)%></td>
  </tr>
  <tr>
    <td height="30" bgcolor="#CCCC99"><div align="center">Author</div></td>
    <td><%=result.getString(3)%></td>
  </tr>
  <tr>
    <td height="30" bgcolor="#CCCC99"><div align="center">Price</div></td>
    <td>$ <%=result.getString(4)%></td>
  </tr>
  <tr>
    <td height="30" bgcolor="#CCCC99"><div align="center">Bookstore counting</div></td>
    <td><%=result.getString(5)%></td>
  </tr>
  <tr>
    <td colspan="3"><p><font size="4">Synopsis</font></p>
      <p><font size="3" style="Times New Roman"><%=result.getString(7)%></font></p></td>
  </tr>
</table>
<br><br><br><br>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/bback.jpg "onClick="location.href='background.jsp'" /><font size="4px">Back to Background&nbsp; &nbsp; &nbsp;</font></p></td> 
</tr></table>  
 </form>
<p>&nbsp;</p>
</div></div>
<%@include file="footer.jsp"  %>
</body>
<%
result.close();
sta.close();
conn.close();
}catch(SQLException ex){
	out.println("SQL fail to be connected");
}
%>
</html>