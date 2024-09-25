<%' insert_reply.asp
%>

<%
' ***********************************************************************
' check.

dim parent_id
dim subject
dim author_name
dim author_email
dim text
dim notify

parent_id    = Request("ParentID")
subject      = Request("Subject")
author_name  = Request("AuthorName")

if isEMail(Request("AuthorEmail")) then
	notify       = Request("email_notify")
	author_email = Request("AuthorEmail")
else
	notify       = ""
	author_email = "anonym"
end if

text         = Request("Text")

if subject="" or author_name="" or text="" then
	Response.Redirect fh.getUriReplyError("Not all fields were filled in")
end if


' ***********************************************************************
' insert.

on error resume next

dim id
id = fh.insertNew( _
	parent_id, _
	Request("forumid"), _
	subject, _
	author_name, _
	author_email, _
	text, _
	notify )

if err<>0 then
	Response.Redirect fh.getUriReplyError(err.Description)
end if

' ***********************************************************************
' notify parent if wanted.

dim rs
set rs = fh.getArticleRs( parent_id )
if rs("Notify")<>"" then


if isEMail(Request("AuthorEmail")) then
	author_email = Request("AuthorEmail")
else
	author_email = rs("AuthorEMail")
end if

	' build body.
	dim body
	body = ""
	body = body & "A reply has been added to you message in the Forum '" &fh.getForumName(Request("forumid"))& "':" &vbCrLf
	body = body & "" &vbCrLf
	body = body & text &vbCrLf
	body = body & "" &vbCrLf
	body = body & "---------------------------------------------------------------" &vbCrLf
	body = body & ANSWERTEXT &vbCrLf
	body = body & BASICURL &vbCrLf
	body = body & "" &vbCrLf


	'on error resume next
	SendEMail MAIL_SVR, MAIL_PORT, author_email, author_name, _
		rs("AuthorEMail"), rs("AuthorName"), subject, body

	if err<>0 then
		Response.Redirect fh.getUriReplyError( _
			JMail.ErrorMessage& " (" &err.Description& ")")
	end if
end if


' ***********************************************************************
' >> continue.

if err<>0 then
	Response.Redirect fh.getUriReplyError(err.Description)
else
	Response.Redirect fh.getUriMain( id )
end if
%>