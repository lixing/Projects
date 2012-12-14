<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Contact Page</title>
</head>
<script language="javascript">
function checkInput(){
	 var n=document.form2.name.value;
	 var e=document.form2.email.value;
	 var i=document.form2.info.value;
	 	if (n==""){
	 		alert("Name must not Null !");
	 		document.form2.name.focus();
	 		return false;
	 	}else if (e==""){
	 		alert("E-mail must not Null !");
	 		document.form2.email.focus();
	 		return false;
	 	}else if (i==""){
	 		alert("Message must not Null !");
	 		document.form2.info.focus();
	 		return false;
	 	} else 
	 		return true;
	 }
function emailValidator(elem, helperMsg){
	var emailExp = /^[\w\-\.\+]+\@[a-zA-Z0-9\.\-]+\.[a-zA-z0-9]{2,4}$/;
	if(elem.value.match(emailExp)){
		return true;
	}else{
		alert(helperMsg);
		elem.focus();
		return false;
	}
}

</script>
<body>
<div id="container">
　　<div id="Header">
  　</div>
</div>
<table width="960" >
</table> 
　　<div id="PageBody" >
　　　　<div id="Sidebar" align="left">
<%@include file="sider.jsp"  %>
　　　　</div><div id="MainBody">
		<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Contact us</font>
    </strong></font></td>
</table>
        <table width="420" height="182" border="0" align="center">
          <tr>
            <td width="100" align="right">Name :</td>
            <td width="20" ></td>
            <td width="300" >Michael Gao</td>
          </tr>
          <tr>
            <td align="right">Phone :</td>
            <td></td>
            <td>13750023491</td>
          </tr>
          <tr>
            <td align="right">E-mail :</td>
            <td></td>
            <td>gqqqq903@163.com</td>
          </tr>
          <tr>
            <td align="right">QQ:</td>
            <td></td>
            <td>147540435</td>
          </tr>
        </table>
<br><br><br><br>
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Leave messages here</font>
    </strong></font></td>
</table>  
  <form name="form2" method="post" action="messageok.jsp" onsubmit="return checkInput()">
<table width="343" height="112" border="0" align="center">
  <tr>
    <th class="style2" scope="row"><div><span class="style1">Your Name:</span></div></th>
    <td><input type="text" name="name"></td>
    </tr>
    <tr>
    <th class="style2" scope="row"><div><span class="style1">Your Email:</span></div></th>
    <td><input type="text" name="email" id="email" onclick="emailValidator(document.getElementById('email'), 'Not a Valid Email')"></td>
  </tr>
    <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Your comments:</span></div></th>
    <td><textarea name="info" class="input1" cols="60" rows="10"> 
</textarea></td>
  </tr>
</table>
<p>&nbsp;</p>
  <div align="center">
    <p><input name="Submit3" type="submit" class="style2" value="Submit" ></p>
 </div>
 </form> 
<br><br><br><br>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/bback.jpg "onClick="location.href='index.jsp'" /><font size="4px">Back to Index&nbsp; &nbsp; &nbsp;</font></p></td> 
</tr></table>   
</div>
　　　　</div>
<%@include file="footer.jsp"  %>
</body>
</html>