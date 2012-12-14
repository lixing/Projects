<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*,java.util.Calendar,java.text.*,java.text.DecimalFormat"%>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Shopping Cart</title>
</head>
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
    <%
    String name = new String(request.getParameter("name").getBytes("ISO-8859-1"),"UTF-8");
    String address = new String(request.getParameter("address").getBytes("ISO-8859-1"),"UTF-8");
    String zipcode=request.getParameter("zipcode");
    String cellphone=request.getParameter("cellphone");
    int ordNo=0;
    try{
    	Connection conn;
		Statement sta;
		ResultSet insert,cus,ord; 
		Class.forName(drv);
		conn = DriverManager.getConnection(url1,user,passwd);
		sta=conn.createStatement();		
	        sta.executeUpdate("INSERT INTO customers(name,address,zip,phone) VALUES('"+name+"','"+
				address+"',"+zipcode+","+cellphone+");");  
	        cus=sta.executeQuery("SELECT customerID FROM customers AS C "+"WHERE C.name='"+name+"';");
	        cus.next();
	        int cusID=cus.getInt(1);
	        
	        ord=sta.executeQuery("SELECT max(orderNo) FROM orderbk;");
	        ord.next();
	        	ordNo=ord.getInt(1);
	        	ordNo++;

	        ResultSet r1= sta.executeQuery
	        ("select isbn,title,author,price,amount from cart");
	    	while(r1.next()){	
	    		Statement sta2=conn.createStatement();
	    		  sta2.executeUpdate
	    		  (
	    				  " INSERT INTO orderbk(orderno,isbn,title,author,price,amount) VALUES " +
	    				  " ("+ordNo+",'"+r1.getString(1)+"','"+r1.getString(2)+"','"+r1.getString(3)+"','"+r1.getString(4)+"','"+r1.getString(5)+"')"); 
		 
	          		 sta2.executeUpdate("UPDATE books SET number=number-"+r1.getString(5)+" "+
	          			 "WHERE isbn="+r1.getString(1)+"; ");  					
	             }
	        	
	            Date currentTime = new Date();
	            SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	            String dateString = formatter.format(currentTime);          
	            sta.executeUpdate("INSERT INTO orders (orderNo,customerID,createdDate,delivery) VALUES" +
	            		" ("+ordNo+","+cusID+",'"+dateString+"','NO');");
	            sta.executeUpdate("delete from cart");

		sta.close();
		conn.close();
        }catch(SQLException ex){
	    out.println("SQL error : " +ex);
}
       
%>
<p align="center"><font size="4px">Thank you for your custom.</font></p>
<p align="center"><font size="4px">Your order has been successfully set up.</font></p>
<p align="center"><font size="4px">And now our store will show your order number.</font></p>
<p align="center"><font size="4px">The number is <%out.println(ordNo);%>.</font></p>
<p align="center"><font size="4px">You can check your order's detail from order search.</font></p>
<br><br><br><br>
<table align ="center">
<tr><td><p align="center"><img src="./images/bg/back.jpg "onClick="location.href='index.jsp'" /><font size="4px">Back to Index&nbsp; &nbsp; &nbsp;</font></p></td> 
</tr></table>     
    </div>
    </div>
<%@include file="footer.jsp"  %>
</body>
</html>