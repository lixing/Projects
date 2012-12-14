<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<%@ include file="database.jsp" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Index</title>
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
<table align="center" width="806" height="35" border="0" cellspacing="0" cellpadding="0" bgcolor="#A60000" bordercolor="#000000" style="border-collapse:collapse;">
<tr bgcolor="#A60000">
    <td width="600" align="center" bgcolor="#A60000"><font size="5px"><strong><font color=white >Welcome to our Bookstore!</font>
    </strong></font></td>
</table>
<table width="480" align = "left">
<tr >
    <td background="images/bg/index_new.jpg" onClick="location.href='newbooks.jsp'"  height="255" > </td>
</tr><tr bgcolor="#A60000" align="center"><td><font color=white><font size="5px">Best Sellers</font></font></td></tr>
<tr><td>
<img src="./images/cover/1q84.jpg " width ="150" height = "200" onClick="location.href='bookinfo.jsp?isbn=9787544247269'" />
<img src="./images/cover/suzumiya.jpg " width ="150" height = "200" onClick="location.href='bookinfo.jsp?isbn=9787532750429'" />
<img src="./images/cover/langkexing.jpg " width ="150" height = "200" onClick="location.href='bookinfo.jsp?isbn=9784097400158'" />
</td></tr>
</table>
<table align="right" width="300" height="495" border="0" cellspacing="0" cellpadding="0" bgcolor="#919191" bordercolor="#000000" style="border-collapse:collapse;">
 <tr><td width="300"  align="right" ><p><!--rolling notice-->
                        <marquee behavior="scroll" direction="up" height="400" 
scrollamount=2 class="stockWarning" onMouseOver=this.stop() 
onMouseOut=this.start()>
                          
  <span class="messageStackSuccess"><font color = #0000FF><font size="3px"><strong>About our bookstore</strong></font></span><font size="2px"><br>Our online store was opened in December 13th,2010, offering novels, light novels and manga at cheap prices with fast delivery.
  We are still working to improve our bookstore better. If you have any problems or advice, please contact and inform us. Wish you a happy shopping journey!
  </font></font><br><br>
  <br><br>
  <span class="messageStackSuccess"><font color = #0000FF><font size="3px"><strong>Books update history</strong></font></span><br>
  <font size="2px">2010-12-17<br>
  The bookstore updated:<br>
  Three books added:<br>灼眼的夏娜   高桥弥七郎<br>
                    Fate/Zero  虚渊玄<br>
                                                     银魂     空知英秋<br><br>
  2010-12-15<br>
  The bookstore updated:<br>
  Two books added:<br>Sherlock Holmes   Sir Arthur Conan Doyle<br>
                                                浪客行   井上雄彦<br><br>
                                                
  2010-12-13<br>
  The bookstore started:<br>
  Five books added:<br>龙珠     鸟山明<br>
                                                   凉宫春日的忧郁    谷川流<br>
                   1988  韩寒<br>
                   Harry Porter  J.K. Rowling <br>
                   1Q84  村上春树<br></font></font>

                          </marquee><!--rolling notice end-->
                      </p></td></tr>
</table>
<table width="403"  >

</table>

<br/><br/>
</div >
</div>
<%@include file="footer.jsp"  %>
</body>
</html>