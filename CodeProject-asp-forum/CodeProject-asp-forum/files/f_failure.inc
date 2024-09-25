<%' failure.asp 
%>


<%
dim err_txt
err_txt = Request("err_txt")

if err_txt="" then err_txt = "unbekannt"
%>

		<p><%=FONT2%><b>An Error occured.</b></font></p>
		
	
		<p><%=FONT1%>Error:</font></p>
		<blockquote>
			<p><%=FONT1%><b><%=err_txt%></b></font></p>
		</blockquote>

		<hr noshade size="1" color="#C0C0C0">

		<p><%=FONT1%>Click <a href="javascript:history.back()"><b>here</b></a> to go back to the previous page to try again.</font></p>