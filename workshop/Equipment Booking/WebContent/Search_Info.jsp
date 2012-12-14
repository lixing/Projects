<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    <%@ page import="java.sql.*"%>
    <%
      String id =request.getParameter("id");
    String ref="Administrator_first_page.jsp?id="+id;
      String manager="";
      manager=request.getParameter("manager");
	  String student="";
	  student=request.getParameter("student");
      String radio =request.getParameter("radio");
      String a="0";%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>User Info</title>
<script type="text/javascript">
    var currentActiveRow;
  function showall(obj)
  { 
	  if(currentActiveRow)   
		     currentActiveRow.style.backgroundColor="";   
		     currentActiveRow=obj; 
		     currentActiveRow.style.backgroundColor="Red";
	var i=obj.rowIndex;
	var obj=document.getElementById("tbTest");  
    var str=new Array();
    for(var j=0;j<3;j++)
    {
      str[j]=obj.rows[i].cells[j].innerHTML;
    }
    document.form.old_name.value=str[0];
    document.form.old_id.value=str[1];
    document.form.old_authority.value=str[2];
  }
  </script>
<SCRIPT LANGUAGE="JavaScript">
<!--
function openPop()
{
    window.open("popup_upload.html", "startpop", "width=600, height=337, scrollbars=no, resizable=no ,status=no , toolbar=no");
}
//-->
</SCRIPT>

</head>
<% 
ResultSet rs;
TestTry.ConnectSql consql = new TestTry.ConnectSql();
 consql.OpenConnection();
 if(!manager.equals("")){
	 rs = consql.SelectMID(manager);
 }
 else if(!student.equals("")){ 
	 rs = consql.SelectSID(student);
 }
 else if((radio.equalsIgnoreCase("student"))||(radio.equalsIgnoreCase("manager"))){
	 rs = consql.Selectid(radio);
 } 
 else{
	 rs=consql.SelectAll();
 }
%>
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
<form name="form" action="ConnectJSP">
<center>
<br>
<p> <font size="+3" color="#0099FF"><strong> List</strong></font></p><br>
    <table align="center" width="700" border="2" id="tbTest" style="border-color:#369; text-align: center; font-size: 18px;">
      <tr>
        <td width="150" height="60" bgcolor="#FFFFCC" align="center">Name</td>
        <td width="150" bgcolor="#FFFF99" align="center">ID</td>
        <td width="150" bgcolor="#FFFFCC" align="center">Authority</td>
      </tr>
      <%try{
    	  while(rs.next()){ 
    	  if(!rs.wasNull()){ a="1"; }%>
      <tr onclick="showall(this);">
        <td height="60"><%=rs.getString("name") %></td>
        <td><%=rs.getString("Id") %></td>
        <td><%=rs.getString("identity") %></td>
      </tr>
      <%}}catch(Exception e){
		  System.out.println("Null"); 
	  } %>
     
    </table>
    <table>
  <tr>
    <td>&nbsp;</td>
    <td><CENTER>
   <%if(a.equalsIgnoreCase("1")){ %><br> <input type="submit" name="modify" id="modify" value="MODIFY"  style="width:80px;height:30px;font-size:15px;"/>
     <%}%>&nbsp;&nbsp;&nbsp;<input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> </center></td>
    <td height="0">&nbsp;</td>
  </tr>
  
</table>
<input type="hidden" name="id" id="id" value=<%=id %>>
<input type="hidden" name="old_id" id="old_id" value="">
<input type="hidden" name="old_name" id="old_name" value="">
<input type="hidden" name="radio" id="radio" value=<%=radio %>>
<input type="hidden" name="manager" id="manager" value="<%=manager %>">
<input type="hidden" name="student" id="student" value="<%=student %>">
<input type="hidden" name="old_authority" id="old_authority" value="">
</center>
</form>
<center>
</center>
</body>
</html>
