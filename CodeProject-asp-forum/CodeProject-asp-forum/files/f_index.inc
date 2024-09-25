<%' index.asp 
%>

		<style type="text/css"><!--
			.LIST:link    { text-decoration:none; }
			.LIST:visited { text-decoration:none; }
			.LIST:active  { text-decoration:none; }
			.LIST:hover   { text-decoration:underline; }
		--></style>

		<!--
		<% ' //////////////////////////////////////////////////////////////// %>
		<% ' // button for admin mode.                                        %>

			<p><font size="2" face="Arial"><a href="start.asp?ad=12345"><b>Enter Admin mode</b></a></font></p>

		-->
		<hr>
		<% ' //////////////////////////////////////////////////////////////// %>
		<% ' // the list of all available forums.                             %>

<p><%= FONT2 %>Current forums &gt;&nbsp;&nbsp;


		<%
		dim forum_rs
		set forum_rs = fh.getForumsRs

		' display all forums by iterating the recordset.
		while not forum_rs.Eof
		%>

			<b><a href="<%=fh.getUriListWithForum(forum_rs("ID"))%>" title="<%=forum_rs("Description")%>"><%=forum_rs("Name")%></a></b>&nbsp;&nbsp;&nbsp;

		<%
			forum_rs.MoveNext
		wend
		%>
</font></p>
	
		<% ' //////////////////////////////////////////////////////////////// %>
		<% ' // the article-list of the current forum.                        %>

		<% 
		' ---------------------------------------------------------
		' select the forum that is specified in the parameters
		' for that page.
		' the caller may have either specified a forum id or
		' the short-name of a forum.
		dim forum_id
		dim forum_name
		forum_id   = Request("forumid")
		forum_name = Request("forum")

		' translate forum name to forum id (if no id present).
		if forum_id="" and forum_name<>"" then
			forum_id = fh.getForumId( forum_name )
		end if

		' if no forum selected, select first as default.
		if forum_id="" then
			dim rs
			set rs = fh.getForumsRs()
			forum_id = rs("ID")
		end if
		%>


	<!--#include file="../files/header.inc"-->


		<% 
		' ---------------------------------------------------------
		' 'forum_id' must be dimmed and set correctly before
		' #including main.inc.
		'
		' main.inc #includes the list for the forum specified by
		' 'forum_id'.
		%>

		<!--#include file="../files/main.inc"-->