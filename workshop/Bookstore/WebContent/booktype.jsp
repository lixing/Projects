<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Book Type</title>
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
<div id="MainBody2">
<table border="0" align="center">
<tr align="center">
<td align="center">

<%
        String type=(String)request.getParameter("typeno");
        if(type==null)
        {
          type="1";	
        }

        try{ Class.forName(drv);
		Connection conn = DriverManager.getConnection(url1,user,passwd);
		
		Statement sta=conn.createStatement();
		ResultSet result= sta.executeQuery("select isbn, title, author, price, cover" 
				                            +" from books where booktype=" + type+ " and post = 1 order by isbn asc");

if (type.equals("2"))
   {
%>
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Light Novel</font>
    </strong></font></td>
</table>
<%
   }
else if (type.equals("3"))
{
%>
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Manga</font>
    </strong></font></td>
</table>
<%
}
else{ 
%>
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Novel</font>
    </strong></font></td>
</table>
<%
   }

while(result.next()){
%>
  <table width="500" height="120" border="0" align="center">
  <tr>
    <td width="180" rowspan="3"><div align="center">
        <img src="./images/cover/<%=result.getString(5)%>" width="210" height="280" onClick="location.href='bookinfo.jsp?isbn=<%=result.getLong(1)%>'" />
</div></td>
    <td>
    <table width="320" height="90" border="0" align="left">
   	<tr>
    	<td width="80" height="30"><div align="left"><span class="STYLE2">Title : </span></div></td>
    	<td><div align="left"><%=result.getString(2)%></div></td>
    </tr>
    <tr>
    	<td width="80" height="30"><div align="left"><span class="STYLE2">Author : </span></div></td>
    	<td><div align="left"><%=result.getString(3)%></div></td>
  	</tr>
  	<tr>
    	<td width="80" height="30"><div align="left"><span class="STYLE2">Price : </span></div></td>
    	<td><div align="left">$<%=result.getString(4)%></div>
    </td>
  	</tr>
    </table>
  </td>
  </tr>
  </table>
  <br>
<%
}
%>　
  </td>
</tr>
</table>

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