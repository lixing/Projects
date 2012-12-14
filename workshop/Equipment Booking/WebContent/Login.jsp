<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>Login</title>
<script language="JavaScript"> 
function nav(x) {
history.go(x);
}
</script>
</head>
 
<body>
<table  background="img/bg.png">
  <tr>
    <td width="950">&nbsp;</td>
    <td width="520"><p>&nbsp;</p>
    <p>&nbsp;</p>
  <td width="150" height="85"><a href="Login.jsp"><img src="img/logout_memo.png"  border="0" width="40" height="50" /></a></td>

</tr>
</table>
<form action="ConnectJSP">
<center>
<table width="1024" height="495" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td width="252">&nbsp;</td>
    <td width="520"><p>&nbsp;</p>
    <p>&nbsp;</p>
    <p><font size="+3" color="#0099FF"><center><strong>Log in</strong></center></font></p></td>
    <td width="252" height="150"></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>
      <span>
     <center>
       <font size="+1" color="#0033FF">LOG IN AS</font>
       &nbsp;&nbsp;&nbsp;&nbsp;
       <select name="select" style="width:100px;height:20px;font-size:15px;">
  <option value="student">Student</option>
  <option value="manager">Manager</option><option value="administrator">Administrator</option></select></center>
  <br><br />
<center>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font size="+1" color="#0033FF">ID</font>&nbsp;&nbsp;&nbsp;&nbsp;
     <input name="id" type="text" id="id" size="20"maxlength="20"style="width:100px;height:20px;font-size:15px;" /></center>
      <br /><br>
      </span>
      <center>
        <font size="+1" color="#0033FF">PASSWORD</font>&nbsp;&nbsp;
        <input name="password" type="password" id="password" size="20"maxlength="20"style="width:100px;height:20px;font-size:15px;" /></center>
    </td> 
    <td height="159">&nbsp;</td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>
       <center><input type="submit" name="login" id="login" value="LOGIN" style="width:80px;height:30px;font-size:15px;"/></center>
     </td>
    <td height="85">&nbsp;</td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td height="70">&nbsp;</td>
  </tr>
</table></center>
</form>
</body>
</html>
