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

<script language="javascript"> 
function   KeyPressNum(strValue)   
{           
	  var   str   =new   String(strValue);  
	  if   ((window.event.keyCode<47||window.event.keyCode>57))   
	  {window.event.returnValue=false;}   
	  else   
	  {window.event.returnValue=true;}   
	  }
</script>
<%
  try{ Class.forName(drv);
  Connection conn = DriverManager.getConnection(url1,user,passwd);
  Statement sta=conn.createStatement();
  String isbn=request.getParameter("isbn");
  ResultSet result= sta.executeQuery
  ("select isbn,title,author,price,number,cover,info"
		  +" from books where isbn='"+isbn+"'");
  result.next();%>
    <form name="search"  method="post" action="bg_storeok.jsp?isbn=<%=result.getLong(1)%>"> 
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Enter the amout you want to increase</font>
    </strong></font></td>
</table>
<table width="500" border="1" align="center">
  <tr>
    <td width="200" rowspan="6"><img src="./images/cover/<%=result.getString(6)%>" width="240" height="320"></td>
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
    <td height="30" bgcolor="#CCCC99"><div align="center">Bookstore counting</div></td>
    <td><%=result.getString(5)%></td>
  </tr>
  <tr>
    <td align="center" height="38" colspan="3">Enter the number you want to buy<br/><br/><input name="amount" type="text" id="find" size="10" onkeypress="return   KeyPressNum();"/></td>
  </tr>
    <tr>
    <td align="center" height="38" colspan="3"><input class="searchbutton" type="submit" value="OK"/></td>
  </tr>
</table>
 </form>
<p>&nbsp;</p>
</div>　　　　</div>
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