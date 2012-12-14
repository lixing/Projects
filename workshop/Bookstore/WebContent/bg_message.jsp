<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Message Board Management</title>
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
Connection conn;
Statement sta;
ResultSet r1; 
Statement sta2;
ResultSet r2; 
try{
	Class.forName(drv);
	conn = DriverManager.getConnection(url1,user,passwd);
	sta=conn.createStatement();			
	r1= sta.executeQuery("select id,name,email,info,reply,msdate,replydate,re from message where re = 0 order by msdate asc");
	%> 
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >This is message board checking page</font>
    </strong></font></td>
</table>
        <h3>Here are all the non replied messages</h3><br/>
	    <table width="800" border="0" align="center">
 		<tr bgcolor="#D9E7FF">
 		<td width="80"><div align="center" ><b>Name</b></div></td>
		<td width="80"><div align="center" ><b>Email</b></div></td>
		<td width="150"><div align="center" ><b>info</b></div></td>
		<td width="80"><div align="center" ><b>Ms Date</b></div></td>
		<td width="150"><div align="center" ><b>Reply</b></div></td>
		<td width="60"><div align="center" ><b>Reply Date</b></div></td>
		<td width="30"><div align="center" ><b>Reply or Not</b></div></td>
		<td width="60"><div align="center" ><b>Reply this message</b></div></td>
		</tr>
<% 	
	String rep=null;  
	String reply="No reply yet"; 
	String replyd = "No";
	while(r1.next()){
        if(r1.getInt(8)== 0) {
			rep="NO";}		
		if(r1.getString(5)!= null) {
					reply=r1.getString(5);}
		if(r1.getString(7)!= null) {
					replyd=r1.getString(7);}	
		
%>	
        <tr> 
		<td width="80"><div align="center" class="style1"><%=r1.getString(2)%></div></td>
		<td width="80"><div align="center" class="style1"><%=r1.getString(3)%></div></td>
		<td width="150"><div align="center" class="style1"><%=r1.getString(4)%></div></td>
		<td width="80"><div align="center" class="style1"><%=r1.getString(6)%></div></td>
		<td width="150"><div align="center" class="style1"><%=reply%></div></td>
		<td width="60"><div align="center" class="style1"><%=replyd%></div></td>	
		<td width="30"><div align="center" class="style1"><%=rep%></div></td>	
		<td width="60"><div align="center" class="style1"><img src="./images/bg/enter.jpg "onClick="location.href='bg_ansmessage.jsp?id=<%=r1.getString(1)%>'" /></div></td>
		</tr>
		<%} %>
    </table>	
    
    
    
    <%
    Class.forName(drv);
	conn = DriverManager.getConnection(url1,user,passwd);
	sta2=conn.createStatement();			
	r2= sta.executeQuery("select id,name,email,info,reply,msdate,replydate,re from message where re =1 order by replydate asc");
	%>
        <h3>Here are the replied messages</h3><br/>
	    <table width="800" border="0" align="center">
 	 	<tr bgcolor="#D9E7FF">
 		<td width="80"><div align="center" ><b>Name</b></div></td>
		<td width="80"><div align="center" ><b>Email</b></div></td>
		<td width="150"><div align="center" ><b>info</b></div></td>
		<td width="80"><div align="center" ><b>Ms Date</b></div></td>
		<td width="150"><div align="center" ><b>Reply</b></div></td>
		<td width="80"><div align="center" ><b>Reply Date</b></div></td>
		<td width="30"><div align="center" ><b>Reply or Not</b></div></td>
		</tr>
<% 		
	while(r2.next()){
		String rep2 = null;
		if (r2.getInt(8)== 1){
			rep2 = "YES";}
%>	
         <tr> 
		<td width="80"><div align="center" class="style1"><%=r2.getString(2)%></div></td>
		<td width="80"><div align="center" class="style1"><%=r2.getString(3)%></div></td>
		<td width="150"><div align="center" class="style1"><%=r2.getString(4)%></div></td>
		<td width="80"><div align="center" class="style1"><%=r2.getString(6)%></div></td>
		<td width="150"><div align="center" class="style1"><%=r2.getString(5)%></div></td>
		<td width="80"><div align="center" class="style1"><%=r2.getString(7)%></div></td>	
		<td width="30"><div align="center" class="style1"><%=rep2%></div></td>	
		</tr>
		<%} %>
    </table>	
<br><br><br><br>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/bback.jpg "onClick="location.href='background.jsp'" /><font size="4px">Back to Background&nbsp; &nbsp; &nbsp;</font></p></td> 
</tr></table>  
 <% 	
             r1.close();
             sta.close();
             r2.close();
	         sta2.close();
	         conn.close();
            }catch(SQLException ex){
		    out.println("SQL error : " +ex);
	         }
%>
    </div></div>
<%@include file="footer.jsp"  %>
</body>
</html>