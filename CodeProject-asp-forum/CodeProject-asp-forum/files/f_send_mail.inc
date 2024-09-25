<%' send_mail.asp 
%>

<%
' ***********************************************************************
' check.

dim id
dim subject
dim author_name
dim author_email
dim text

id           = Request("select")
subject      = Request("Subject")
author_name  = Request("AuthorName")
author_email = Request("AuthorEmail")
text         = Request("Text")

if subject="" or author_name="" or author_email="" or text="" then
	Response.Redirect fh.getUriEmailError("not all fields were filled")
end if


' ***********************************************************************
' get the e-mail adress of the receiver

dim rs
set rs = fh.getArticleRs( id )

dim rec_email
dim rec_name

rec_email = rs("AuthorEMail")
rec_name  = rs("AuthorName")


' ***********************************************************************
' build body.

dim body
body = ""
body = body & "This is an answer to your message in the forum '" &fh.getForumName(rs("ForumID"))& "':" &vbCrLf
body = body & "" &vbCrLf
body = body & text &vbCrLf
body = body & "" &vbCrLf
body = body & "---------------------------------------------------------------" &vbCrLf
body = body & ANSWERTEXT &vbCrLf
body = body & BASICURL &vbCrLf
body = body & "" &vbCrLf


' ***********************************************************************
' send via e-mail.

on error resume next
SendEMail MAIL_SVR, MAIL_PORT, author_email, author_name, rec_email, rec_name, subject, body

if err<>0 then
	Response.Redirect _
		fh.getUriEmailError(JMail.ErrorMessage& " (" &err.Description& ")")
end if


' ***********************************************************************
' >> continue.

Response.Redirect fh.getUriMain( id )
%>