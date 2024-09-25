<%
' ###########################################################################
' #
' # file:
' # 	new.asp
' #
' # description:
' # 	user form to insert a new article into the forum.
' #
' # version:
' # 	2000-02-06 Uwe Keim   password support added.
' # 	1999-12-29 Uwe Keim   file created.
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
strTitle   = "New Message"
strUpdate  = "15 Jun 2000"
forum_id   = Request.QueryString("forumid")
forum_name = fh.getForumName(forum_id)
strDesc    = "Here you can add a new message to the " & forum_name & " forum"
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

		<form action="<%=fh.getUriUserDoNew%>" method="post"
			name="form" onsubmit="return chkFormular()">

			<input type="hidden" name="forumid"  value="<%=forum_id%>">

			<div align="left">
				<table border="0" cellspacing="0">
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Subject:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="35"
							name="Subject"></font></td>
					</tr>
					<tr>
						<td valign="top"><font size="1" face="Verdana">Text:</font></td>
						<td valign="top" colspan="2"><font size="1"
							face="Verdana"><textarea name="Text" rows="15"
							cols="60"></textarea></font></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Your Name:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="35"
							name="AuthorName" value="<%=Session("AuthorName")%>"></font></td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">E-Mail:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="35"
							name="AuthorEmail" value="<%=Session("AuthorEmail")%>"></font></td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">&nbsp;</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="checkbox" name="email_notify"
							value="ja" checked> Notify me by e-mail if someone
							answers to this message</font></td>
					</tr>
					<tr>
						<td valign="top"><font face="verdana" size="1">&nbsp;</font></td>
						<td valign="top" colspan="2"><font face="verdana" size="1">&nbsp;</font></td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Password:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="40"
							name="ArticlePassword" value="<%=getRndNr%>"> Set only if you want to 
							modify your message later.</font></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2"><font size="1"
							face="Verdana"><input type="submit" name="B1"
							value="Submit"></font></td>
					</tr>
				</table>
			</div>
		</form>


<!--#include file="includes/footer.asp" -->
<!--#include file="includes/cleanup.inc"-->
