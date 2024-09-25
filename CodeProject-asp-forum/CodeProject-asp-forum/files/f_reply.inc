<%' reply.asp  
%>

		<script language="JavaScript"><!--
			function chkFormular() {
				if ( document.form.Subject.value=="" ) {
					alert( "Please enter a subject!" );
					document.form.Subject.focus();
					return false;
				}

				if ( document.form.Text.value=="" ) {
					alert( "Please enter a message!" );
					document.form.Text.focus();
					return false;
				}

				if ( document.form.AuthorName.value=="" ) {
					alert( "Please enter a name!" );
					document.form.AuthorName.focus();
					return false;
				}
				//if ( document.form.AuthorEmail.value=="" ) {
					//alert(document.form.email_notify);
					//document.form.AuthorEmail.focus();
					//return false;
				//}
			}
		//--></script>

		<%
		' ************************************************************

		dim article_rs
		set article_rs = fh.getArticleRs(Request("select"))

		dim reply_subject
		reply_subject = article_rs("Subject")

		if InStr( reply_subject, "Re:" )<>1 then
			reply_subject = "Re: " + reply_subject
		end if

		' ************************************************************
		%>


	


		<!-------------------------------------->
		<!-- the message to reply to -->

		<table border="0" cellspacing="0" cellpadding="0" width="100%">
			<tr>
				<td width="100%" bgcolor="<%= COLOR_REPLY_BG%>">
					<table cellspacing="2" cellpadding="0" width="100%">
						<tr>
							<td><%= FONT_REPLY_FORM1 %>Forum:</font></td>
							<td width="100%"><%= FONT_REPLY_FORM1 %><b><%=fh.getForumName(article_rs("ForumID"))%></b></font></td>
						</tr>
						<tr>
							<td><%= FONT_REPLY_FORM1 %>Subject:</font></td>
							<td width="100%"><%= FONT_REPLY_FORM1 %><b><%=article_rs("Subject")%></b></font></td>
						</tr>
						<tr>
							<td><%= FONT_REPLY_FORM1 %>Sender:</font></td>
							<td width="100%"><%= FONT_REPLY_FORM1 %><b><%=article_rs("AuthorName")%></b></font></td>
						</tr>
						<tr>
							<td><%= FONT_REPLY_FORM1 %>Date:</font></td>
							<td width="100%"><%= FONT_REPLY_FORM1 %><b><%=FormatDateTime(article_rs("Date"),vbShortDate)%></b></font></td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td>
					<table cellspacing="5" cellpadding="0" width="100%">
						<tr>
							<td><%= FONT_REPLY_FORM1 %><%=fmtContent(article_rs("Text"))%></font></td>
						</tr>
					</table>
				</td>
			</tr>
		</table>

		<!-------------------------------------->

		<form action="<%= fh.getUriSendReply %>" method="POST"
			name="form" onsubmit="return chkFormular()">

			<input type="hidden" name="ParentID" value="<%=Request("select")%>">
			<input type="hidden" name="forumid"  value="<%=article_rs("ForumID")%>">
			
			<div align="left">
				<table border="0" cellspacing="0">
					<tr>
						<td valign="middle"><%= FONT_REPLY_FORM1 %>Subject:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="40" name="Subject" value="<%=reply_subject%>"></td>
					</tr>
					<tr>
						<td valign="top"><%= FONT_REPLY_FORM1 %>Text:</font></td>
						<td valign="top" colspan="2"><textarea name="Text" rows="15" cols="60"></textarea></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="middle"><%= FONT_REPLY_FORM1 %>Name:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="40" name="AuthorName"></td>
					</tr>
					<tr>
						<td valign="middle"><%= FONT_REPLY_FORM1 %>E-Mail:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="40" name="AuthorEmail"></td>
					</tr>
					<tr>
						<td valign="middle">&nbsp;</td>
						<td valign="middle" colspan="2"><%= FONT_REPLY_FORM1 %><input type="checkbox" name="email_notify" value="ja" checked>
							Notify me by email if someone responds to this message?</font></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="middle">&nbsp;</td>
						<td valign="middle" colspan="2"><input type="submit" name="B1" value="Submit"></td>
					</tr>
				</table>
			</div>
		</form>