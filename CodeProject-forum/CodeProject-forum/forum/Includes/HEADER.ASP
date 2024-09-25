<%
' ###########################################################################
' #
' # file:
' # 	header.asp
' #
' # description:
' # 	This file is placed to the beginning of every file in the forum script
' #     set.
' #
' # version:
' # 	2000-04-26 C Maunder   created file
' #
' # copyright:
' #		Written by Uwe Keim <keim@zeta-software.de>
' #		Adapted by Chris Maunder <cmaunder@mail.com>
' #		Copyright (c) 1998-2000. All Rights Reserved.
' # 
' #     Check the Code Project (http://www.codeproject.com) for the latest.
' # 
' #		These scripts may be used in any way you desire PROVIDING the 
' #		"powered by CodeProject" logo remains in the top left corner of the
' #		front index page. This file may be redistributed unmodified by any 
' #		means PROVIDING it is not sold for profit without the authors written 
' #		consent, and providing that this notice and the authors' name and all
' #		copyright notices remains intact. 
' # 
' #		An email letting us know how you are using it would be nice as well. 
' # 
' #		This file is provided "as is" with no expressed or implied warranty.
' #		The author accepts no liability for any damage/loss of business that
' #		this product may cause.
' # 
' ###########################################################################

%>
<!--#include file="../../common/headerscripts.asp"-->
<!doctype html public "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<title>Message Boards - by The Code Project (www.codeproject.com)</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<meta HTTP-EQUIV="Reply-to" CONTENT="mailto:webmaster@codeproject.com">
<link rel="stylesheet" href="/styles/global.css">
<link rel="stylesheet" type=text/css href="forum.css">
</head>

<body text=black bgColor=white aLink=red link=blue vLink=navy>

<!-- Header-->
<table bgColor=#ff9900 border=0 cellPadding=1 cellSpacing=0 width="100%">
<tr><td width="100%">
<table bgColor=#ff9900 border=0 cellPadding=0 cellSpacing=0 width="100%">

<!-- Logo and advertisement -->
<tr>
<td><a href="<%=SITE_URL%>">
<img border=0 width=120 height=60 src="<%=VP_SCRIPT_IMAGES&SITE_LOGO%>" alt="<%=SITE_NAME%>"></a>
</tr>

<!-- Article Title and Author -->
<tr><td bgcolor=#ff9900>
	<table cellpadding=3 width=100% border=0 bgcolor=#FBEDBB><tr><td width=80% valign=top>
	
	<table width=100% border=0><tr><td nowrap>
	<font size=1 style="font-size:8pt">
	<a href='<%=SITE_URL%>'><%=SITE_NAME%></a> &gt;&gt; 
	<a href='<%=VP_FORUM%>'>Forums home page</a>
	</font>
	</td></tr></table>
		
	<table width=100% border=0>
	<tr><td>&nbsp;</td></tr>
	<tr><td valign=top>
	<font size="4" face="Verdana"><b><%=strTitle%></b></font><br>
	<font size="2" face="Verdana"><%=strDesc%></font>
	</td>
<%
	' This is a little dodgy - but hey...
	if forum_id<>"" and Right(Request.ServerVariables("URL"), 9) = "index.asp" then 
%>
	<td align=right valign=bottom>
	<form action="<%=fh.getUriDoFilterByKeywords%>" method="post" id=form1 name=form1>
	<table border="0"><tr>
	<td><input type="text" name="keywords" size="30" value="<%=fh.getKeywordsFilter%>" style="font-size:70%"></td>
	<td><input type="submit" value="Search" name="B1" class=FormButton></td>
	</tr></table>
	</form>	
	</td>
<% End If %>
	
	</tr></table>
	
	<p><font size=2 style="font-size=8pt;"><%
	' Display list of forums
	
	if forum_id<>"" then
			
		dim rsForums
		set rsForums = fh.getForumsRs
		
		while not rsForums.Eof

			' don't link the current forum.
			if CStr(rsForums("ID"))=CStr(forum_id) then			
				%><b title="<%=rsForums("Description")%>"><%=rsForums("Name")%></b> <%
			' link the not-current forum.
			else
				%><b><a href="<%=VP_FORUM%>index.asp?forumid=<%=rsForums("ID")%>" class="forum_link" title="<%=rsForums("Description")%>"><%=rsForums("Name")%></a></b><%
			end if

			rsForums.MoveNext

			' separator between a forum name.
			if not rsForums.Eof then 
				%> | <%
			end if
		wend
	
		rsForums.close
		set rsForums = nothing
				
	End If	
	%></font></p>

	</td></tr></table>
</td></tr>

</table>
</td></tr>
</table>