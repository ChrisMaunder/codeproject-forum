<?php

include "config.inc";
include "functions.inc";

?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">

<html>
<head>
	<title>CP PHP Forum</title>

<style type="text/css">
	.nav:link    { text-decoration:none; color:#000000; }
	.nav:visited { text-decoration:none; color:#000000; }
	.nav:active  { text-decoration:none; color:#000000; }
	.nav:hover   { text-decoration:underline; color:#0000a0; }
	.nav2:link    { text-decoration:none; color:#000000; }
	.nav2:visited { text-decoration:none; color:#000000; }
	.nav2:active  { text-decoration:none; color:#000000; }
	.nav2:hover   { text-decoration:underline; color:#0000a0; }
</style>
<link rel="stylesheet" type=text/css href="css/global.css">
</head>

<body>
		<script language="JavaScript"><!--
			function chkFormular() {
				if ( document.form.Subject.value=="" ) {
					alert( "Please enter a subject" );
					document.form.Subject.focus();
					return false;
				}

				if ( document.form.Text.value=="" ) {
					alert( "Please enter a message" );
					document.form.Text.focus();
					return false;
				}

				if ( document.form.AuthorName.value=="" ) {
					alert( "Please enter your name" );
					document.form.AuthorName.focus();
					return false;
				}

				if ( document.form.AuthorEmail.value=="" ) {
					alert( "Please enter your e-mail address" );
					document.form.AuthorEmail.focus();
					return false;
				}
			}
		//--></script>

		<!-------------------------------------->
		<!-- the message to reply to -->

		<?php // $Parent is the message to reply to

			$dbcon = mysql_connect ('localhost', $un, $pw);
			mysql_select_db ( $db );
			$sql= "SELECT ForumID, Subject, AuthorName, Date, Text FROM cparticle WHERE ID = ".$Parent;
			$res = mysql_query($sql);
			if ($res)
			if ($row = mysql_fetch_object($res))
			{
				$reply_subject = "Re: ".$row->Subject;
		?>

		<table border="0" cellspacing="0" cellpadding="0" width="100%">
			<tr>
				<td width="100%" bgcolor="<?php echo $COLOR_REPLY_BG; ?>">
					<table cellspacing="2" cellpadding="0" width="100%">
						<tr>
							<td><?php echo $FONT_REPLY_FORM1; ?>Forum:</font></td>
							<td width="100%"><?php echo $FONT_REPLY_FORM1; ?><b><?php echo $row->ForumID; ?></b></font></td>
						</tr>
						<tr>
							<td><?php echo $FONT_REPLY_FORM1; ?>Subject:</font></td>
							<td width="100%"><?php echo $FONT_REPLY_FORM1; ?><b><?php echo $row->Subject; ?></b></font></td>
						</tr>
						<tr>
							<td><?php echo $FONT_REPLY_FORM1; ?>Sender:</font></td>
							<td width="100%"><?php echo $FONT_REPLY_FORM1; ?><b><?php echo $row->AuthorName; ?></b></font></td>
						</tr>
						<tr>
							<td><?php echo $FONT_REPLY_FORM1; ?>Date:</font></td>
							<td width="100%"><?php echo $FONT_REPLY_FORM1; ?><b><?php echo $row->Date; ?></b></font></td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td>
					<table cellspacing="5" cellpadding="0" width="100%">
						<tr>
							<td><?php echo $FONT_REPLY_FORM1; echo fmtContent($row->Text); ?></font></td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
<?php 		} ?>

		<!-------------------------------------->

		<form action="index.php?Action=new&forum_id=<?php echo $forum_id; ?>" method="POST"
			name="form" onsubmit="return chkFormular()">

			<input type="hidden" name="Parent" value="<?php echo $Parent; ?>">
			<input type="hidden" name="forumid"  value="<?php echo $ForumID; ?>">

			<div align="left">
				<table border="0" cellspacing="0">
					<tr>
						<td valign="middle"><?php echo $FONT_REPLY_FORM1; ?>Subject:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="40" name="Subject" value="<?php echo $reply_subject; ?>"></td>
					</tr>
					<tr>
						<td valign="top"><?php echo $FONT_REPLY_FORM1; ?>Text:</font></td>
						<td valign="top" colspan="2"><textarea name="Text" rows="15" cols="60"></textarea></td>
					</tr>
					<tr>
						<td valign="top">&nbsp;</td>
						<td valign="top" colspan="2">&nbsp;</td>
					</tr>
					<tr>
						<td valign="middle"><?php echo $FONT_REPLY_FORM1; ?>Name:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="40" name="AuthorName"></td>
					</tr>
					<tr>
						<td valign="middle"><?php echo $FONT_REPLY_FORM1; ?>E-Mail:</font></td>
						<td valign="middle" colspan="2"><input type="text" size="40" name="AuthorEmail"></td>
					</tr>
					<tr>
						<td valign="middle">&nbsp;</td>
						<td valign="middle" colspan="2"><?php echo $FONT_REPLY_FORM1; ?><input type="checkbox" name="email_notify" value="ja" checked>
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

		</body>
		</html>

