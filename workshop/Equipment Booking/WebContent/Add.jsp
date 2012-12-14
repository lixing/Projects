<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="java.util.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html><%String dep=request.getParameter("dep"); 
String ref = "Manager_first_page.jsp?dep="+dep;%>
<head>
<meta>
<link href="./structure/css.css" rel="stylesheet" type="text/css" />
<title>Add new Equipment</title>
</head>

<script language="javascript">
var array0 = new Array("SELECT CATEGORY","CTV","IJ","MPRO","ITSC","IJ Photography");        
var array1= new Array("SELECT TYPE");
var arrayCTV= new Array("SELECT TYPE","Tripod Digital","Microphone-Cordless","Stabiliser Jacket","Camera-Video Digital","Camera Flash","Camera-Still Digital","Camera-Still Film","Microphone","Camera Lens","Video Switcher","Light Meter","Microphone Boom","Microphone Cable","Reflector","Stabiliser","P2 Memory Card","Boom Stand","Monitor","Camera Mounting Kit","Tripod Dolly","Windshield");  
 var arrayIJ= new Array("SELECT TYPE","Tripod Digital","Camera-Video Digital","MP3 Recorder","Microphone Cable","Microphone","Camera-Still Digital","Camera Flash","Tripod Still","Off-Camera Shoe Cord","Camera Lens","Canon Battery","CF Card","PISEN Battery");    
var arrayIJP= new Array("SELECT TYPE","Light Shed","Soft Box Lighting Kit","Sand Bag","Background Shade");
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

function   KeyPressNum(strValue)   
{           
	  var   str   =new   String(strValue);  
	  if   ((window.event.keyCode<47||window.event.keyCode>57))   
	  {window.event.returnValue=false;}   
	  else   
	  {window.event.returnValue=true;}   
	  }
	  
 function checkInput(){
	 var equipmentname=document.addequipment1.equipmentname.value;
	 var amount=document.addequipment1.Amount.value;
	 var description=document.addequipment1.Description.value;

	 	if (equipmentname==""){
	 		alert("Name must not Null !");
	 		document.addequipment1.equipmentname.focus();
	 		return false;
	 	}else if (amount==""){
	 		alert("amount must not Null !");
	 		document.addequipment1.amount.focus();
	 		return false;
	 	}else if (description==""){
	 		alert("description code must not Null !");
	 		document.addequipment1.description.focus();
	 		return false;
	 	}
	 	else 
	 		return true;
	 }

</script>
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
<form name="addequipment1" action="ConnectJSP"> 
<table align="center" width="806" height="35" border="0"  bgcolor="#52D0EB" style="border-collapse:collapse;">
<tr>
    <td width="600" align="center"><font size="5px"><strong><font color=white >You can upload the equipment information as excel file</font>
    </strong></font></td></tr>
    <tr>
   
</table>

<table align="center" width="806" height="35" border="0"  style="border-collapse:collapse;">
<tr>
 <td width="800" align="center"><font size="3px"><strong><font  >Excel Format Requirement: 5 columns, the order from left to right column should be "category", "type", "equipment name", "functionality", "total amount"</font>
    </strong></font></td></tr>
</table>
<center>
      <input type="hidden" name="RadioGroup1"  id="RadioGroup1" value="excel" /><br><br>
 <input type="hidden" name="dep" id="dep" value=<%= dep %>>
    <input type ="file" name="file1" id="file1" />
    <input type="submit" name="submit" id="submit" value="submit" /> <br/> 
    </center>
  </form> 
 <form action="ConnectJSP">
<table align="center" width="806" height="35" border="0"  bgcolor="#52D0EB" style="border-collapse:collapse;">
<tr>
    <td width="600" align="center" ><font size="5px"><strong><font color=white >Now enter the detailed Equipment information here</font>
    </strong></font></td>
</table>
<p>
  <label></label></p>
<table width="343" height="112" border="0" align="center">
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1"><font color="#0033FF" size="+1"><strong>Equipment Name:</strong></font></span></div></th>
    <td><input type="text" name="equipmentname"  ></td>
  </tr>
    <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1"><font color="#0033FF" size="+1"><strong>Equipment Category:</strong></font></span></div></th>
       <td><select id="select1" name="category" onchange="checkSelect(this);">
       <option value="SELECT CATEGORY" selected="selected" >SELECT CATEGORY</option>
    <option value="<%=dep %>" ><%=dep %></option>

</select></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1"><font color="#0033FF" size="+1"><strong>Equipment Type:</strong></font></span></div></th>
    <td><select id="select2" name="type"><option value="SELECT TYPE" >SELECT TYPE</option>
</select></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1"><font color="#0033FF" size="+1"><strong>Amount:</strong></font></span></div></th>
    <td><input type="text" name="Amount" onkeypress="return KeyPressNum();" ></td>
  </tr>
  <tr>
    <th class="style2" scope="row"><div align="center"><span class="style1"><font color="#0033FF" size="+1"><strong>Description:</strong></font></span></div></th>
    <td><input type="text" name="Description"  ></td>   
  </tr>
</table>
 
<p>&nbsp;</p>
  <div align="center">
    <p><input type="submit" name="submit" id="submit" value="SUBMIT"style="width:80px; height:30px; font-size:15px;" /> <input type="button" name="Back" id="Back" value="BACK" onclick="javascript:window.location='<%=ref%>'" style="width:80px; height:30px; font-size:15px;"/> </p>
   
 </div>
  <input type="hidden" name="RadioGroup1"  id="RadioGroup1" value="addequipment" />
 <input type="hidden" name="dep" id="dep" value=<%= dep %>>
 </form> 
 
</body>
</html>