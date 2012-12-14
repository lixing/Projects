<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="java.util.*,java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Lending Record</title>
</head>

<%
String dep=request.getParameter("dep"); 
String ref = "Manager_first_page.jsp?dep="+dep;
ResultSet rs3;
TestTry.ConnectSql consql = new TestTry.ConnectSql();
consql.OpenConnection();
String st="lending";
rs3 = consql.SelectRecord2(st,dep);
%>


<body>
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
  <form name="form1" action="ConnectJSP ">
  
    	<table align="center" width="806" height="35" border="0" bgcolor="#52D0EB" style="border-collapse:collapse;">
<tr>
    <td width="600" align="center" ><font size="5px"><strong><font color=white >The records of equipment lending</font>
    </strong></font></td>
</table>
     <center>
 
      <input type="hidden" name="RadioGroup1"  id="RadioGroup1" value="viewlending"/>
    
      
	    <table width="800" border="1" align="center">
	
 		<tr bgcolor="#D9E7FF">
 			<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Select</b></div></td>
 			<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Booking Number</b></div></td>
 				<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>User ID</b></div></td>
 			<td width="110" bgcolor="#FFFF99"><div align="center" ><b>User Name</b></div></td>
 		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Major</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>E-mail</b></div></td>
		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Telephone</b></div></td>
			<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Equipment ID</b></div></td>
 		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Equipment Name</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Amount</b></div></td>
		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Start_Date</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Deadline</b></div></td>
				<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Reasons</b></div></td>
	
		
		</tr>
<% 	
	while(rs3.next()){
		
%>
        
        <tr> 
        <td width="110"><div align="center" class="style1"><input type="radio" name="RadioGroup2"  id="RadioGroup2" value=<%=rs3.getString("BookingNumber")%>><br /></div></td>
       <td width="110"><div align="center" class="style1"><%=rs3.getString("BookingNumber")%></div></td>
        <td width="110"><div align="center" class="style1"><%=rs3.getString("UserID")%></div></td>
        <td width="110"><div align="center" class="style1"><%=rs3.getString("name")%></div></td>
		 <td width="110"><div align="center" class="style1"><%=rs3.getString("major")%></div></td>
        <td width="110"><div align="center" class="style1"><%=rs3.getString("e_mail")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs3.getString("telephone")%></div></td>
			<td width="110"><div align="center" class="style1"><%=rs3.getString("EquipmentID")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs3.getString("equipment")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs3.getString("amount")%></div></td>
			<td width="110"><div align="center" class="style1"><%=rs3.getString("Start_Date")%></div></td>
				<td width="110"><div align="center" class="style1"><%=rs3.getString("Deadline")%></div></td>
					<td width="110"><div align="center" class="style1"><%=rs3.getString("reasons")%></div></td>
						
	
		</tr>
		<%}%>
    </table>	
    <br><br>
<table align="center">
<tr>
<td><div align="center" class="style1"><input type="checkbox" name="checkbox" id="checkbox" value="broke" >Broke Equipment</div> <div align="center" class="style1"><input type="checkbox" name="checkbox2" id="checkbox2" value="overdue" >Overdue</div></td>
</tr>
</table>
        <input type="hidden" name="dep" id="dep" value=<%= dep %>>
<br><br><br><br>
<input type="submit" name="submit" id="submit" value="Returned" style="width:80px; height:30px; font-size:15px;"/> <input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> 
 </center>

    
     </form> 
  
</body>
</html>