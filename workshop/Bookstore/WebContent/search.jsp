<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Search Books</title>
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
    /*String findname=request.getParameter("find");
findname = new String(findname.getBytes("utf-8"));
这个用了还是乱码= =  */

String findname = new String(request.getParameter("findbook").getBytes("ISO-8859-1"),"UTF-8");
Connection conn;
Statement sta;
ResultSet r1; 
try{
	Class.forName(drv);
	conn = DriverManager.getConnection(url1,user,passwd);

	sta=conn.createStatement();			
	r1= sta.executeQuery("select isbn, title, author, price, cover from books " 
			+"where post =1 and title like '%"+findname+"%' or author like '%"+findname+"%'"  );
	%>
    	<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Search Books</font>
    </strong></font></td>
</table>
    	<h3>&nbsp; &nbsp; &nbsp; &nbsp;Your searching key : <%=findname %></h3>
	    <table width="600" border="1" align="center">
 		<tr bgcolor="#D9E7FF">
 		<td height="20" width="80"><div align="center" ><b>Book Front</b></div></td>
		<td width="80"><div align="center" ><b>ISBN</b></div></td>
		<td width="120"><div align="center" ><b>Title</b></div></td>
		<td width="120"><div align="center" ><b>Author</b></div></td>
		<td width="70"><div align="center" ><b>Price</b></div></td>
		</tr>
<% 	
	while(r1.next()){
%>	
        <tr> 
		<td height= "160" width="120"><div align="center" class="style1"><img src="./images/cover/<%=r1.getString(5)%>" width="120" height="160" onClick="location.href='bookinfo.jsp?isbn=<%=r1.getLong(1)%>'" /></div></td>
		<td height="20" width="70"><div align="center" class="style1"><%=r1.getLong(1)%></div></td>
		<td width="120"><div align="center" class="style1"><%=r1.getString(2)%></div></td>
		<td width="120"><div align="center" class="style1"><%=r1.getString(3)%></div></td>
		<td width="70"><div align="center" class="style1"><%=r1.getFloat(4)%></div></td>
		</tr>
		<%} %>
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
<tr><td><p align="center"><img src="./images/bg/back.jpg "onClick="location.href='index.jsp'" /><font size="4px">Back to Index&nbsp; &nbsp; &nbsp;</font></p></td> 
</tr></table>     
    </div>
    </div>
<%@include file="footer.jsp"  %>
</body>
</html>