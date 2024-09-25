<%' insert_new.asp 
%>

<%
' ***********************************************************************
' check.

dim subject
dim author_name
dim author_email
dim Text
dim notify

subject      = Request("Subject")
author_name  = Request("AuthorName")
author_email = Request("AuthorEmail")
Text         = Request("Text")

if isEMail(Request("AuthorEmail")) then
	notify       = Request("email_notify")
	author_email = Request("AuthorEmail")
else
	notify       = ""
	author_email = "anonym"
end if

if subject="" or author_name="" or Text="" then
	Response.Redirect fh.getUriNewError("Not all fields were filled in")
end if


' ***********************************************************************
' insert.

'on error resume next

dim id
id = fh.insertNew( _
	0, _
	Request("forumid"), _
	subject, _
	author_name, _
	author_email, _
	text, _
	notify )


' ***********************************************************************
' >> continue.

if err<>0 then
	Response.Redirect getUriNewError(err.Description)
else
	Response.Redirect fh.getUriMain( id )
end if
%>
