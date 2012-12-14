<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <% 
      String id =request.getParameter("id");
    String ref = "Administrator_first_page.jsp?id="+id;
      String old_id=request.getParameter("old_id");
      String old_name=request.getParameter("old_name");
      String old_authority=request.getParameter("old_authority");%>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>Modify_Info</title>

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
<br><br>
<font color="#0099FF" size="+3"> <strong>Modify Information</strong></font>
</form>
<form action="ConnectJSP">
<input type="hidden" name="old_id" id="old_id" value=<%=old_id %>>
<table width="800" height="400" border="0" align="center" cellpadding="0" cellspacing="0">
 
  <tr>
    <td>&nbsp;</td>
    <td>
      <font color="#0033FF"><strong>Name: </strong></font>
      <input name="new_name" type="text" id="new_name" value="<%=old_name %>"size="20" maxlength="20" style=" font-size:18px" />
      <br /><br>
     <font color="#0033FF"><strong>&nbsp;&nbsp;&nbsp;&nbsp;ID:&nbsp;&nbsp;&nbsp;&nbsp; </strong></font> 
      <input name="new_id" type="text" id="new_id" size="20" value="<%=old_id %>"maxlength="20"style=" font-size:18px" /><br> <br>   
      <font color="#0033FF"><strong>Authority</strong></font>
       &nbsp; 
       <input name="new_authority" type="text" id="new_authority" value="<%=old_authority %>"size="20"maxlength="20"style=" font-size:18px" /> 
    
    </td>
    <td >&nbsp;</td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td> 
      <input type="hidden" name="old_name" id="old_name" value="<%=old_name %>">
       <input type="hidden" name="old_authority" id="old_authority" value="<%=old_authority %>">
      <input type="button" name="back" id="back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px;height:30px;font-size:15px;"/>
     &nbsp; &nbsp; 
       <input type="submit" name="save" id="save" value="SAVE" style="width:80px;height:30px;font-size:15px;"/>
      </td>
    <td height="150">&nbsp;</td>
  </tr>

</table>
</form>
</center>
</body>
</html>