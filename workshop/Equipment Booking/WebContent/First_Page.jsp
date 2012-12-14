<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<%
String id=request.getParameter("id");
%>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>First Page</title>

</head>

<body>
<center>
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
<input type="hidden" name="id" id="id" value=<%= id %>></td>
  <p> <center>
    <p><font color="#0099FF" size="+3"> <strong>Equipment Loan System</strong></font></p>
    <p>&nbsp;</p>
  </center></p>
  <center>
  <p>
 
    <label>
     <input name="RadioGroup1" type="radio" id="RadioGroup1" value="Booking" checked="checked" />
      </label> <font size="+2" color="#0033FF"><strong>Booking</strong></font><br /><br>
    <label>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <input type="radio" name="RadioGroup1" id="RadioGroup1" value="MyRecord" />
      <font size="+2" color="#0033FF"><strong>My Record</strong></font><br />
    </label>
    </p>
  <p><br />
  </p>
   </center>
 
  <input type="submit" name="Enter" id="Enter" value="ENTER"  style="width:80px; height:30px; font-size:15px"/>
    
</form>
</center>
</body>

</html>
