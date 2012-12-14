<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<%String ref = request.getHeader("REFERER");
String dep=request.getParameter("dep");
%>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Manage Page</title>
</head>

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
</form>
<form action="ConnectJSP">

 <center>
<br></br>
    <p><font size="+3" color="#0099FF"><strong>Equipment Manage System  </strong></font></p><br></br>
    

  <table>
  <tr align="left"><td>
      <input type="radio" name="RadioGroup1"  id="RadioGroup1" value="View_Modify"checked="checked"/>
      <font color="#0033FF" size="+1">View&nbsp;and&nbsp;Modify&nbsp;Equipment</font><br /><br>
   </td></tr>
   <tr align="left"><td>
      <input type="radio" name="RadioGroup1"  id="RadioGroup1" value="Add" /><font color="#0033FF" size="+1">
      Add&nbsp;New&nbsp;Equipment</font><br /><br>
    </td></tr>
    <tr align="left"><td>
      <input type="radio" name="RadioGroup1"  id="RadioGroup1" value="lending" /><font color="#0033FF" size="+1">
      View&nbsp;Lending&nbsp;Record</font><br /><br>
      </td></tr>
    <tr align="left"><td>
      <input type="radio" name="RadioGroup1"  id="RadioGroup1" value="lent" /><font color="#0033FF" size="+1">
      View&nbsp;Recent&nbsp;Record</font><br /><br>
       </td></tr>
      <tr align="left"><td>
   
      <input type="radio" name="RadioGroup1"  id="RadioGroup1" value="statistic" /><font color="#0033FF" size="+1">
      Equipment&nbsp;Lent&nbsp;Statistic</font><br /><br>
    </td></tr>  </table>
    <input type="hidden" name="dep" id="dep" value=<%= dep %>>
    
  
  <p><br />
  </p>
  <input type="submit" name="Enter" id="Enter" value="Enter" style="width:80px; height:30px; font-size:15px;"/>
  </center>
</form>
<center>

</center></body>
</html>