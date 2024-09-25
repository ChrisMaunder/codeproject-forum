<%
' ###########################################################################
' #
' # file:
' # 	main.asp
' #
' # description:
' # 	displays the actual list of articles for a forum.
' #
' # version:
' # 	2000-05-18 C Maunder  Lots changes (cosmetic). Added expansion.
' #                           Modified WriteIndent, introduced constants
' #                           EXPANSION NOT YET COMPLETE
' # 	2000-02-06 Uwe Keim   optimized the WriteIndent() function.
' # 	2000-01-07 Uwe Keim   added forum administration link.
' # 	2000-01-05 Uwe Keim   added resource strings.
' # 	2000-01-01 Uwe Keim   calling getArticleAnchor().
' # 	1999-12-29 Uwe Keim   file created.
' #
' ###########################################################################


const indentBlank    = 0
const indentContent  = 1
const indentSelected = 2

' 'forum_id' must be dimmed and set correctly before
' #including this file.
'
' this file #includes the list for the forum specified by
' 'forum_id'.
'
' if you want to change the design/layout of the forum
' (like e.g. colors, font, columns, etc.), THIS file is
' the correct place.

Dim title_font, content_font
title_font   = "class='messagetitle' size=1 face='Verdana, san serif'"
content_font = "class='messagecontent' size=1 face='Courier New, Courier'"


' ///////////////////////////////////////////////////////////////////////////
' // draw the indent graphics.

' this function draws the indent and the article-image, based on the 
' indent-level and the state of the article.
sub WriteIndent( ind_lvl, state )
	Response.Write "<img border=""0"" height=""1"" width="""&CStr(20*CInt(ind_lvl))&""" src="""&VP_SCRIPT_IMAGES&"ind.gif"">"

	if state=indentSelected then
		Response.Write "<img align=""absmiddle"" src="""&VP_SCRIPT_IMAGES&"news_selected.gif"">"
	elseif state=indentContent then
		Response.Write "<img border=""0"" align=""absmiddle"" src="""&VP_SCRIPT_IMAGES&"news_none.gif"">"
	else
		Response.Write "<img border=""0"" align=""absmiddle"" src="""&VP_SCRIPT_IMAGES&"news_unselected.gif"">"
	end if

	Response.Write "<img border=""0"" width=""2"" height=""2"" align=""absmiddle"" src="""&VP_SCRIPT_IMAGES&"t.gif"">"
end sub
' ///////////////////////////////////////////////////////////////////////////
' begin the table with all articles
%>
<table border="0" cellspacing="0" cellpadding="0" width="100%">
<% 'header %>
<tr>	
    <td width="70%" bgcolor="#FBEDBB"><table border="0" cellspacing="0" cellpadding="2" width="100%"><tr><td><font <%=title_font%>><%=IDS_FORUM_LIST_COLSUBJECT%>&nbsp;</font></td></tr></table></td>
    <td width="20%" bgcolor="#FBEDBB"><table border="0" cellspacing="0" cellpadding="0" width="100%"><tr><td><img src="<%=VP_SCRIPT_IMAGES%>t.gif" border="0" width="1" height="1"></td></tr><tr><td><font <%=title_font%>><%=IDS_FORUM_LIST_COLAUTHOR%>&nbsp;</font></td></tr><tr><td><img src="<%=VP_SCRIPT_IMAGES%>t.gif" border="0" width="1" height="1"></td></tr></table></td>
    <td width="10%" bgcolor="#FBEDBB"><table border="0" cellspacing="0" cellpadding="0" width="100%"><tr><td><img src="<%=VP_SCRIPT_IMAGES%>t.gif" border="0" width="1" height="1"></td></tr><tr><td align=right><font <%=title_font%>><%=IDS_FORUM_LIST_COLDATE%>&nbsp;</font></td></tr><tr><td><img src="<%=VP_SCRIPT_IMAGES%>t.gif" border="0" width="1" height="1"></td></tr></table></td>
</tr>
<% 'distance between header and entries %>
<tr><td colspan="3"><img src="<%=VP_SCRIPT_IMAGES%>t.gif" border="0" width="1" height="2"></td></tr>
<%
	' ---------------------------------------------------------
	' read all articles of this forum into memory.
	fh.readArticles forum_id

	' no entries.
	if fh.endOfList then

		'inform user that there are no entries here %>
		<tr><td colspan="3"><img src="<%=VP_SCRIPT_IMAGES%>t.gif" border="0" width="1" height="9"></td></tr>
		<tr><td align="center" colspan="3"><font <%=title_font%>>-- No entries present --</font></td></tr>
<%
	end if

    dim MessageNumber
    MessageNumber = 1
    
    ' ** TODO - Need to add a function Move() to make this quicker
    ' fh.Move(StartRow)
    ' MessageNumber = StartRow 
    
	' display all articles by iterating the sorted list.
	while not fh.endOfList

      if (MessageNumber >= StartRow and MessageNumber <= EndRow) Then
        
		' ---------------------------------------------------------
		' the recordset of the current article.
		dim article_rs
		set article_rs = fh.getArticleRs( fh.getCurId )

		' store some decision values.
		dim is_root						' whether the current article is a root-article.
		dim is_selected					' whether the current article is selected.
		dim is_new
		dim message_id
		message_id  = article_rs("ID")
		is_root     = (article_rs("ParentID")=0)
		is_selected = (CStr(Request("select"))=CStr(message_id))
		is_new      = (LastVisit<>"" and CDate(LastVisit) <= CDate(article_rs("Date")))

		' design: all root-entries are bold.
		dim bold_in, bold_out
		if is_root then
			bold_in  = "<b>"
			bold_out = "</b>"
		else
			bold_in  = ""
			bold_out = ""
		end if

		' design: add "new" tag if the message is new
		dim image_tag
		if is_new Then
			image_tag = "<img src='" & VP_SCRIPT_IMAGES & "New.gif' height='12'>"
		else
			image_tag = ""
		end if
		
		dim IndentType
		if is_selected Then
			IndentType = indentSelected
		Else
			IndentType = indentBlank
		End If

		' design: a selected article gets other colors than an unselected article.
		dim select_color
		dim text_color
		dim content_color

		if is_selected then
			text_color    = "color  =""" &COLOR_SELECTED_FG& """"
			select_color  = "bgcolor=""" &COLOR_SELECTED_BG& """"
			content_color = "bgcolor=""" &COLOR_CONTENT_BG & """"
		else
			text_color    = ""
			if Expanded = expandPreview then
				select_color  = "bgcolor=""" &COLOR_EXPANDNONSELECTED_CONTENT_BG& """"
			else
				select_color  = "bgcolor=""" &COLOR_NONSELECTED_BG& """"
			end if
			content_color = "bgcolor=""" &COLOR_NONSELECTED_CONTENT_BG& """"
		end if

		' design: root articles shows the # of children (direct and
		'         indirect childs) as a number after the subject.
		dim cnt_txt
		'if (fh.getCurArticleCount>1) then
		'	cnt_txt = " <font " & title_font & " color=""#808080"">(" &fh.getCurArticleCount-1& ")</font>"
		'else
			cnt_txt = ""
		'end if
		
		' if the forum is in admin mode, there are serveral
		' links that allows you to edit and remove articles.
		dim admin_links
		if fh.isInAdminMode then
			admin_links = ""
			admin_links = admin_links & "<font " & title_font & text_color& "><b><em>"
			admin_links = admin_links & "&nbsp;&nbsp;&nbsp;&nbsp; "
			admin_links = admin_links & "<a title="""&IDS_FORUM_LIST_ADMINMODIFY&""" href=""" &fh.getUriAdminModifyCur(message_id)& """ target=""_top"">"
			admin_links = admin_links & "<img src="""&VP_SCRIPT_IMAGES&"admin_modify.gif"" border=""0"" align=""absmiddle"">"
			admin_links = admin_links & "</a>"
			admin_links = admin_links & " "
			admin_links = admin_links & "<a title="""&IDS_FORUM_LIST_ADMINDEL&""" href="""    &fh.getUriAdminDoDeleteCur& """ target=""_top"">"
			admin_links = admin_links & "<img src="""&VP_SCRIPT_IMAGES&"admin_del.gif"" border=""0"" align=""absmiddle"">"
			admin_links = admin_links & "</a>"
			admin_links = admin_links & " "
			admin_links = admin_links & "<a title="""&IDS_FORUM_LIST_ADMINDELRECURSIVE&""" href=""" &fh.getUriAdminDoDeleteCurSubs& """ target=""_top"">"
			admin_links = admin_links & "<img src="""&VP_SCRIPT_IMAGES&"admin_delall.gif"" border=""0"" align=""absmiddle"">"
			admin_links = admin_links & "</a>"
			admin_links = admin_links & "</em></b></font>"
		else	
			admin_links = ""
		end if

		'specify the distance of two articles  by modifing the "height" attribute 
        %>  <tr><td colspan="3"><img src="<%=VP_SCRIPT_IMAGES%>t.gif" border="0" width="1" height="7"></td></tr><% 
        
	    'a selected entry 
		if is_selected then
%>
	<tr><td width="70%"><table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr><td><a name="<%=fh.getArticleAnchor(message_id)%>"></a>
	<font <%=title_font%> <%=text_color%>><%WriteIndent fh.getCurIndentLevel, IndentType%></font></td>
	<td <%=select_color%> width="100%"><font <%=title_font%> <%=text_color%>><%=bold_in%><%=fmtFilter(article_rs("Subject"))%><%=bold_out%><%=image_tag%>
	<%=cnt_txt%> <%=admin_links%>&nbsp;</font></td></tr>
	</table></td>

	<td nowrap <%=select_color%> width="20%"><font <%=title_font%> <%=text_color%>><%=bold_in%><%=fmtFilter(article_rs("AuthorName"))%><%=bold_out%>&nbsp;</font></td>
	<td nowrap align=right <%=select_color%> width="10%"><font <%=title_font%> <%=text_color%>><%=bold_in%><%=DateTimeString(article_rs("Date"), True)%><%=bold_out%>&nbsp;</font></td>
	</tr>

	<tr>
		<td colspan="3" width="100%">
		<table border="0" cellspacing="0" cellpadding="0" width="100%">
		<tr><td><font <%=title_font%> <%=text_color%>><%WriteIndent fh.getCurIndentLevel, indentContent%></font></td>
			<td <%=content_color%> width="100%"><table border="0" cellspacing="5" cellpadding="0" width="100%">
		<tr><td><table border="0" cellspacing="0" cellpadding="0" width="100%">
		<tr><td colspan="2"><font <%=content_font%>><%=fmtContent(article_rs("Text"))%><br>&nbsp;</td></tr>
		<tr><td align="left"><font <%=title_font%>>
		    [<a href="<%=fh.getUriUserReplyCur(message_id)%>" title="<%=IDS_FORUM_REPLY_TITLE%>"><%=IDS_FORUM_LIST_REPLY%></a>]
			[<a href="<%=fh.getUriUserMailCur(message_id)%>"  title="<%=IDS_FORUM_MAIL_TITLE%>"><%=IDS_FORUM_LIST_MAIL%></a>]
			[<a	href="<%=fh.getUriUserNew(article_rs("ForumID"))%>" title="<%=IDS_FORUM_NEW_TITLE%>"><%=IDS_FORUM_LIST_NEW%></a>]
			</font></td>
											
    		<%if article_rs("Password")<>"" then%>
	    		<td align="right"><font <%=title_font%>>
				[<a href="<%=fh.getUriOwnerModifyCurPw(message_id)%>"><font <%=title_font%>><i><%=IDS_FORUM_LIST_OWNERMODIFY%></i></a>]
				[<a href="<%=fh.getUriOwnerDeleteCurPw(message_id)%>"><font <%=title_font%>><i><%=IDS_FORUM_LIST_OWNERDELETE%></i></a>]</font></td>
			<%else%>
				<td align="right">&nbsp;</td>
			<%end if%>
		</tr>
		</table></td>
    	</tr></table></td>
	    </tr></table></td>
	</tr>
<%
		else
%>
	<tr><td width="70%"><table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr><td><a name="<%=fh.getArticleAnchor(message_id)%>"></a>
	<font <%=title_font%> <%=text_color%>><%WriteIndent fh.getCurIndentLevel, indentBlank%></font></td>
	<td <%=select_color%> width="100%"><a class="LIST" href="<%=fh.getUriSelectCur%>">
	<font <%=title_font%> <%=text_color%>><%=bold_in%><%=fmtFilter(article_rs("Subject"))%><%=bold_out%></a><%=image_tag%>
	<%=cnt_txt%> <%=admin_links%>&nbsp;</font></td></tr>
	</table></td>
	
	<td nowrap <%=select_color%> width="20%"><font <%=title_font%> <%=text_color%>><%=bold_in%><%=fmtFilter(article_rs("AuthorName"))%><%=bold_out%>&nbsp;</font></td>
	<td nowrap align=right <%=select_color%> width="10%"><font <%=title_font%> <%=text_color%>><%=bold_in%><%=DateTimeString(article_rs("Date"), True)%><%=bold_out%>&nbsp;</font></td>
	</tr>
<%			if Expanded = expandPreview Then %>
	<tr><td colspan=3>
	<table border=0 cellspacing="0" cellpadding="0" width="100%">
	<tr><td><font <%=title_font%> <%=text_color%>><%WriteIndent fh.getCurIndentLevel, indentContent%></td>
	<td width="100%" <%=content_color%>><font <%=title_font%>><%=fmtFilter(Left(article_rs("Text"),150))%>...</font></td></tr>
	</table></td></tr>
<%			End If
	
		end if

	  end if
	  
	  MessageNumber = MessageNumber + 1
	  
	  ' advance the "message pointer"
	  fh.moveNext
wend

'distance between header and entries 
%>
<tr><td colspan="3"><img src="<%=VP_SCRIPT_IMAGES%>t.gif" border="0" width="1" height="9"></td></tr>

</table>