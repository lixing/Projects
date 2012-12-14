<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%String id =request.getParameter("id");
String ref="First_Page.jsp?id="+id;%>
<html>
<head>
<title>Booking</title>

<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
<meta http-equiv="description" content="this is my page">
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<!--<link rel="stylesheet" type="text/css" href="./styles.css">-->
<script type="text/javascript">
    var array0 = new Array("SELECT CATEGORY","CTV","IJ","MPRO","ITSC","IJ Photography");        
    var array1= new Array("SELECT TYPE");
    var arrayCTV= new Array("SELECT TYPE","Tripod_Digital","Microphone-Cordless","Stabiliser_Jacket","Camera-Video_Digital","Camera_Flash","Camera-Still_Digital","Camera-Still_Film","Microphone","Camera_Lens","Video_Switcher","Light_Meter","Microphone_Boom","Microphone_Cable","Reflector","Stabiliser","P2_Memory_Card","Boom_Stand","Monitor","Camera_Mounting_Kit","Tripod_Dolly","Windshield");  
     var arrayIJ= new Array("SELECT TYPE","Tripod_Digital","Camera-Video_Digital","MP3_Recorder","Microphone_Cable","Microphone","Camera-Still_Digital","Camera_Flash","Tripod_Still","Off-Camera_Shoe_Cord","Camera_Lens","Canon_Battery","CF_Card","PISEN_Battery");    
    var arrayIJP= new Array("SELECT TYPE","Light_Shed","Soft_Box_Lighting_Kit","Sand_Bag","Background_Shade");
    var arrayM= new Array("SELECT TYPE");
    var arrayI= new Array("SELECT TYPE");
    function checkSelect(select){    
        if (select.value == array0[0]){
        var select2= document.getElementById('select2');
            for(var i=0; i<array1.length; i++){    
            var option = new Option(array1[i]);
            select2.options[i] = option ;
            }
        }
        else if (select.value == array0[1]){
        var select2= document.getElementById('select2');
            for(var i=0; i<arrayCTV.length; i++){    
            var option = new Option(arrayCTV[i]);
            select2.options[i] = option ;
            }
        }
       else if (select.value == array0[2]){
        var select2= document.getElementById('select2');
            for(var i=0; i<arrayIJ.length; i++){    
            var option = new Option(arrayIJ[i]);
            select2.options[i] = option ;
            }
        }
      else if (select.value == array0[3]){
        var select2= document.getElementById('select2');
            for(var i=0; i<arrayM.length; i++){    
            var option = new Option(arrayM[i]);
            select2.options[i] = option ;
            }
        }
      else if (select.value == array0[4]){
        var select2= document.getElementById('select2');
            for(var i=0; i<arrayI.length; i++){    
            var option = new Option(arrayI[i]);
            select2.options[i] = option ;
            }
        }
      else if (select.value == array0[5]){
        var select2= document.getElementById('select2');
            for(var i=0; i<arrayIJP.length; i++){    
            var option = new Option(arrayIJP[i]);
            select2.options[i] = option ;
            }
        }
    }
    
</script>
<script language=javascript>
var DS_x,DS_y;

function dateSelector() //构造dateSelector对象，用来实现一个日历形式的日期输入框。
{
var myDate=new Date();
this.year=myDate.getFullYear(); //定义year属性，年份，默认值为当前系统年份。
this.month=myDate.getMonth()+1; //定义month属性，月份，默认值为当前系统月份。
this.date=myDate.getDate(); //定义date属性，日，默认值为当前系统的日�
this.inputName=''; //定义inputName属性，即输入框的name，默认值为空。注意：在同一页中出现多个日期输入框，不能有重复的name！
this.display=display; //定义display方法，用来显示日期输入框�

}

function display() //定义dateSelector的display方法，它将实现一个日历形式的日期选择框。
{
var week=new Array('Sun','Mon','Tue','Wed','Thu','Fri','Sat');

document.write("<style type=text/css>");
document.write(" .ds_font td,span { font: normal 12px 宋体; color: #000000; }");
document.write(" .ds_border { border: 1px solid #000000; cursor: hand; background-color: #DDDDDD }");
document.write(" .ds_border2 { border: 1px solid #000000; cursor: hand; background-color: #DDDDDD }");
document.write("</style>");

var M=new String(this.month);
var d=new String(this.date);

if(M.length==1&&d.length==1){
document.write("<input style='text-align:center;' id='DS_"+this.inputName+"' name='"+this.inputName+"' value='"+this.year+"-0"+this.month+"-0"+this.date+"' title=Modify ondblclick='this.readOnly=false;this.focus()' onblur='this.readOnly=true' readonly>");}
else if(M.length==1&&d.length==2){
document.write("<input style='text-align:center;' id='DS_"+this.inputName+"' name='"+this.inputName+"' value='"+this.year+"-0"+this.month+"-"+this.date+"' title=Modify ondblclick='this.readOnly=false;this.focus()' onblur='this.readOnly=true' readonly>");}
else if(M.length==2&&d.length==1){
document.write("<input style='text-align:center;' id='DS_"+this.inputName+"' name='"+this.inputName+"' value='"+this.year+"-"+this.month+"-0"+this.date+"' title=Modify ondblclick='this.readOnly=false;this.focus()' onblur='this.readOnly=true' readonly>");}
else if(M.length==2&&d.length==2){
document.write("<input style='text-align:center;' id='DS_"+this.inputName+"' name='"+this.inputName+"' value='"+this.year+"-"+this.month+"-"+this.date+"' title=Modify ondblclick='this.readOnly=false;this.focus()' onblur='this.readOnly=true' readonly>");}

document.write("<button style='width:120px;height:18px;font-size:12px;margin:1px;border:1px solid #A4B3C8;background-color:#DFE7EF;' type=button onclick=this.nextSibling.style.display='block' onfocus=this.blur()>Choose Date</button>");

document.write("<div style='position:absolute;display:none;text-align:center;width:0px;height:0px;overflow:visible' onselectstart='return false;'>");
document.write(" <div style='position:absolute;left:-60px;top:20px;width:142px;height:165px;background-color:#F6F6F6;border:1px solid #245B7D;' class=ds_font>");
document.write(" <table cellpadding=0 cellspacing=1 width=140 height=20 bgcolor=#CEDAE7 onmousedown='DS_x=event.x-parentNode.style.pixelLeft;DS_y=event.y-parentNode.style.pixelTop;setCapture();' onmouseup='releaseCapture();' onmousemove='dsMove(this.parentNode)' style='cursor:move;'>");
document.write(" <tr align=center>");
document.write(" <td width=12% onmouseover=this.className='ds_border' onmouseout=this.className='' onclick=subYear(this) title='Last Year'><<</td>");
document.write(" <td width=12% onmouseover=this.className='ds_border' onmouseout=this.className='' onclick=subMonth(this) title='Last Month'><</td>");
document.write(" <td width=52%><b>"+this.year+"</b><b>/</b><b>"+this.month+"</b></td>");
document.write(" <td width=12% onmouseover=this.className='ds_border' onmouseout=this.className='' onclick=addMonth(this) title='Next Month'>></td>");
document.write(" <td width=12% onmouseover=this.className='ds_border' onmouseout=this.className='' onclick=addYear(this) title='Next Year'>>></td>");
document.write(" </tr>");
document.write(" </table>");

document.write(" <table cellpadding=0 cellspacing=0 width=140 height=20 onmousedown='DS_x=event.x-parentNode.style.pixelLeft;DS_y=event.y-parentNode.style.pixelTop;setCapture();' onmouseup='releaseCapture();' onmousemove='dsMove(this.parentNode)' style='cursor:move;'>");
document.write(" <tr align=center>");
for(i=0;i<7;i++)
  document.write(" <td>"+week[i]+"</td>");
document.write(" </tr>");
document.write(" </table>");

document.write(" <table cellpadding=0 cellspacing=2 width=140 bgcolor=#EEEEEE>");
for(i=0;i<6;i++)
{
document.write(" <tr align=center>");
  for(j=0;j<7;j++)
document.write(" <td width=10% height=16 onmouseover=if(this.innerText!=''&&this.className!='ds_border2')this.className='ds_border' onmouseout=if(this.className!='ds_border2')this.className='' onclick=getValue(this,document.all('DS_"+this.inputName+"'))></td>");
document.write(" </tr>");
}
document.write(" </table>");

document.write(" <span style=cursor:hand onclick=this.parentNode.parentNode.style.display='none'>CLOSE</span>");
document.write(" </div>");
document.write("</div>");

dateShow(document.all("DS_"+this.inputName).nextSibling.nextSibling.childNodes[0].childNodes[2],this.year,this.month)
}

function subYear(obj) //减小年份
{
var myObj=obj.parentNode.parentNode.parentNode.cells[2].childNodes;
myObj[0].innerHTML=eval(myObj[0].innerHTML)-1;
dateShow(obj.parentNode.parentNode.parentNode.nextSibling.nextSibling,eval(myObj[0].innerHTML),eval(myObj[2].innerHTML))
}

function addYear(obj) //增加年份
{
var myObj=obj.parentNode.parentNode.parentNode.cells[2].childNodes;
myObj[0].innerHTML=eval(myObj[0].innerHTML)+1;
dateShow(obj.parentNode.parentNode.parentNode.nextSibling.nextSibling,eval(myObj[0].innerHTML),eval(myObj[2].innerHTML))
}

function subMonth(obj) //减小月份
{
var myObj=obj.parentNode.parentNode.parentNode.cells[2].childNodes;
var month=eval(myObj[2].innerHTML)-1;
if(month==0)
{
month=12;
subYear(obj);
}
myObj[2].innerHTML=month;
dateShow(obj.parentNode.parentNode.parentNode.nextSibling.nextSibling,eval(myObj[0].innerHTML),eval(myObj[2].innerHTML))
}

function addMonth(obj) //增加月份
{
var myObj=obj.parentNode.parentNode.parentNode.cells[2].childNodes;
var month=eval(myObj[2].innerHTML)+1;
if(month==13)
{
month=1;
addYear(obj);
}
myObj[2].innerHTML=month;
dateShow(obj.parentNode.parentNode.parentNode.nextSibling.nextSibling,eval(myObj[0].innerHTML),eval(myObj[2].innerHTML))
}

function dateShow(obj,year,month) //显示各月份的日
{
var myDate=new Date(year,month-1,1);
var today=new Date();
var day=myDate.getDay();
var selectDate=obj.parentNode.parentNode.previousSibling.previousSibling.value.split('-');
var length;
switch(month)
{
case 1:
case 3:
case 5:
case 7:
case 8:
case 10:
case 12:
length=31;
break;
case 4:
case 6:
case 9:
case 11:
length=30;
break;
case 2:
if((year%4==0)&&(year%100!=0)||(year%400==0))
length=29;
else
length=28;
}
for(i=0;i<obj.cells.length;i++)
{
obj.cells[i].innerHTML='';
obj.cells[i].style.color='';
obj.cells[i].className='';
}
for(i=0;i<length;i++)
{
obj.cells[i+day].innerHTML=(i+1);
if(year==today.getFullYear()&&(month-1)==today.getMonth()&&(i+1)==today.getDate())
obj.cells[i+day].style.color='red';
if(year==eval(selectDate[0])&&month==eval(selectDate[1])&&(i+1)==eval(selectDate[2]))
obj.cells[i+day].className='ds_border2';
}
}

function getValue(obj,inputObj) //把选择的日期传给输入框
{
var myObj=inputObj.nextSibling.nextSibling.childNodes[0].childNodes[0].cells[2].childNodes;
if(obj.innerHTML)
if(obj.innerHTML.length==1&&myObj[2].innerHTML.length==1)
inputObj.value=myObj[0].innerHTML+"-0"+myObj[2].innerHTML+"-0"+obj.innerHTML;
  else if(obj.innerHTML.length==1&&myObj[2].innerHTML.length==2)
inputObj.value=myObj[0].innerHTML+"-"+myObj[2].innerHTML+"-0"+obj.innerHTML;
  else if(obj.innerHTML.length==2&&myObj[2].innerHTML.length==1)
inputObj.value=myObj[0].innerHTML+"-0"+myObj[2].innerHTML+"-"+obj.innerHTML;
  else if(obj.innerHTML.length==2&&myObj[2].innerHTML.length==2)
inputObj.value=myObj[0].innerHTML+"-"+myObj[2].innerHTML+"-"+obj.innerHTML;
inputObj.nextSibling.nextSibling.style.display='none';
for(i=0;i<obj.parentNode.parentNode.parentNode.cells.length;i++)
obj.parentNode.parentNode.parentNode.cells[i].className='';
obj.className='ds_border2'
}

function dsMove(obj) 
{
if(event.button==1)
{
var X=obj.clientLeft;
var Y=obj.clientTop;
obj.style.pixelLeft=X+(event.x-DS_x);
obj.style.pixelTop=Y+(event.y-DS_y);
}
}
</script>

</head>
<body>
<center>
<form name="form">
<table  background="img/bg.png" style="background-repeat:no-repeat;" width="1200;">
  <tr>
    <td width="850">&nbsp;</td>
    <td width="520"><p>&nbsp;</p>
    <p>&nbsp;</p></td>
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
<form action="ConnectJSP">

<table border="0"  cellpadding="0" cellspacing="0">
      <tr>
        <td width="202">&nbsp;</td>
        <td width="620"><span id="p1"><center><font color="#0099FF" size="+3"> <strong> Book informaion search</strong></font></center></span></td>
        <td width="202" height="175"></td>
      </tr>
      </table>
<table>
<tr>
<table border="0">
<tr>
<td>
<p><font color="#0033FF" size="+2">
Equipment:&nbsp;&nbsp;&nbsp;&nbsp;</font></p>
</td>
<td>
<select id="select1" name="category" onchange="checkSelect(this);">
    <option value="SELECT CATEGORY" selected="selected" >SELECT CATEGORY</option>
    <option value="CTV" >CTV</option>
    <option value="IJ" >IJ</option>
    <option value="MPRO" >MPRO</option>
   <option value="ITSC" >ITSC</option>
    <option value="IJ Photography" >IJ Photography</option>
</select>
</td>
<td>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<select id="select2" name="type"><option value="SELECT TYPE" >SELECT TYPE</option>
</select>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#0033FF" size="+2">Input yourself:</font><input type="text" name="own" id="own" value=""><br/></td></tr>
</table>
</tr>
<tr>
<table>
<tr height="100">
<td>
<font color="#0033FF" size="+2"><strong>FROM:</strong></font>
<script language=javascript>
var myDate=new dateSelector();
//myDate.year--;
myDate.inputName='start_date'; //注意这里设置输入框的name，同一页中日期输入框，不能出现重复的name。
myDate.display();
</script></td>
<td>
<font color="#0033FF" size="+2"><strong>TO:</strong></font> 
<script language=javascript>
//myDate.year++;
myDate.inputName='end_date'; //注意这里设置输入框的name，同一页中的日期输入框，不能出现重复的name。
myDate.display();
</script><br/></td>
</tr>
</table>
</tr>
</table><br/>
<input type="hidden" name="id" id="id" value=<%= id %>>
<input type="hidden" name="today" id="today" value="">
<input type="submit" name="OK" id="OK" value="OK" style="width:80px;height:30px;font-size:15px;"/>&nbsp;&nbsp;&nbsp;<input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> 
</form>
</center>
</body>
</html>