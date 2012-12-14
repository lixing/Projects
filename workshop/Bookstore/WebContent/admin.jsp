<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GB18030">
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Admin login</title>
</head>
<script language=javascript>
function checkInput(){
var t_name=document.login.ad_name.value;
var t_pw=document.login.ad_pw.value;
	if (t_name=="" || t_pw==""){
		alert("Admin Name and Password must not Null !");
		document.login.ad_name.focus();
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
　　<div id="PageBody" >
　　　　<div id="Sidebar" align="left">
<%@include file="sider.jsp"  %>
　　　　</div>

    <div id="MainBody">
<table width="600" border="0" align="center">
  <tr>
    <td>
	<table width="100%" height="100%" border="3" cellpadding="0" cellspacing="0" bordercolor="#000000">
		<tr><td height="440" align="center" valign="middle" bordercolor="#666666"> 
			<form method="Post" action='login.jsp' name="login" onsubmit="return checkInput()">
				<table width="300" height="200" border="0" cellpadding="0" cellspacing="0" bgcolor="#CCCC99" >
					<tr>
						<td class="style3" align="left">&nbsp; Administrator</td>
					</tr>
					<tr>
						<td align="right" class="style2" width="130">Admin Name:&nbsp;</td>
						<td width="170" align="left" class="style2"><input type="text" name="ad_name" /></td>
					</tr>
					<tr>
						<td align="right" class="style2" width="130">Password:&nbsp;</td>
						<td align="left" class="style2"><input type="password" name="ad_pw" /></td>
					</tr>
					<tr>
						<td colspan="2" align="center"><input type="submit" value="Login" class="style2"/>&nbsp;
						<input type="reset" value="Reset" class="style2"/>&nbsp;
					</tr>
				</table>
			</form>
		</td>
		</tr>
	</table>
    </td>
  </tr>
  <tr>
  </tr>
</table>
</div>    </div><%@include file="footer.jsp"  %>
</body>
</html>