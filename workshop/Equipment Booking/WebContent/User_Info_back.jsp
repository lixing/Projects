<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<%String ref = request.getHeader("REFERER");
String id =request.getParameter("id");
String EquipmentID =request.getParameter("EquipmentID");
String amount_allowed=request.getParameter("amount_allowed");
String start_date=request.getParameter("start_date");
String end_date=request.getParameter("end_date");
String equipment=request.getParameter("equipment");
String Name =request.getParameter("Name");
String Major =request.getParameter("Major");
String E_mail=request.getParameter("E_mail");
String Telephone=request.getParameter("Telephone");
String Amount=request.getParameter("Amount");
String Reasons="null";
Reasons=request.getParameter("Reasons");
String credit=request.getParameter("credit");
String category=request.getParameter("category");
String type=request.getParameter("type");
%>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>User Information</title>
<script>
 function isEmail(strEmail) {  
  if (strEmail.search(/^\w+((-\w+)|(\.\w+))*\@[A-Za-z0-9]+((\.|-)[A-Za-z0-9]+)*\.[A-Za-z0-9]+$/) != -1)  
  return true;  
  else  
  alert("Input the right e-mail address");  
  }  

</script>
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
<table>
<tr>
<td width="252">&nbsp;</td>
<td width="252">&nbsp;</td>
</tr>
</table>
</form>
<form action="ConnectJSP">
<center>
<p><font color="#0099FF" size="+3"> <strong> Apply information</strong></font> </p>
<table width="600" border="0">
  <tr align="center">
    <td width="300"><font color="#0033FF"><strong>&nbsp;&nbsp;&nbsp;&nbsp;ID:&nbsp;&nbsp;:&nbsp;&nbsp; </strong></font>
      <input type="text"  height="20"name="id" id="id" value="<%=id %>" readonly="readonly" /></td>
    <td width="300"  height="44"><font color="#0033FF"><strong>Name: </strong></font>
      <input type="text" name="Name" id="Name" value="<%=Name %>"readonly="readonly" /></td>
    </tr>
  <tr  align="center">
    <td><font color="#0033FF"><strong>Major&nbsp;&nbsp;:&nbsp;&nbsp; </strong></font>
      <input type="text" name="Major" id="Major"value="<%=Major %>"readonly="readonly" /></td>
    <td height="52"><font color="#0033FF"><strong>E-mail&nbsp;&nbsp;:&nbsp;&nbsp; </strong></font>
      <input type="text"  name="E-mail" id="E-mail"value="<%=E_mail %>"onmouseout="isEmail(this.value)"/></td>
    </tr>
  <tr align="center">
    <td><font color="#0033FF"><strong>Telephone&nbsp;&nbsp;:&nbsp;&nbsp; </strong></font>
      <input type="text" name="Telephone" maxlength="11" id="Telephone"  value="<%=Telephone %>" onkeyup="value=value.replace(/[^\d]/g,'') " 
    onbeforepaste="clipboardData.setData('text',clipboardData.getData('text').replace(/[^\d]/g,''))" /></td>
    <td height="52"><font color="#0033FF"><strong>Amount&nbsp;&nbsp;:&nbsp;&nbsp; </strong></font>
      <input type="text" name="Amount" id="Amount"  value="<%=Amount %>" onkeyup="value=value.replace(/[^\d]/g,'') " 
onbeforepaste="clipboardData.setData('text',clipboardData.getData('text').replace(/[^\d]/g,''))" /></td>
    </tr>
  <tr >
    <td align="center"><font color="#0033FF"><strong>Reasons&nbsp;&nbsp;:&nbsp;&nbsp; </strong></font>
    <input type="text" name="Reasons" id="Reasons" value="<%=Reasons %>" width="80px;" height="80px;"/></td>
  </tr>
</table>
<br><br>
<input type="hidden" name="start_date" id="start_date" value=<%= start_date %>>
<input type="hidden" name="end_date" id="end_date" value=<%= end_date %>>
<input type="hidden" name="amount_allowed" id="amount_allowed" value="<%=amount_allowed %>">
<input type="hidden" name="EquipmentID" id="EquipmentID" value="<%=EquipmentID %>">
<input type="hidden" name="equipment" id="equipment" value="<%=equipment%>">
<input type="hidden" name="credit" id="credit" value="<%=credit%>">
<input type="hidden" name="category" id="category" value="<%=category %>">
<input type="hidden" name="type" id="type" value="<%=type%>">
  <input type="submit" name="submit1" id="submit1" value="SUBMIT" style="width:80px;height:30px;font-size:15px;"/> 
  <input type="button" name="back" id="back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px;height:30px;font-size:15px;"/>
</center>
</form>
</body>
</html>