<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Message Board</title>
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
		Connection conn;
		Statement sta;
		ResultSet r1; 
		try{
			Class.forName(drv);
			conn = DriverManager.getConnection(url1,user,passwd);

			sta=conn.createStatement();			
			r1= sta.executeQuery("select id, name, info, reply, msdate,replydate from message order by id asc"  );
			%> 
		   <table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Messages Board</font>
    </strong></font></td>
</table>
		<% 	
	   	String reply="No reply yet"; 
		String replyd = "No";
			while(r1.next()){
				if(r1.getString(4)!= null) {
					reply=r1.getString(4);}
				else {reply="No reply yet";}
				if(r1.getString(6)!= null) {
					replyd=r1.getString(6);}
				else {replyd = "No";}

		%>	
		        <table width="800" height="100" border="1" bordercolor="#000000" align="center">
		        <tr> 
				<td width="50" align="right"><%=r1.getString(2)%>:</td>
				<td width="550"><%=r1.getString(3)%></td>
				<td width="200">Post date:<%=r1.getString(5)%></td>
				</tr></table >
				<table width="800" height="50" border="1" bordercolor="#9966FF" align="center"><tr>
				<td width="600">Admin reply:<%=reply%></td>
				<td width="199">Reply date:<%=replyd%></td>
               	</tr></table><br><br>
				<%} %>
		
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