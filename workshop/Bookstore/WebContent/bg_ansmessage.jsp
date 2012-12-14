<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Answer messages</title>
</head>
<script language="javascript">
function checkInput(){
	 var a=document.form2.answer.value;
	 	if (a==""){
	 		alert("Name must not Null !");
	 		document.form2.answer.focus();
	 		return false;
	 	} else 
	 		return true;
	 }
</script>
<body>
<div id="container">
　　<div id="Header">
  　</div>
</div>
<table width="960" >
</table> 
<%String id=request.getParameter("id");%>
　　<div id="PageBody" >
<div id="Sidebar" align="left">
<%@include file="bgsider.jsp"  %>
　　　　</div><div id="MainBody">
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Admin answer message here</font>
    </strong></font></td>
</table>
<form name="form2" method="post" action="bg_ansok.jsp?id=<%=id%>" onsubmit="return checkInput()">
<table width="343" height="112" border="0" align="center">
    <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">My answers:</span></div></th>
    <td><textarea name="answer" class="input1" cols="60" rows="10"> 
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
<tr><td><p align="center"><img src="./images/bg/smessage.jpg "onClick="location.href='bg_message.jsp'" /><font size="4px">Back to Message Management&nbsp; &nbsp; &nbsp;</font></p></td> 
<td><p align="center"><img src="./images/bg/bback.jpg "onClick="location.href='background.jsp'" /><font size="4px">Back to Background</font></p></td></tr></table>  
</div>　　　　</div>
<%@include file="footer.jsp"  %>
</body>
</html>