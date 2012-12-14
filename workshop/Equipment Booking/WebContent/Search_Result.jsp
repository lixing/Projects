<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    <%@ page import="java.sql.*"%>
    <%
    String id =request.getParameter("id");
    String ref="Booking.jsp?id="+id;
    String category=request.getParameter("category");
    String type=request.getParameter("type");
    String start_date=request.getParameter("start_date");
    String end_date=request.getParameter("end_date"); 
    String a="0";%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>  
<meta   http-equiv="Content-Type"   content="text/html;   charset=gb2312">
<title>Search Result</title>
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
    for(var j=0;j<6;j++)
    {
      str[j]=obj.rows[i].cells[j].innerHTML;
    }
    document.form.EquipmentID.value=str[0];
    document.form.equipment.value=str[1];
    document.form.category.value=str[2];
    document.form.type.value=str[3];
    document.form.amount_allowed.value=str[5];
    
  }
  </script>

</head>
<body>

<% 
ResultSet rs;
TestTry.ConnectSql consql = new TestTry.ConnectSql();
 consql.OpenConnection();
rs = consql.SelectEquipment(category,type);
%>
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
<table>
<tr>
<td width="252">&nbsp;</td>
<td width="252">&nbsp;</td>
</tr>
</table>
</form>
<form name="form" action="ConnectJSP">
<table border="0"  cellpadding="0" cellspacing="0">
      <tr>
        <td width="202">&nbsp;</td>
        <td width="620"><span id="p1">&nbsp;&nbsp;<font color="#0099FF" size="+3"> <strong> View of Equipment information</strong></font></span></td>
        <td width="202" height="175"></td>
      </tr>
      </table>
<table width="805" height="173" border="1"  cellpadding="0" cellspacing="0" id="tbTest">
  <tr>
    <td width="192" height="94" bgcolor="#FFFFCC">EquipmentID</td>
    <td width="217" bgcolor="#FFFF99">Equipment</td>
    <td width="285" bgcolor="#FFFFCC">Category</td>
    <td width="171" bgcolor="#FFFF99">Type</td>
    <td width="285" bgcolor="#FFFFCC">Functionality</td>
    <td width="171" bgcolor="#FFFF99">Amount Allowed</td>   
  </tr>
 
<%while(rs.next()){ 
if(!rs.wasNull()){a="1";}%>
<tr onclick="showall(this);">
    <td width="192" height="77"><%=rs.getString("Id") %></td>
    <td width="217"><%=rs.getString("equipment") %></td>
    <td width="217"><%=rs.getString("category") %></td>
    <td width="217"><%=rs.getString("type") %></td>
    <td width="285"><%=rs.getString("functionality") %></td>
    <td width="171"><%=rs.getString("amount_allowed") %></td>
  </tr>
  <%} %>
</table><br/>

<input type="hidden" name="id" id="id" value=<%= id %>>
<input type="hidden" name="equipment" id="equipment" value="">
<input type="hidden" name="amount_allowed" id="amount_allowed" value="">
<input type="hidden" name="EquipmentID" id="EquipmentID" value="">
<input type="hidden" name="start_date" id="start_date" value=<%= start_date %>>
<input type="hidden" name="end_date" id="end_date" value=<%= end_date %>>
<input type="hidden" name="category" id="category" value="">
<input type="hidden" name="type" id="type" value="">
<%if(a.equalsIgnoreCase("1")){ %><input type="submit" name="searchresult" id="searchresult" value="OK" style="width:80px;height:30px;font-size:15px;"/>
<%} %> &nbsp;&nbsp;&nbsp;<input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> 
</form>
</center>
</body>
</html>