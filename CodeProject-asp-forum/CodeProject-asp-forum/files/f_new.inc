<%' new.asp 
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
			}
		//--></script>

		<%
		' ************************************************************

		dim rs
		set rs = fh.getForumRs(Request("forumid"))

		' ************************************************************
		%>

	
		<p><%=FONT_REPLY_FORM2%>Here you can enter a new message in the Forum <b><%=rs("Name")%></b>.</font></p>

		<form action="<%=fh.getUriInsertNew%>" method="post"
			name="form" onsubmit="return chkFormular()">

			<input type="hidden" name="forumid"  value="<%=Request("forumid")%>">

			<div align="left">
				<table border="0" cellspacing="0">
					<tr>
						<td valign="middle"><%= FONT_REPLY_FORM1 %>Subject:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="35" name="Subject"></td>
					</tr>
					<tr>
						<td valign="top"><%=FONT_REPLY_FORM1%>Text:</font></td>
						<td valign="top" colspan="2"><textarea name="Text" rows="15" cols="60"></textarea></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="middle"><%=FONT_REPLY_FORM1%>Name:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="35" name="AuthorName"></td>
					</tr>
					<tr>
						<td valign="middle"><%=FONT_REPLY_FORM1%>E-Mail:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="35" name="AuthorEmail"></td>
					</tr>
					<tr>
						<td valign="middle">&nbsp;</td>
						<td valign="middle" colspan="2"><%=FONT_REPLY_FORM1%><input type="checkbox" name="email_notify"
							value="ja" checked> Notify me by email if someone responds to this message?</font></td>
					</tr> 
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2"><input type="submit" name="B1" value="Submit"></td>
					</tr>
				</table>
			</div>
		</form>