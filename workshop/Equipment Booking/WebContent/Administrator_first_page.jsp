<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%String ref = request.getHeader("REFERER");
  String id=request.getParameter("id");
%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>Untitled Document</title>

 
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
  <p> <center><font size="+3" color="#0099FF"><strong>  Administrator Manage System</strong></font></center></p>
  <form action="ConnectJSP">  
  <center>
<input type="hidden" name="id" id="id" value="<%=id %>">
<table width="295" border="0">
  <tr>
    <td width="227" height="44" bgcolor="#52D0EB" align="left">
      <p>
        <label>
          <input type="radio" name="RadioGroup1" value="all" checked="checked" id="RadioGroup1" />
          <strong>Search all ID</strong>
        </label>
        <br />
        
      </p>
    </td>
  </tr>
  <tr>
    <td height="33" align="left">
      <p>
        <label>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          <input type="radio" name="RadioGroup2" value="manager" checked="checked" id="RadioGroup2" /> 
         <font color="#0033FF"> All Managers</font>
        </label>
        <br />
      </p>
    </td>
  </tr>
  <tr>
    <td align="left" height="33"><label>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       <input type="radio" name="RadioGroup2" value="student" id="RadioGroup2" />
      <font color="#0033FF">All Students</font>
    </label></td>
  </tr>
  <tr>
    <td height="33" align="center"><label>
      <input type="radio" name="RadioGroup2" value="all" id="RadioGroup2" />
      <font color="#0033FF">All Managers and Students</font>
    </label></td>
  </tr>
  <tr>
    <td height="28">&nbsp;</td>
  </tr>
  <tr bgcolor="#52D0EB" align="left">
    <td height="44"><input type="radio" name="RadioGroup1" value="single" id="RadioGroup1" />
     <strong> Search by single ID</strong></td>
  </tr>
  <tr>
    <td height="46" align="center"><font color="#0033FF">Manager :</font>&nbsp;&nbsp;
        <input type="text" name="manager" id="manager" />
    </td>
  </tr>
  <tr>
    <td align="center" height="46"><font color="#0033FF">Student :</font>&nbsp;&nbsp;&nbsp;&nbsp;
        <input type="text" name="student" id="student" />
    </td>
  </tr>
  <tr>
    <td><center>
      <p>&nbsp;        </p>
      <p>
        <input type="submit" name="search" id="search" value="Search" style="width:80px; height:30px; font-size:15px;" />
      </p>
    </center>
    </td>
  </tr>
</table>
</center>
</form>
</body>
</html>
