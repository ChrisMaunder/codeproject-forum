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

Dim MailComponentAvailable
MailComponentAvailable = False

' ***********************************************************************
' send an email without attachment. The err object is set if an error occurs.

' NOTE: If you have a Mail component registered on your system then set
'       MailComponentAvailable (above) as True, and modify the script
'       below to use whatever syntax your mailer uses.

sub SendEMail( mail_from, from_name, mail_to, to_name, mail_subject, mail_body )

  'Response.Write "Server     : " & MAIL_SVR & vbCRLF &_
  '               "Port       : " & MAIL_PORT & vbCRLF &_
  '               "Email from : " & mail_from & vbCRLF &_                
  '               "From       : " & from_name & vbCRLF &_
  '               "Email to   : " & mail_to & vbCRLF &_
  '               "To         : " & to_name & vbCRLF &_
  '               "Subject    : " & MAIL_PREFIX & mail_subject & vbCRLF

  if MailComponentAvailable Then

	' //////////////////////////////////////////////////////////////////
	dim JMail
	set JMail = Server.CreateObject("JMail.SMTPMail") 

	' this is my local SMTP server
	JMail.ServerAddress = MAIL_SVR & ":" & CStr(MAIL_PORT)

	' no empty sender allowed.
	if mail_from="" then mail_from = mail_to
	if from_name="" then from_name = to_name

	' this is the sender
	JMail.Sender     = mail_from
	JMail.SenderName = from_name
	JMail.Subject    = MAIL_PREFIX & mail_subject
	
	' the recipients
	JMail.AddRecipientEx mail_to, to_name

	' add some body
	JMail.Body = mail_body

	' normal priority
	JMail.Priority = 3
	
	JMail.AddHeader "Originating-IP", Request.ServerVariables("REMOTE_ADDR")

	' send it and handle errors
	JMail.Execute
	
	set JMail = nothing
	' //////////////////////////////////////////////////////////////////

  end if

end sub
%>