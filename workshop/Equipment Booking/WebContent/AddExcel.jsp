<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*,java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html><%String dep=request.getParameter("dep"); 
String ref = "Add.jsp?dep="+dep;%>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Add Equipment</title>
</head>
<body>


<% 
ResultSet rs1;
TestTry.ConnectSql consql = new TestTry.ConnectSql();
 consql.OpenConnection();
rs1 = consql.ShowEquipmentTemp();
%>
<form>
<table  background="img/bg.png">
  <tr>
    <td width="950">&nbsp;</td>
    <td width="520"><p>&nbsp;</p>
    <p>&nbsp;</p>
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
 
    	<table align="center" width="806" height="35" border="0" bgcolor="#52D0EB"  style="border-collapse:collapse;">
<tr>
    <td width="600" align="center" ><font size="5px"><strong><font color=white >Here is the list of equipment in the excel file</font>
    </strong></font></td>
</table>
	     <center>
 <br><br>
	    <table width="800" border="0" align="center">
 		<tr >
 		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Equipment Name</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Category</b></div></td>
		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Type</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Description</b></div></td>
		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Amount</b></div></td>
		</tr>
<% 	

	while(rs1.next()){
	
%>
        
        <tr> 
        <td width="110"><div align="center" class="style1"><%=rs1.getString("equipment")%></div></td>
        <td width="110"><div align="center" class="style1"><%=rs1.getString("category")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("type")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("functionality")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("allowed")%></div></td>
		</tr>
		<%} %>
    </table>	
   
   </center>
<br><br><br><br>
<center>
      <p><input type="hidden" name="RadioGroup1"  id="RadioGroup1" value="addexcel"/></p>
      </center>
<div align="center">
    <p><input type="submit" name="submit" id="submit"  value="SUBMIT"style="width:80px; height:30px; font-size:15px;" />&nbsp;&nbsp;&nbsp; <input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> </p>
    
 </div>
 <input type="hidden" name="dep" id="dep" value=<%= dep %>>
     </form> 
    
</body>
</html>