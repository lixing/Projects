<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    <%@ page import="java.sql.*"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Modify Amount</title>
</head>

<%
String dep=request.getParameter("dep"); 
String ref = "View.jsp?dep="+dep;
ResultSet rs1;
String id =request.getParameter("id"); 
TestTry.ConnectSql consql = new TestTry.ConnectSql();
consql.OpenConnection();
rs1 = consql.SelectEquipment1(id);
String amount="";
%>
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
<body>

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
    <td width="600" align="center"><font size="5px"><strong><font color=white >You can modify the amount of the equipment</font>
    </strong></font></td>
    
</table>
 <center>
 <br><br>
	    <table width="800" border="1" align="center">
 		<tr >
 		<td width="110" bgcolor="#FFFFCC" ><div align="center" ><b>Equipment ID</b></div></td>
 		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Equipment Name</b></div></td>
		<td width="110" bgcolor="#FFFFCC" ><div align="center" ><b>Category</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Type</b></div></td>
		<td width="110" bgcolor="#FFFFCC" ><div align="center" ><b>Functionality</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Total</b></div></td>
		<td width="110" bgcolor="#FFFFCC" ><div align="center" ><b>Amount Allowed</b></div></td>
		<td width="110" bgcolor="#FFFF99"><div align="center" ><b>Broken</b></div></td>
		
		</tr>
		
<% 	
	while(rs1.next()){
		
%>
        
        <tr> 
            
        <td width="110"><div align="center" class="style1"><%=rs1.getString("Id")%></div></td>
		 <td width="110"><div align="center" class="style1"><%=rs1.getString("equipment")%></div></td>
        <td width="110"><div align="center" class="style1"><%=rs1.getString("category")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("type")%></div></td>
		<td width="110"><div align="center" class="style1"><%=rs1.getString("functionality")%></div></td>
		  <td width="110"><div align="center" class="style1"><input width="50" type="text" value=<%=rs1.getString("Total")%> size="2" id="Amount" name="Amount"  onkeypress="return KeyPressNum();"></div></td>
		 <td width="110"><div align="center" class="style1"><input width="50" type="text" value=<%=rs1.getString("amount_allowed")%> size="2" id="allowed" name="allowed"  onkeypress="return KeyPressNum();"></div></td>
		  <td width="110"><div align="center" class="style1"><input width="50" type="text" value=<%=rs1.getString("broken")%> size="2" id="broken" name="broken"  onkeypress="return KeyPressNum();"></div></td>

	
		</tr>
		<%} %>
    </table>	
      </center>
      <input type="hidden" name="RadioGroup1"  id="RadioGroup1" value="ModifyAmount" />
    <br><br>
    <center>
  <b><font color="#0033FF" size="+1"><strong>Type in the amount you want to modify </strong></font></b>
<br></center>
<center><br><br>
 <input type="submit" name="submit" id="submit" value="Modify" style="width:80px; height:30px; font-size:15px;" /> &nbsp;&nbsp;&nbsp; <input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> 
   </center>
 <input type="hidden" name="dep" id="dep" value=<%= dep %>>
  <input type="hidden" name="id" id="id" value=<%= id %>>
     </form> 
         
</body>
</html>