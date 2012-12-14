<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*,java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>View all records</title>
</head>
<body>


<% 
String dep=request.getParameter("dep");
String ref = "Manager_first_page.jsp?dep="+dep;
ResultSet rs1;
TestTry.ConnectSql consql = new TestTry.ConnectSql();
 consql.OpenConnection();
rs1 = consql.ShowEquipment(dep);
%> 
<form action="ConnectJSP">
<table  background="img/bg.png">
  <tr>
    <td width="950">&nbsp;</td>
    <td width="520"><p>&nbsp;</p>
    <p>&nbsp;</p></td>
  <td width="150" height="85"><a href="Login.jsp"><img src="img/logout_memo.png"  border="0" width="40" height="50" /></a></td>

</tr>
</table>
<br>   <br>
<center>
<table width="806" height="35" border="0" bgcolor="#52D0EB"  style="border-collapse:collapse;">
<tr>
    <td width="600" align="center"><font size="5px"><strong><font color=white >Here is the list of equipment, you can increase the amount</font>
    </strong></font></td>
</table></center>
<br><br>
<center>
<table width="1117" border="10">
  <tr>
    <td width="800"><table width="800" border="1" align="center">
 		<tr >
 		<td width="110" bgcolor="#FFFFCC" ><div align="center" ><b>Select the Equipment</b></div></td>
 		<td width="110"  bgcolor="#FFFF99"><div align="center" ><b>Equipment ID</b></div></td>
 		<td width="110" bgcolor="#FFFFCC"><div align="center"  ><b>Equipment Name</b></div></td>
		<td width="110"  bgcolor="#FFFF99"><div align="center" ><b>Category</b></div></td>
		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Type</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center"  ><b>Functionality</b></div></td>
		<td width="110"  bgcolor="#FFFFCC"><div align="center"><b>Total</b></div></td>
		<td width="110"  bgcolor="#FFFF99"><div align="center" ><b>Amount Allowed</b></div></td>
		<td width="110" bgcolor="#FFFFCC"><div align="center" ><b>Broken</b></div></td>
		</tr>
<% 	

	while(rs1.next()){
	
%>
        
        <tr> 
        <td width="110"><div align="center" class="style1"><input type="radio" name="RadioGroup2"  id="RadioGroup2" value=<%=rs1.getString("Id")%>><br /></div></td>
        <td width="110"><div align="center" class="style1"><%=rs1.getString("Id")%></div></td>
		 <td width="110"><div align="center" class="style1"><%=rs1.getString("equipment")%></div></td>
        <td width="110"><div align="center" class="style1"><%=rs1.getString("category")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("type")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("functionality")%></div></td>
		  <td width="110"><div align="center" class="style1"><%=rs1.getString("Total")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("amount_allowed")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("broken")%></div></td>
		</tr>
		<%} %>
    </table>	</td>
    <td width="301"> <table>
       <tr align="left"><td>   
      <input type="radio" name="RadioGroup1"  id="RadioGroup1" value="info" checked="checked"/>
       <font color="#0033FF" size="+1"><strong>Modify Equipment Infomation</strong></font><br /><br />
       </td></tr>
 <tr align="left"><td>
      <input type="radio" name="RadioGroup1"  id="RadioGroup1" value="addamount" />
      <font color="#0033FF" size="+1"><strong>Modify Amount</strong></font><br /><br />
    </td></tr>
    <tr align="left"><td>   
      <input type="radio" name="RadioGroup1"  id="RadioGroup1" value="delete"/>
       <font color="#0033FF" size="+1"><strong>Delete Equipment</strong></font><br /><br />
       </td></tr>
 </table>
   
<div align="center">
    <p><input type="submit" name="submit" id="submit" value="SUBMIT" style="width:80px; height:30px; font-size:15px;" /> &nbsp;&nbsp;&nbsp; <input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> </p>
 </div>
 <input type="hidden" name="dep" id="dep" value=<%= dep %>>

</td>
  </tr>
</table>
</center>
</form>
</body>
</html>