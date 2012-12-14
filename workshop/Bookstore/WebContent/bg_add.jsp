<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*,com.jspsmart.upload.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Add new books</title>
</head>
<%
SmartUpload mySmartUpload =new SmartUpload();

mySmartUpload.initialize(pageContext);

mySmartUpload.upload();

com.jspsmart.upload.File myFile = mySmartUpload.getFiles().getFile(0);

String myFileName=myFile.getFileName();

myFile.saveAs("D:/workspace/Bookstore/WebContent/images/cover/"+myFileName+"",SmartUpload.SAVE_PHYSICAL); 
%>
<script language="javascript">
function   KeyPressNum(strValue)   
{           
	  var   str   =new   String(strValue);  
	  if   ((window.event.keyCode<47||window.event.keyCode>57))   
	  {window.event.returnValue=false;}   
	  else   
	  {window.event.returnValue=true;}   
	  }
 function checkInput(){
	 var i=document.form2.isbn.value;
	 var t=document.form2.title.value;
	 var a=document.form2.author.value;
	 var p=document.form2.price.value;
	 var b=document.form2.booktype.value;
	 var inf=document.form2.info.value;
	 	if (i==""){
	 		alert("ISBN must not Null !");
	 		document.form2.isbn.focus();
	 		return false;
	 	}else if (t==""){
	 		alert("Title must not Null !");
	 		document.form2.title.focus();
	 		return false;
	 	}else if (a==""){
	 		alert("author code must not Null !");
	 		document.form2.author.focus();
	 		return false;
	 	}else if (p==""){
	 		alert("Price must not Null !");
	 		document.form2.price.focus();
	 		return false;
	 	}else if (b==""){
	 		alert("Book Type must not Null !");
	 		document.form2.booktype.focus();
	 		return false;
	 	}else if (inf==""){
	 		alert("Book information must not Null !");
	 		document.form2.info.focus();
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
<%@include file="bgsider.jsp"  %>
　　　　</div>
<div id="MainBody">
  <form name="form2" method="post" action="bg_addok.jsp?cover=<%=myFileName%>" onsubmit="return checkInput()">
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Now enter the detailed book information here</font>
    </strong></font></td>
</table>
<p>
  <label></label></p>
<table width="343" height="112" border="0" align="center">
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">ISBN:</span></div></th>
    <td><input type="text" name="isbn" onkeypress="return   KeyPressNum();" ></td>
  </tr>
    <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Title:</span></div></th>
    <td><input type="text" name="title"></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Author:</span></div></th>
    <td><input type="text" name="author"></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Price:</span></div></th>
    <td><input type="text" name="price" onkeypress="return KeyPressNum();" ></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Book type:</span></div></th>
    <td><input type="text" name="booktype" onkeypress="return KeyPressNum();" ></td>
  </tr>
   <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1">Book information:</span></div></th>
    <td><textarea name="info" class="input1" cols="60" rows="15"> 
</textarea></td>
  
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