<%' modify.asp 
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
		set rs = fh.getArticleRs(Request("modify"))

		' ************************************************************
		%>
		<%=FONT_REPLY_FORM2%><b>Modify a message</b></font>

		<!-------------------------------------->

		<form action="<%=fh.getUriModify%>" method="post"
			name="form" onsubmit="return chkFormular()">

			<input type="hidden" name="id" value="<%=rs("ID")%>">

			<div align="left">
				<table border="0" cellspacing="0">
					<tr>
						<td valign="middle"><%=FONT_REPLY_FORM1%>Subject:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="35" name="Subject" value="<%=rs("Subject")%>"></td>
					</tr>
					<tr>
						<td valign="top"><%=FONT_REPLY_FORM1%>Text:</font></td>
						<td valign="top" colspan="2"><textarea name="Text" rows="15" cols="60"><%=rs("Text")%></textarea></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="middle"><%=FONT_REPLY_FORM1%>Name:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="35" name="AuthorName" value="<%=rs("AuthorName")%>"></td>
					</tr>
					<tr>
						<td valign="middle"><%=FONT_REPLY_FORM1%>E-Mail:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="35" name="AuthorEmail" value="<%=rs("AuthorEmail")%>"></td>
					</tr>
					<tr>
						<%
						dim notify_checked
						if rs("Notify")<>"" and isEMail(rs("AuthorEmail"))then
							notify_checked="checked" 
						else 
							notify_checked=""
						end if
						%>
						<td valign="middle">&nbsp;</td>
						<td valign="middle" colspan="2"><%=FONT_REPLY_FORM1%><input type="checkbox" name="email_notify"
							value="ja" <%=notify_checked%>> Mir eine E-Mail schicken wenn jemand auf mein Eintrag antwortet.</font></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2"><input type="submit" name="B1" value="Absenden"></td>
					</tr>
				</table>
			</div>
		</form>