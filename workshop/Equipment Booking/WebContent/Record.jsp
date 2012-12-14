<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    <%@ page import="java.sql.*"%>
    <%String ref = request.getHeader("REFERER");
    String id =request.getParameter("id");%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>My Record</title>
</head>

<body>
<% 
ResultSet rs1,rs2;
TestTry.ConnectSql consql = new TestTry.ConnectSql();
 consql.OpenConnection();
rs1 = consql.SelectRecord(id);
rs2 = consql.SelectInfo(id);
String credit="null";
%>
<form>
<table  background="img/bg.png">
  <tr>
    <td width="950">&nbsp;</td>
    <td width="520"><p>&nbsp;</p>
    <p>&nbsp;</p>
  <td width="150" height="85"><a href="Login.jsp"><img src="img/logout_memo.png"  border="0" width="40" height="50" /></a></td>

</tr>
</table>
</form>
<center><br />
 <font size="+3" color="#0099FF"><strong> Book information search</strong></font><br /><br />
 <br />
 
<table width="1300" border="1"  cellpadding="0" cellspacing="0" id="tbTest" align="center">
  <tr>
     <td width="71" height="64" bgcolor="#FFFFCC">Credit</td>
     <td width="84" "#FFFF99">Booking No.</td>
    <td width="75" bgcolor="#FFFFCC">UserID</td>
    <td width="87" "#FFFF99">EquipmentID</td>
    <td width="188" bgcolor="#FFFFCC" align="center">E_mail</td>
    <td width="131" "#FFFF99">Telephone</td>   
    <td width="89" bgcolor="#FFFFCC">Equipment</td>
    <td width="48" "#FFFF99">Amount</td>
    <td width="135" bgcolor="#FFFFCC">Start Date</td>
    <td width="118" "#FFFF99">Deadline</td>   
    <td width="100" bgcolor="#FFFFCC" align="center">Reasons</td> 
    <td width="50" "#FFFF99" align="center">Status</td>  
  </tr>
<%while(rs2.next()){ credit=rs2.getString("credit");}%>
 <%while (rs1.next()){%>
  <tr>
     <td width="42" height="43"><%=credit%></td>
    <td width="106"><%=rs1.getString("BookingNumber") %></td>
    <td width="50"><%= rs1.getString("UserID")%></td>
    <td width="90"><%= rs1.getString("EquipmentID")%></td>
    <td width="41"><%= rs1.getString("e_mail")%></td>  
    <td width="63"><%=rs1.getString("telephone") %></td>  
    <td width="72"><%=rs1.getString("equipment") %></td>
    <td width="53"><%= rs1.getString("amount")%></td>
    <td width="46"><%= rs1.getString("Start_Date")%></td>
    <td width="66"><%= rs1.getString("Deadline")%></td>    
        <td width="69"><%= rs1.getString("reasons")%></td>
    <td width="56"><%= rs1.getString("Status")%></td>
  </tr>
  <%} %>
  </table>
   <form action="javascript:window.location='<%=ref%>'">
   <input type="hidden" name="id" id="id" value=<%=id %>><br/><br/><br/>
  <input type="submit" value="Back" style="width:80px;height:30px;font-size:15px;"/>
  </form>
</center> 

</body>
</html>