<% option explicit 

' ###########################################################################
' #
' # file:
' # 	index.asp
' #
' # description:
' # 	start file for the forum.
' #
' # version:
' # 	2000-02-06 Uwe Keim   file created.
' #
' # copyright:
' #		Written by Uwe Keim <keim@zeta-software.de>
' #		Adapted by Chris Maunder <cmaunder@mail.com>
' #		Copyright (c) 1998-2000. All Rights Reserved.
' # 
' # 	Check the Code Project (http://www.codeproject.com) for the latest.
' # 
' #		These scripts may be used in any way you desire PROVIDING the 
' #		'"powered by CodeProject" logo remains in the top left corner of the
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
<!--#include file="../common/scripts.asp"-->
<!--#include file="includes/locafx.inc"-->
<%

Dim strTitle, strDesc, strUpdate, forum_id, forum_name
strTitle   = "Welcome to the Code Project discussion boards"
strDesc    = "Please choose a discussion forum from the list below"
strUpdate  = "15 Jun 2000"
forum_id   = Request.QueryString("forumid")
forum_name = Request.QueryString("forum")


' ///////////////////////////////////////////////////////////////////
' // prepare the forum id.
	
' select the forum that is specified in the parameters for that page.
' the caller may have either specified a forum id or the short-name of a forum.
	
' translate forum name to forum id (if no id present).
if forum_id="" and forum_name<>"" then
	forum_id = fh.getForumId( forum_name )
end if

if forum_id <> "" Then
 	fh.getForumDetails forum_id, strTitle, strDesc 
End If

%><!-- #include file="includes/header.asp" --><%	

' ///////////////////////////////////////////////////////////////////
' // Get the type of view (expanded/collapsed etc)

Dim Expanded
Expanded = Request.QueryString("exp")
if Expanded = "" Then 
	Expanded = Session("expand")
	if Expanded = "" Then 
		Expanded = Request.Cookies("expand")
		if Expanded <> "" Then Session("expand") = Expanded
	End If
End If
if Expanded <> "" Then fh.setExpandedView(Expanded)

' ///////////////////////////////////////////////////////////////////
' // Get the LastVisit - it's set in LastVisit.asp

Dim LastVisit
LastVisit = Session("LastVisit")

' Look for a "DateFilter" value in the Session object, and if no value
' there, look for it in a cookie. If we get a value then set the
' forum objects filter type as that value. This "DateFilter"
' value will be stored in the Session object and cookies collection
' when the user hits the "Refresh" button. Until then it will remain
' remain at the default value
Dim DateFilter
DateFilter = Request.QueryString("df")
if DateFilter = "" Then 
	DateFilter = Session("DateFilter")
	if DateFilter = "" Then 
		DateFilter = Request.Cookies("DateFilter")
		if DateFilter <> "" Then Session("DateFilter") = DateFilter
	End If
End If
if DateFilter <> "" Then fh.setDateFilterStart DateFilter, LastVisit

' ///////////////////////////////////////////////////////////////////
' // prepare row count.

if forum_id<>"" then
		
	' messages per page
	Dim MessagesPerPage
	MessagesPerPage = Request.QueryString("app")
	if MessagesPerPage = "" Then 
		MessagesPerPage = Session("MPP")
		if MessagesPerPage = "" Then 
			MessagesPerPage = Request.Cookies("MPP")
			if MessagesPerPage = "" Then MessagesPerPage = 10
			Session("MPP") = MessagesPerPage
		End If
	End If
	if MessagesPerPage <> "" Then fh.setArticlesPerPage(MessagesPerPage)
		
	if fh.getFirstRow() = "" Then fh.setFirstRow("1")
	
	Dim StartRow, EndRow, RowCount, CommentCount
	Dim PrevRow, NextRow, LastRow
	CommentCount = CInt(fh.getSelectedArticleRsCount(forum_id, fh.getDateFilterStart, "", fh.getKeywordsFilter))	' Number of comments
	RowCount = fh.getArticlesPerPage()					' Number to show per page

	'Response.Write "<br>RowCount: " & RowCount
	'Response.Write "<br>Start date: " & fh.getDateFilterStart

	if RowCount = "All" Then							' Special case
		StartRow = 1
		RowCount = CommentCount
	Else
		StartRow = CInt(fh.getFirstRow())				' First row on page to start showing
		RowCount = CInt(RowCount)
	End If
	if StartRow > CommentCount Then StartRow = 1 
	
	EndRow = StartRow + RowCount-1						' Last row on page to show
	if EndRow > CommentCount Then EndRow = CommentCount

	PrevRow = StartRow - RowCount						' Start of previous page's rows
	if PrevRow < 1 Then PrevRow = 1

	NextRow = EndRow + 1								' Start of next pages rows. May be > CommentCount		

	if RowCount <> 0 Then
		Dim remainder
		remainder = CommentCount mod RowCount
	    if remainder = 0 Then
		    LastRow = CommentCount - RowCount + 1
	    else
		    LastRow = CommentCount - remainder + 1
	    End If
	End if

	if LastRow < 1 Then LastRow = 1						' Start of last pages rows 

	' ///////////////////////////////////////////////////////////////////
	' // Form for selecting date, messages per page etc.

	' helper function for writing the date option-comobobox values
	' and automatically selecting the current.
	sub writeDateOption(str, text, can_empty)
		if ( fh.getDateFilterStartType=str or _
			             ((fh.getDateFilterStartType="") and can_empty) ) then
			Response.Write "<option selected value=""" &str& """>" &text& "</option>" &vbCrLf
		else
			Response.Write "<option value=""" &str& """>" &text& "</option>" &vbCrLf
		end if
	end sub

	sub writeAPPOption( str, can_empty )
		if (fh.getArticlesPerPage=str) or ((fh.getArticlesPerPage="") and can_empty) then
			Response.Write "<option selected value=""" &str& """>" &str& "</option>" &vbCrLf
		else
			Response.Write "<option value=""" &str& """>" &str& "</option>" &vbCrLf
		end if
	end sub

	sub writeExpandOption( value, text, can_empty )
		if (fh.getExpandedView=value) or ((fh.getExpandedView="") and can_empty) then
			Response.Write "<option selected value=""" &value& """>" &text& "</option>" &vbCrLf
		else
			Response.Write "<option value=""" &value& """>" &text& "</option>" &vbCrLf
		end if
	end sub
%>
<br><br>
<table border=0 bgcolor="#FF9900" width=100% cellspacing=1>
<form action="<%=fh.getUriDoFilterMessages%>" method="post">
<tr><td>

<table width=100% border=0><tr>
<td width=100%><b><font color=white>&nbsp;</font></b></td>
<td nowrap valign=top>
	<font size="1" style="font-size:8pt" face="Verdana">Messages since </font>
	<select size="1" name="datefilter" style="font-size:8pt">
		<%
		if LastVisit<>"" Then
			writeDateOption datefilterLastVisit, "Since "&DateTimeString(LastVisit,True), false
		End if
		writeDateOption datefilterLastDay,  "Last Day"     , false
		writeDateOption datefilterLastWeek, "Last Week"    , false
		writeDateOption datefilterLastMonth,"Last Month"   , false
		writeDateOption datefilterLastHalf, "Last 6 Months", false
		writeDateOption datefilterLastYear, "Last Year"    , false
		writeDateOption datefilterAll,      "All"          , true
		%>
	</select>&nbsp;&nbsp;
</td>
<%
' ////////////////////////////////////////////////////////////
' Expand/Collapse
%>
<td nowrap valign=top>
	<font size="1" style="font-size:8pt" face="Verdana">View </font>
	<select size="1" name="expand" style="font-size:8pt"><%
        writeExpandOption expandNone, "Normal", True 
        'writeExpandOption expandCollapse, "Collapsed", False	- Not yet implemented
        writeExpandOption expandPreview, "Preview", False 
	%></select>&nbsp;&nbsp;
</td>
<%
' ////////////////////////////////////////////////////////////
%>
<td nowrap valign=top>
	<font size="1" style="font-size:8pt" face="Verdana">Per page </font>
	<select size="1" name="perpage" style="font-size:8pt">
		<%writeAPPOption  "5", false%>
		<%writeAPPOption  "10", false%>
		<%writeAPPOption  "25", true%>
		<%writeAPPOption  "50", false%>
		<%writeAPPOption "100", false%>
		<%'writeAPPOption "All", true%>
	</select>
</td>
<td valign=top><input type="submit" value="Refresh" name="submit" class=FormButton></td>
</tr></table>

</td></tr></form>

<tr bgcolor=#FBEDBB><td>
<% 
' ///////////////////////////////////////////////////////////////////
' // link for new message, message count, then navigation links

%><table border=0 width=100% bgcolor=#FBEDBB><tr>
<td><font size="1" face="Verdana" style="font-size:8pt"><a href="<%=fh.getUriUserNew(forum_id)%>" target="_top" title="<%=IDS_FORUM_NEW_TITLE%>"><%=IDS_FORUM_LIST_NEW%></a></font></td>
<% if CommentCount<>"0" Then %>
<td><font size="1" face="Verdana" style="font-size:8pt">
Messages <%=StartRow%> to <%=EndRow%> of <%=CommentCount%> (Total: <%=fh.getCommentCount(forum_id)%>)
</td>
<% Else %>
<td><font size="1" face="Verdana" style="font-size:8pt">Total Messages for this article: <%=fh.getCommentCount(forum_id)%></td>
<% end if %>

<% if CommentCount<>"0" Then %>
<td align=right><font face="verdana" size="1" style="font-size:8pt">
<% if StartRow <> "1" Then %>
<a href="<%=fh.getUriRow(0, "1")%>">First</a> |
<% Else %>
First |
<% End If %>
<% if StartRow <> "1" Then %>
<a href="<%=fh.getUriRow(0, PrevRow)%>">Prev</a> |
<% Else %>
Prev |
<% End If %>
<% if StartRow + RowCount <= CommentCount Then %>
<a href="<%=fh.getUriRow(0, NextRow)%>">Next</a> |
<% Else %>
Next |
<% End If %>
<% if StartRow + RowCount <= CommentCount Then %>
<a href="<%=fh.getUriRow(0, LastRow)%>">Last</a>
<% Else %>
Last
<% End If %>
</font></td>
<% end if %>
</tr></table>

</td></tr><tr><td bgcolor=white>
<%
' ///////////////////////////////////////////////////////////////////
' // in admin mode, show link to change forum properties

if fh.isInAdminMode then
	%><p><font size="1" face="Verdana">[<a href="<%=fh.getUriAdminModifyForum(forum_id)%>" target="_top"><%=IDS_FORUM_LIST_ADMINFORUM%></a>]</font></p><%
end if

' ///////////////////////////////////////////////////////////////////
' // include the actual article list.
%>
<!--#include file="includes/main.asp"-->
<%
' ///////////////////////////////////////////////////////////////////
' // Navigation links
%>	
</td></tr></table>
<%
else
	set rsForums = fh.getForumsRs
%>

<table border=0 width="100%" cellspacing=7>
<tr valign=bottom><td><b>Forum</b></td><td><b>Description</b></td><td align=right><b>Total</b></td>
<%if LastVisit<>"" Then%>
<td align=right nowrap><b>New<sup>*</sup></b></td>
<% Else %>
<td>&nbsp;</td>
<% End If %>
</tr>
<tr><td colspan=4><hr size=1 width=100% noshade></td></tr>
<%
	rsForums.MoveFirst
	while not rsForums.Eof

		Dim id
		id = rsForums("ID")
		strTitle = rsForums("Name")
		strDesc = rsForums("Description")

		Response.Write "<tr valign=top>"
		Response.Write "<td nowrap><a href='" &myself& "?forumid=" &id& "'>" & strTitle & "</a></td>" & vbCRLF
		Response.Write "<td>" & strDesc & "</td>" & vbCRLF
		Response.Write "<td align=right>" & fh.getCommentCount(id) & "</td>"
		if LastVisit<>"" Then
			Response.Write "<td align=right>" & fh.getNewCommentCount(id, LastVisit) & "</td>"
		Else
			Response.Write "<td align=right>&nbsp;</td>"
		End If
		Response.Write "</tr>" & vbCRLF

		rsForums.MoveNext
	wend
		
	rsForums.close
	set rsForums = nothing

	%><tr><td colspan=4><hr size=1 width=100% noshade><br><% 

	if LastVisit<>"" Then 
		%><sup>*</sup>New messages since <%=DateTimeString(LastVisit, False)%>. Local time is <%=DateTimeString(Now(), False)%></td></tr><% 
	End If 
	
%>
</table>
		
<%end if %>
<!--#include file="includes/cleanup.inc"-->
<!--#include file="includes/footer.asp" -->
