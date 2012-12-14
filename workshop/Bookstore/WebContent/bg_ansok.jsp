<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*,java.util.Calendar,java.text.*,java.text.DecimalFormat"%>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Answer messages OK</title>
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
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Your answer has been updated</font>
    </strong></font></td>
</table>
<%	
String answer = new String(request.getParameter("answer").getBytes("ISO-8859-1"),"UTF-8");
String id=request.getParameter("id");
try{ Class.forName(drv);
Connection conn = DriverManager.getConnection(url1,user,passwd);
Statement sta=conn.createStatement();

Date currentTime = new Date();
SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
String dateString = formatter.format(currentTime);    
sta.executeUpdate
("UPDATE message SET reply = '"+answer+"', replydate = '"+dateString+"', re = 1 WHERE id = '"+id+"'");

sta.close();
conn.close();
}catch(SQLException ex){
	out.println("SQL fail to be connected");
}
%>



<br><br><br><br>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/smessage.jpg "onClick="location.href='bg_message.jsp'" /><font size="4px">Back to Message Management&nbsp; &nbsp; &nbsp;</font></p></td> 
<td><p align="center"><img src="./images/bg/bback.jpg "onClick="location.href='background.jsp'" /><font size="4px">Back to Background</font></p></td></tr></table>  
</div></div>
<%@include file="footer.jsp"  %>
</body>
</html>