<%
' ###########################################################################
' #
' # file:
' # 	modify.asp
' #
' # description:
' # 	user form to query the password for modifying 
' # 	an existing article in a forum.
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
strTitle   = "Enter your password"
strUpdate  = "15 Jun 2000"
forum_id   = Request.QueryString("forumid")
forum_name = fh.getForumName(forum_id)
strDesc    = "Please enter your password to modify the message"
%>

<!-- #include file="includes/header.asp" -->

		<%
		' ************************************************************

		dim rs
		set rs = fh.getArticleRs(Request.QueryString("select"))

		' ************************************************************
		%>

		<form action="<%=fh.getUriOwnerModify%>" method="post">

			<input type="hidden" name="id" value="<%=rs("ID")%>">

			<div align="left">
				<table border="0" cellspacing="0">
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Password:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="35"
							name="ArticlePassword"></font></td>
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

		<% 
		rs.close
		set rs = nothing
		%>
		
<!--#include file="includes/footer.asp" -->
<!--#include file="includes/cleanup.inc"-->
