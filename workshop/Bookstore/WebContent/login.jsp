<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Login fail</title>
</head>
	<%
	String ad_n=request.getParameter("ad_name");
	String ad_pw=request.getParameter("ad_pw");
	
	if (ad_n.equals("gq") && ad_pw.equals("123")){
		session.setAttribute("ad_name",ad_n);
	%><jsp:forward page="background.jsp"/> 
	<%}else{%>  
<body>
<div id="container">
　　<div id="Header">
  　</div></div>   
　　<div id="PageBody" >
　　　　<div id="Sidebar" align="left">
<%@include file="sider.jsp"  %>
　　　　</div>
    <div id="MainBody">
   <table width="806" border="0" align="center">
  <tr>
  	<td height="300">
  		<br><h2 align="center" class="style3">Login Failed! </h2>
  		<br><h2 align="center" class="style3">Your admin name or password is wrong! </h2>
  	</td>
  </tr>
</table>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/login.jpg "onClick="location.href='admin.jsp'" /><font size="4px">Login again&nbsp; &nbsp; &nbsp;</font></p></td> 
<td><p align="center"><img src="./images/bg/back.jpg "onClick="location.href='index.jsp'" /><font size="4px">Back to index</font></p></td></tr></table>       
   </div>  </div>
  <%
  }%>
  <%@include file="footer.jsp"  %>
</body>
</html>