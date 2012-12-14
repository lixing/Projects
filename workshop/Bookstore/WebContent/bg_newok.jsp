<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Switch books new successfully</title>
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
<%@include file="bgsider.jsp"  %>
　　　　</div><div id="MainBody">
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Change book attribute successfully!</font>
    </strong></font></td>
</table>
		<%
  try{ Class.forName(drv);
  Connection conn = DriverManager.getConnection(url1,user,passwd);
  Statement sta=conn.createStatement();
  String isbn=request.getParameter("isbn");
  sta.executeUpdate
  ("UPDATE books SET new = 1 where isbn='"+isbn+"'");
  sta.close();
  conn.close();
  }catch(SQLException ex){
  	out.println("SQL fail to be connected");
  }
  %>   
<br><br><br><br>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/snewold.jpg "onClick="location.href='bg_newold.jsp'" /><font size="4px">Back to Change&nbsp; &nbsp; &nbsp;</font></p></td> 
<td><p align="center"><img src="./images/bg/bback.jpg "onClick="location.href='background.jsp'" /><font size="4px">Back to Background</font></p></td></tr></table>  
</div></div>
<%@include file="footer.jsp"  %>
</body>
</html>