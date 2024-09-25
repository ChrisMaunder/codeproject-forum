<%
' ###########################################################################
' #
' # file:
' # 	admin.asp
' #
' # description:
' # 	user form change the properties of a forum.
' #
' # version:
' # 	2000-01-07 Uwe Keim   file created.
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
strTitle   = "Administer Forum"
strUpdate  = "15 Jun 2000"
forum_id   = Request.QueryString("forumid")
forum_name = fh.getForumName(forum_id)
strDesc    = "This allows you to administer the " & forum_name & " forum"
%>

<!-- #include file="includes/header.asp" -->

		<script language="JavaScript"><!--
			function chkFormular() {
				if ( document.form.ForumName.value=="" ) {
					alert( "<%=IDS_JS_NEEDFORUMNAME%>" );
					document.form.ForumName.focus();
					return false;
				}
			}
		//--></script>

		<%
		' ************************************************************

		dim rs
		set rs = fh.getForumRs(Request.QueryString("forumid"))

		' ************************************************************
		%>

		<p><font size="1" face="Verdana">Here you can change properties
			of the forum<b><%=rs("Name")%></b>.</font></p>

		<form action="<%=fh.getUriAdminDoModifyForum(Request.QueryString("forumid"))%>" method="post"
			name="form" onsubmit="return chkFormular()">

			<input type="hidden" name="forumid"  value="<%=Request.QueryString("forumid")%>">

			<div align="left">
				<table border="0" cellspacing="0">
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Short name:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="35"
							name="Shortname" value="<%=rs("Shortname")%>"></font></td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Name:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="35"
							name="ForumName" value="<%=rs("Name")%>"></font></td>
					</tr>
					<tr>
						<td valign="top"><font size="1" face="Verdana">Description:</font></td>
						<td valign="top" colspan="2"><font size="1"
							face="Verdana"><textarea name="Description" rows="5"
							cols="30"><%=rs("Description")%></textarea></font></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Notify new E-Mail:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="35"
							name="NotifyNew" value="<%=rs("NotifyNew")%>"></font></td>
					</tr>
					<tr>
						<td valign="middle"><font size="1" face="Verdana">Notify reply E-Mail:</font></td>
						<td valign="middle" colspan="2"><font size="1"
							face="Verdana"><input type="text" size="35"
							name="NotifyReply" value="<%=rs("NotifyReply")%>"></font></td>
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
		' ************************************************************

		rs.close
		set rs = nothing

		' ************************************************************
		%>

	
<!--#include file="includes/footer.asp" -->
<!--#include file="includes/cleanup.inc"-->

