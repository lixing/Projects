<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Background</title>
</head>
<body>
<div id="container">
　　<div id="Header">
  　</div></div>   
　　<div id="PageBody" >
　　　　　　　　<div id="Sidebar" align="left">
<%@include file="sider.jsp"  %>
　　　　</div>
　　　　<div id="MainBody">   
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Background Management System</font>
    </strong></font></td>
</table>
<table width="200" border="2" align="center">
<tr>
<td><img src="./images/bg/view.jpg" width="100" height="100" onClick="location.href='bg_view.jsp'" /></td>
<td><img src="./images/bg/post.jpg" width="100" height="100" onClick="location.href='bg_post.jsp'" /></td>
<td><img src="./images/bg/add.jpg" width="100" height="100" onClick="location.href='bg_upload.jsp'" /></td>
<td><img src="./images/bg/newold.jpg" width="100" height="100" onClick="location.href='bg_newold.jsp'" /></td>
<td><img src="./images/bg/store.jpg" width="100" height="100" onClick="location.href='bg_store.jsp'" /></td>
<td><img src="./images/bg/deliver.jpg" width="100" height="100" onClick="location.href='bg_deliver.jsp'" /></td>
<td><img src="./images/bg/message.jpg" width="100" height="100" onClick="location.href='bg_message.jsp'" /></td>
</tr>
<tr><td>View all books</td>
<td>Post/Drop books</td>
<td>Add new books</td>
<td>Change new books</td>
<td>Increase storage</td>
<td>Deliver books</td>
<td>Message Board Management</td>
</tr>
</table>
    </div></div><%@include file="footer.jsp"  %>
</body>
</html>