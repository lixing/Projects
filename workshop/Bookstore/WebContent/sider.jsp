 <script language="javascript">
 function   KeyPressNum(strValue)   
{           
	  var   str   =new   String(strValue);  
	  if   ((window.event.keyCode<47   ||   window.event.keyCode>57)   )   
	  {window.event.returnValue=false;}   
	  else   
	  {window.event.returnValue=true;}   
}


</script>
    <h1>Categories</h1>
        <h2><a href="index.jsp">Home</a></h2>
        <h2><a href="cart.jsp">Shopping Cart</a></h2>
        <h2><a href="contact.jsp">Contact us</a></h2>
        <h2><a href="messageboard.jsp">Message Board</a></h2>
    <h1>Book Type</h1>
        <h2><a href="booktype.jsp?typeno=1">Novels</a></h2>
        <h2><a href="booktype.jsp?typeno=2">Light Novels</a></h2>
        <h2><a href="booktype.jsp?typeno=3">Manga</a></h2>
    <h1>Search</h1>
 <form name="searchorder"  method="post" action="ordercheck.jsp">
 <table width="90" height="35" border="0">
 <tr>
    <td align="center"><input name="findorder" type="text" id="order" size="10" onkeypress="return   KeyPressNum();"></td>
</tr>
    <tr>
<td align="center"><input class="searchbutton" type="submit" value="Search orders"/></td>
 </tr>
 </table>
 </form>
 <form name="searchbook"  method="post" action="search.jsp">
 <table width="90" height="35" border="0">
 <tr>
    <td align="center"><input name="findbook" type="text" id="book" size="10"></td>
</tr>
    <tr>
<td align="center"><input class="searchbutton" type="submit" value="Search books"/></td>
 </tr>
 </table>
 </form>

    