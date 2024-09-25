<% option explicit

' ###########################################################################
' #
' # file:
' # 	insert_new.asp
' #
' # description:
' # 	inserts a new article for a forum in the database.
' #
' # version:
' # 	2000-02-06 Uwe Keim   password support added.
' # 	2000-01-07 Uwe Keim   added notifications to forum admin.
' # 	1999-12-29 Uwe Keim   file created.
' #
' # copyright:
' #		Written by Uwe Keim <keim@zeta-software.de>
' #		Adapted by Chris Maunder <cmaunder@mail.com>
' #		Copyright (c) 1998-2000. All Rights Reserved.
' # 
' #     Check the Code Project (http://www.codeproject.com) for the latest.
' # 
' #		These scripts may be used in any way you desire PROVIDING the 
' #		"powered by CodeProject" logo remains in the top left corner of the
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
%>
<!--#include file="../../common/scripts.asp"-->
<!--#include file="../includes/locafx.inc"-->
<%
' ***************************************************************************
' check.

dim forum_id
dim subject
dim author_name
dim author_email
dim text
dim email_notify
dim password

forum_id     = Request.QueryString("forumid")
subject      = Request.Form("Subject")
author_name  = Request.Form("AuthorName")
author_email = Request.Form("AuthorEmail")
Text         = Request.Form("Text")
email_notify = Request.Form("email_notify")
password     = Request.Form("ArticlePassword")

if subject="" or author_name="" or author_email="" or Text="" then
	Response.Redirect fh.getUriFailure(IDS_NEW_ERR_FIELDSMISSING)
end if

' Store in session variables to save user typing later on
Session("AuthorName") = author_name
Session("AuthorEmail") = author_email

' ***************************************************************************
' insert.

on error resume next

dim id
id = fh.insertChild( _
	0, _
	forum_id, _
	subject, _
	author_name, _
	author_email, _
	text, _
	email_notify, _
	password )


' ***************************************************************************
' notify admin if wanted.

dim rs
set rs = fh.getForumRs( forum_id )

dim notify_new
if not (rs.Bof and Rs.Eof) then
	notify_new = rs("NotifyNew")
else
	notify_new = ""
end if

if notify_new<>"" then
	' build body.
	dim body
	body = fmt(IDS_NEW_NOTIFYADMINBODY, Array(fh.getForumName(forum_id),text))

	on error resume next
	sendEMail author_email, author_name, notify_new, notify_new, subject, body

	if err<>0 then
		Response.Redirect fh.getUriFailure( _
			err.ErrorMessage& " (" &err.Description& ")")
	end if
end if


' ***************************************************************************
' >> continue.

if err<>0 then
	Response.Redirect fh.getUriFailure(err.Description)
else
	Response.Redirect fh.getUriMain( id )
end if

rs.close
set rs = nothing

' ***************************************************************************
%>
<!--#include file="../includes/cleanup.inc"-->
