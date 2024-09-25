<%
' ###########################################################################
' #
' # file:
' # 	mail.asp
' #
' # description:
' # 	user form for replying by e-mailing directly to an article
' #		in the forum.
' #
' # version:
' # 	1.00  1999-12-29 Uwe Keim   file created.
' #
' # copyright:
' #		Written by Uwe Keim <keim@zeta-software.de>
' #		Adapted by Chris Maunder <cmaunder@mail.com>
' #		Copyright (c) 1998-2000. All Rights Reserved.
' # 
' #     Check the Code Project (http://www.codeproject.com) for the latest.
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
strTitle   = "Email a message to author of the current message"
strUpdate  = "15 Jun 2000"
forum_id   = Request.QueryString("forumid")
forum_name = fh.getForumName(forum_id)
strDesc    = "This form allows you to mail a message to the author of the previous message directly. Your message will <b>not</b> appear on the discussion boards."
%>

<!-- #include file="includes/header.asp" -->

		<script language="JavaScript"><!--
			function chkFormular() {
				if ( document.form.Subject.value=="" ) {
					alert( "<%=IDS_JS_NEEDSUBJECT%>" );
					document.form.Subject.focus();
					return false;
				}

				if ( document.form.Text.value=="" ) {
					alert( "<%=IDS_JS_NEEDMSG%>" );
					document.form.Text.focus();
					return false;
				}

				if ( document.form.AuthorName.value=="" ) {
					alert( "<%=IDS_JS_NEEDAUTHOR%>" );
					document.form.AuthorName.focus();
					return false;
				}

				if ( document.form.AuthorEmail.value=="" ) {
					alert( "<%=IDS_JS_NEEDEMAIL%>" );
					document.form.AuthorEmail.focus();
					return false;
				}
			}
		//--></script>

		<%
		' ************************************************************

		' get the article to reply to.
		dim article_rs
		set article_rs = fh.getArticleRs(Request.QueryString("select"))

		' build the subject.
		dim reply_subject
		reply_subject = article_rs("Subject")

		if InStr( reply_subject, "Re:" )<>1 then
			reply_subject = "Re: " + reply_subject
		end if

		' ************************************************************
		%>
	
		<!-------------------------------------->
		<!-- the message to reply to -->

		<%
		' colors.
		dim text_color
		dim select_color
		dim content_color

		text_color    = "color  =""#FFFFFF"""
		select_color  = "bgcolor=""#99CCFF"""
		content_color = "bgcolor=""#D5EAFF"""
		%>

		<table border="0" cellspacing="0" cellpadding="0" width="100%">
			<tr>
				<td width="100%" <%=select_color%>>
					<table cellspacing="2" cellpadding="0" width="100%">
						<tr>
							<td><font size="1" <%=text_color%> face="Verdana">Forum</td>
							<td width="100%"><font size="1" <%=text_color%> 
								face="Verdana"><b><%=fh.getForumName(article_rs("ForumID"))%></b></td>
						</tr>
						<tr>
							<td><font size="1" <%=text_color%> face="Verdana">Subject:</td>
							<td width="100%"><font size="1" <%=text_color%> 
								face="Verdana"><b><%=article_rs("Subject")%></b></td>
						</tr>
						<tr>
							<td><font size="1" <%=text_color%> face="Verdana">Sender:</td>
							<td width="100%"><font size="1" <%=text_color%> 
								face="Verdana"><b><%=article_rs("AuthorName")%></b></td>
						</tr>
						<tr>
							<td><font size="1" <%=text_color%> face="Verdana">Date:</td>
							<td width="100%"><font size="1" <%=text_color%> 
								face="Verdana"><b><%=FormatDateTime(article_rs("Date"),vbShortDate)%></b></td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td <%=content_color%>><table cellspacing="5" cellpadding="0" width="100%">
					<tr><td><font size="2" style="font-size:90%"
					face="Courier New"><%=fmtContent(article_rs("Text"))%></font></td></tr></table></td>
			</tr>
		</table>

		<!-------------------------------------->

		<form action="<%=fh.getUriUserDoMail%>" method="POST" 
			name="form" onsubmit="return chkFormular()">

			<input type="hidden" name="ParentID" value="<%=Request.QueryString("select")%>">

			<div align="left">
				<table border="0" cellspacing="0">
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Subject:</font></td>
						<td valign="middle" colspan="2"><font face="verdana"
							size="1"><input
						type="text" size="40" name="Subject"
						value="<%=reply_subject%>"></font></td>
					</tr>
					<tr>
						<td valign="top"><font size="1" face="Verdana">Text:</font></td>
						<td valign="top" colspan="2"><font size="1"
							face="Verdana"><textarea name="Text" rows="15"
							cols="60"></textarea></font></td>
					</tr>
					<tr>
						<td valign="top"><font face="verdana" size="1">&nbsp;</font></td>
						<td valign="top" colspan="2"><font face="verdana" size="1">&nbsp;</font></td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Your name:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="40"
							name="AuthorName" value="<%=Session("AuthorName")%>"></font></td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">E-Mail:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="40"
							name="AuthorEmail" value="<%=Session("AuthorEmail")%>"></font></td>
					</tr>
					<tr>
						<td valign="top"><font face="verdana" size="1">&nbsp;</font></td>
						<td valign="top" colspan="2"><font face="verdana" size="1">&nbsp;</font></td>
					</tr>
					<tr>
						<td valign="middle"><font face="verdana" size="1">&nbsp;</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="submit" name="B1"
							value="Submit"></font></td>
					</tr>
				</table>
			</div>
		</form>
		
		<%
		article_rs.close
		set article_rs = nothing
		%>
		
<!--#include file="includes/footer.asp" -->
<!--#include file="includes/cleanup.inc"-->
