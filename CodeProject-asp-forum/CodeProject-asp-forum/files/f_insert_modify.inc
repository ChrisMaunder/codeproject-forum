<%' insert_modify.asp 
%>

<%
' ***********************************************************************
' check.

dim id
dim subject
dim author_name
dim author_email
dim text
dim notify

id           = Request("select")
subject      = Request("Subject")
author_name  = Request("AuthorName")
text         = Request("Text")


if isEMail(Request("AuthorEmail")) then
	author_email = Request("AuthorEmail")
	notify       = Request("email_notify")
else
	notify       = ""
	author_email = "anonym"
end if

if id="" or subject="" or author_name="" or text="" then
	Response.Redirect fh.getUriModifyError("Not all fields were filled in")
end if


' ***********************************************************************
' modify.

'on error resume next

fh.modifyArticle _
	id, _
	subject, _
	author_name, _
	author_email, _
	text, _
	notify


' ***********************************************************************
' >> continue.

if err<>0 then
	Response.Redirect fh.getUriModifyError(err.Description)
else
	Response.Redirect fh.getUriMain( id )
end if
%>