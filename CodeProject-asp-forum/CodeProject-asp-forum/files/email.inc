<%
' ###########################################################################
' #
' # file:
' # 	email.inc
' #
' # description:
' # 	email functions, using the JMail-component from
' #		http://tech.dimac.net
' #
' # version:
' # 	1.01  1999-12-10 Uwe Keim   simplified version for forum.
' # 	1.01  1999-12-08 Uwe Keim   added empty-sender handling.
' # 	1.00  1999-05-20 Uwe Keim   file created.
' #
' ###########################################################################


' ***********************************************************************
' check email
public function isEMail( sCheckEMail )
	Dim sEmail, nAtLoc

	isEMail = True
	sEmail = Trim(sCheckEmail)
	nAtLoc = InStr(1, sEmail, "@") 'Location of "@"

	If Not (nAtLoc > 1 And (InStrRev(sEmail, ".") > nAtLoc + 1)) Then
		'"@" must exist, and last "." in string must follow the "@"
		isEMail = False
	ElseIf InStr(nAtLoc + 1, sEmail, "@") > nAtLoc Then
		'String can't have more than one "@"
		isEMail = False
	ElseIf Mid(sEmail, nAtLoc + 1, 1) = "." Then
		'String can't have "." immediately following "@"
		isEMail = False
	ElseIf InStr(1, Right(sEmail, 2), ".") > 0 Then
		'String must have at least a two-character top-level domain.
		isEMail = False
	End If
end function
'*********************************************************************


' ***********************************************************************
' send an email without attachment.
' the err object is set, if an error occurs.

sub SendEMail( mail_server, mail_port, mail_from, from_name, mail_to, to_name, mail_subject, mail_body )
	dim JMail
	set JMail = Server.CreateObject("JMail.SMTPMail") 

	' this is my local SMTP server
	JMail.ServerAddress = mail_server & ":" & CStr(mail_port)

	' no empty sender allowed.
	if mail_from="" then mail_from = mail_to
	if from_name="" then from_name = to_name

	' this is the sender
	JMail.Sender     = mail_from
	JMail.SenderName = from_name
	JMail.Subject    = mail_subject
	
	' the recipients
	JMail.AddRecipientEx mail_to, to_name

	' add some body
	JMail.Body = mail_body

	' normal priority
	JMail.Priority = 3
	
	JMail.AddHeader "Originating-IP", Request.ServerVariables("REMOTE_ADDR")

	' send it and handle errors
	JMail.Execute
end sub
%>