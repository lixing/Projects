<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Customer Information</title>
</head>
<script language="javascript">
function   KeyPressNum(strValue)   
{           
	  var   str   =new   String(strValue);  
	  if   ((window.event.keyCode<47||window.event.keyCode>57))   
	  {window.event.returnValue=false;}   
	  else   
	  {window.event.returnValue=true;}   
	  }
 function  NameCheck(strValue)   
{           
	  var   str   =new   String(strValue);  
	  if   ((window.event.keyCode<31 ||(window.event.keyCode>33 && window.event.keyCode<64) ||(window.event.keyCode>90 && window.event.keyCode<97)  ||	 window.event.keyCode>122)  )   
	  {window.event.returnValue=false;}   
	  else   
	  {window.event.returnValue=true;}   
	  }
 function checkInput(){
	 var n=document.form2.name.value;
	 var a=document.form2.address.value;
	 var z=document.form2.zipcode.value;
	 var c=document.form2.cellphone.value;
	 	if (n==""){
	 		alert("Name must not Null !");
	 		document.form2.name.focus();
	 		return false;
	 	}else if (a==""){
	 		alert("Address must not Null !");
	 		document.form2.address.focus();
	 		return false;
	 	}else if (z==""){
	 		alert("Zip code must not Null !");
	 		document.form2.zipcode.focus();
	 		return false;
	 	}else if (c==""){
	 		alert("Cell phone number must not Null !");
	 		document.form2.cellphone.focus();
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
  <form name="form2" method="post" action="paybill.jsp" onsubmit="return checkInput()">
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Please enter your information here</font>
    </strong></font></td>
</table>
<p>
  <label></label></p>
<table width="343" height="112" border="0" align="center">

  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Name:</span></div></th>
    <td><input type="text" name="name" onkeypress="return NameCheck();" ></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Address:</span></div></th>
    <td><input type="text" name="address" ></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Zip Code:</span></div></th>
    <td><input type="text" name="zipcode" onkeypress="return   KeyPressNum();" ></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Cellphone:</span></div></th>
    <td><input type="text" name="cellphone" onkeypress="return   KeyPressNum();" ></td>
  </tr>
</table>
<p>&nbsp;</p>
  <div align="center">
    <p><input name="Submit3" type="submit" class="style2" value="Submit" ></p>
 </div>
 </form>
  </div></div>
<%@include file="footer.jsp"  %>
</body>
</html>