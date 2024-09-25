<%
' ///////////////////////////////////////////////////////////////////////////
' // draw the indent graphics.

' this function draws the indent and the article-image, based on the 
' indent-level and the state of the article.
sub WriteIndent( ind_lvl, state )
	dim i
	for i=1 to ind_lvl
		Response.Write "<img border=""0"" height=""1"" width=""20"" src=""../img_forum/ind.gif"">"
	next

	if state="selected" then
		Response.Write "<img border=""0"" align=""absmiddle"" src=""../img_forum/news_selected.gif"">"
	elseif state="content" then
		Response.Write "<img border=""0"" align=""absmiddle"" src=""../img_forum/news_none.gif"">"
	else
		Response.Write "<img border=""0"" align=""absmiddle"" src=""../img_forum/news_unselected.gif"">"
	end if

	Response.Write "<img border=""0"" width=""2"" height=""2"" align=""absmiddle"" src=""../img_forum/t.gif"">"
end sub

' ///////////////////////////////////////////////////////////////////////////
%>

<%
fh.readArticles forum_id
%>

<p><%=FONT1%>[<a href="<%=fh.getUriNew(forum_id)%>" target="_top">New Message</a>]</font></p>

<table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
		<td width="70%" bgcolor="<%= COLOR_HEADER_BG %>">
			<table border="0" cellspacing="0" cellpadding="2" width="100%">
				<tr>
					<td><%=FONT1%>Message&nbsp;&nbsp;</font></td>
				</tr>
			</table>
		</td>
		<td width="20%" bgcolor="<%= COLOR_HEADER_BG %>">
			<table border="0" cellspacing="0" cellpadding="0" width="100%">
				<tr>
					<td><img src="../img_forum/t.gif" border="0" width="1" height="1"></td>
				</tr>
				<tr>
					<td><%=FONT1%>Author&nbsp;&nbsp;</font></td>
				</tr>
				<tr>
					<td><img src="../img_forum/t.gif" border="0" width="1" height="1"></td>
				</tr>
			</table>
		</td>
		<td width="10%" bgcolor="<%= COLOR_HEADER_BG %>">
			<table border="0" cellspacing="0" cellpadding="0" width="100%">
				<tr>
					<td><img src="../img_forum/t.gif" border="0" width="1" height="1"></td>
				</tr>
				<tr>
					<td><%=FONT1%>Date&nbsp;&nbsp;</font></td>
				</tr>
				<tr>
					<td><img src="../img_forum/t.gif" border="0" width="1" height="1"></td>
				</tr>
			</table>
		</td>
	</tr>
	<tr><td colspan="3"><img src="../img_forum/t.gif" border="0" width="1" height="2"></td></tr>

	<%	dim rs_entries
		dim sql
		sql= "SELECT * FROM Article WHERE ForumID =" &forum_id& " ORDER BY [Position]"
		set rs_entries = fh.m_Conn.Execute(sql)
		
		while not rs_entries.Eof
		' store some decision values.
		dim parent						' whether the current article is a parent article
		dim selected					' whether the current article is selected.
		parent     = (rs_entries("ParentID")=0)
		selected = (CStr(Request("select"))=CStr(rs_entries("ID")))

		' design: all parent entries are bold.
		dim bold_in, bold_out
		if parent then
			bold_in  = "<b>"
			bold_out = "</b>"
		else
			bold_in  = ""
			bold_out = ""
		end if

		' design: a selected article gets other colors than
		'         an unselected article.
		dim select_color
		dim text_color
		dim content_color

		if selected then
			text_color    = "color  =""" &COLOR_SELECTED_FG& """"
			select_color  = "bgcolor=""" &COLOR_SELECTED_BG& """"
			content_color = "bgcolor=""" &COLOR_CONTENT_BG & """"
		else
			text_color    = "color =""#000000"""
			select_color  = "bgcolor=""" &COLOR_NONSELECTED_BG& """"
			content_color = ""
		end if


		dim cnt_txt
		cnt_txt = ""


		' if the forum is in admin mode, there are serveral
		' links that allows you to edit and remove articles.
		dim admin_links
		if fh.isInAdminMode then
			admin_links = ""
			admin_links = admin_links & FONT1 &"<b><em>"
			admin_links = admin_links & "&nbsp;&nbsp;&nbsp;&nbsp; "
			admin_links = admin_links & "<a title=""Modify this message"" href=""" &fh.getUriModifyCurMsg(rs_entries("ID"))& """ target=""_top"">"
			admin_links = admin_links & "<img src=""../img_forum/admin_modify.gif"" border=""0"" align=""absmiddle"">"
			admin_links = admin_links & "</a>"
			admin_links = admin_links & " "
			admin_links = admin_links & "<a title=""Delete this message and all its children"" href=""" &fh.getUriDeleteCurMsgSubs(rs_entries("ID"))& """ target=""_top"">"
			admin_links = admin_links & "<img src=""../img_forum/admin_delall.gif"" border=""0"" align=""absmiddle"">"
			admin_links = admin_links & "</a>"
			admin_links = admin_links & "</em></b></font>"
		else	
			admin_links = ""
		end if %>

		<!-- specify the distance of two articles 
			 by modifing the "height" attribute -->
		<tr><td colspan="3"><img src="../img_forum/t.gif" border="0" width="1" height="9"></td></tr>

		<!-- ********************************************************* -->
		<!-- a selected entry -->

		<% if selected then %>
			<tr>
				<!-- col 1 -->
				<td width="70%">
					<table border="0" cellspacing="0" cellpadding="0" width="100%">
						<tr>
							<td><a name="<%= rs_entries("ID")%>"></a><%=FONT1%><%WriteIndent rs_entries("Indent"), ""%></font></td>
							<td <%=select_color%> width="100%"><%=FONT1%><%=bold_in%><%= rs_entries("Subject")%><%=bold_out%>
								<%=cnt_txt%> <%=admin_links%>&nbsp;&nbsp;</font></td>
						</tr>
					</table>
				</td>

				<!-- col 2 -->
				<td nowrap <%=select_color%> width="20%"><%=FONT1%><%=bold_in%><%= rs_entries("AuthorName")%><%=bold_out%>&nbsp;&nbsp;</font></td>

				<!-- col 3 -->
				<td nowrap <%=select_color%> width="10%"><%=FONT1%><%=bold_in%><%=FormatDateTime(rs_entries("Date"),vbShortDate)%><%=bold_out%>&nbsp;&nbsp;</font></td>
			</tr>

			<!-- the content of a selected entry -->
			<% if CStr(Request("select"))=CStr(rs_entries("ID")) then %>
				<tr>
					<!-- col 1,2 and 3 -->
					<td colspan="3" width="100%"><table border="0" cellspacing="0" cellpadding="0" width="100%">
						<tr>
							<td><%=FONT1%><%WriteIndent rs_entries("Indent"), "content"%></font></td>
							<td <%=content_color%> width="100%"><table border="0" cellspacing="5" cellpadding="0" width="100%">
								<tr>
									<td><%=FONT1%><%=fmtContent(rs_entries("Text"))%><br>&nbsp;<br>
										[<a href="<%=fh.getUriReplyForum%>" target="_top"><%=FONT1%>Reply</font></a>]
										[<a href="<%=fh.getUriReplyAuthor%>" target="_top"><%=FONT1%>Email Author</font></a>]
										[<a	href="<%=fh.getUriNew(rs_entries("ForumID"))%>" target="_top"><%=FONT1%>New Message</font></a>]</font></td>
								</tr>
							</table></td>
						</tr>
					</table></td>
				</tr>
			<%end if%>

		<!-- ********************************************************* -->
		<!-- a not-selected entry -->

		<% else %>
			<tr>
				<!-- col 1 -->
				<td width="70%"><table border="0" cellspacing="0" cellpadding="0" width="100%">
					<tr>
						<td><a name="<%=rs_entries("ID")%>"></a><%=FONT1%><%WriteIndent rs_entries("Indent"), ""%></font></td>
						<td <%=select_color%> width="100%"><a class="LIST" href="<%=fh.getUriSelectMsg(rs_entries("ID"))%>" target="_top"><%=FONT1%><%=bold_in%><%=rs_entries("Subject")%><%=bold_out%></a> 
							<%=cnt_txt%> <%=admin_links%>&nbsp;&nbsp;</font></td>
					</tr>
				</table></td>

				<!-- col 2 -->
				<td nowrap <%=select_color%> width="20%"><%=FONT1%><%=bold_in%><%=rs_entries("AuthorName")%><%=bold_out%>&nbsp;&nbsp;</font></td>

				<!-- col 3 -->
				<td nowrap <%=select_color%> width="10%"><%=FONT1%><%=bold_in%><%=FormatDateTime(rs_entries("Date"),vbShortDate)%><%=bold_out%>&nbsp;&nbsp;</font></td>
			</tr>
		<% end if %>

		<!-- ********************************************************* -->




		<% rs_entries.MoveNext
		wend %>
</table>
