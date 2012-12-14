<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    <%@ page import="java.sql.*"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Modify Information</title>
</head>

<%
String dep=request.getParameter("dep"); 
String ref = "View.jsp?dep="+dep;
ResultSet rs1;
String id =request.getParameter("id"); 
TestTry.ConnectSql consql = new TestTry.ConnectSql();
consql.OpenConnection();
rs1 = consql.SelectEquipment1(id);
String category="";
	String type="";
%>

<body>
 <center>
<form>
<table  background="img/bg.png">
  <tr>
    <td width="950">&nbsp;</td>
    <td width="520"><p>&nbsp;</p>
    <p>&nbsp;</p></td>
  <td width="150" height="85"><a href="Login.jsp"><img src="img/logout_memo.png"  border="0" width="40" height="50" /></a></td>

</tr>
</table>
<table>
<tr>
<td width="252">&nbsp;</td>
<td width="252">&nbsp;</td>
</tr>
</table>
</form>

  <form action="ConnectJSP">
  
    	<table align="center" width="806" height="35" border="0" bgcolor="#52D0EB" style="border-collapse:collapse;">
<tr>
    <td width="600" align="center"><font size="5px"><strong><font color=white >You can modify the information of the equipment</font>
    </strong></font></td>
    
</table>

 <br><br>
	    <table width="800" border="1" align="center">
 		<tr >
 		<td bgcolor="#FFFFCC" >Equipment ID</td>
 		<td bgcolor="#FFFF99">Equipment Name</td>
		<td bgcolor="#FFFFCC" >Category</td>
		<td bgcolor="#FFFF99">Type</td>
		<td bgcolor="#FFFFCC" >Functionality</td>
		</tr>		
<% 	
	while(rs1.next()){
%>       
        <tr>            
        <td><%=rs1.getString("Id")%></td>
		<td ><input type="text" value=<%= rs1.getString("equipment") %> name="equipment" id="equipment"></td>
        <td><%=rs1.getString("category")%></td>
		<td><%=rs1.getString("type")%></td>
        <td ><input type="text" value=<%=rs1.getString("functionality")%> name="functionality" id="functionality"></td>	
		</tr>
		<%} %>
    </table>    
      <input type="hidden" name="RadioGroup1"  id="RadioGroup1" value="ModifyInfo" />
    <br><br>
    <font color="#0033FF" size="+1"><strong>Type in the information you want to modify </strong></font>
<br><br>
 <input type="submit" name="submit" id="submit" value="Modify" style="width:80px; height:30px; font-size:15px;" />&nbsp;&nbsp;&nbsp; <input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> 
   
 <input type="hidden" name="dep" id="dep" value=<%= dep %>>
  <input type="hidden" name="category" id="category" value=<%= category %>>
   <input type="hidden" name="type" id="type" value=<%= type %>>
  <input type="hidden" name="id" id="id" value=<%= id %>>
     </form> 
         
      
     </center>
</body>
</html>
