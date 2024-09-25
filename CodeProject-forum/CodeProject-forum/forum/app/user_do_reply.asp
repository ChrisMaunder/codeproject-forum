<% option explicit 

' ###########################################################################
' #
' # file:
' # 	insert_reply.asp
' #
' # description:
' # 	stores the reply to a forum article in the database.
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
' ***********************************************************************
' check.

dim forum_id
dim parent_id
dim subject
dim author_name
dim author_email
dim text
dim email_notify
dim password

forum_id     = Request.Form("forumid")
parent_id    = Request.Form("ParentID")
subject      = Request.Form("Subject")
author_name  = Request.Form("AuthorName")
author_email = Request.Form("AuthorEmail")
text         = Request.Form("Text")
email_notify = Request.Form("email_notify")
password     = Request.Form("ArticlePassword")

if subject="" or author_name="" or author_email="" or text="" then
	Response.Redirect fh.getUriFailure(IDS_REPLY_ERR_FIELDSMISSING)
end if

' Store in session variables to save user typing later on
Session("AuthorName") = author_name
Session("AuthorEmail") = author_email

' ***********************************************************************
' insert.

on error resume next

dim id
id = fh.insertChild( _
	parent_id, _
	forum_id, _
	subject, _
	author_name, _
	author_email, _
	text, _
	email_notify, _
	password )

if err<>0 then
	Response.Redirect fh.getUriFailure(err.Description)
end if


' ***********************************************************************
' notify parent if wanted.

dim rs
set rs = fh.getArticleRs( parent_id )
if rs("Notify")<>"" then

	' build body.
	dim body
	body = fmt(IDS_REPLY_NOTIFYBODY, Array(fh.getForumName(forum_id),text))

	on error resume next
	sendEMail author_email, author_name, _
		rs("AuthorEMail"), rs("AuthorName"), subject, body

	if err<>0 then
		Response.Redirect fh.getUriFailure( _
			err.ErrorMessage& " (" &err.Description& ")")
	end if
end if


' ***********************************************************************
' notify admin if wanted.

set rs = fh.getForumRs( forum_id )
if rs("NotifyReply")<>"" then

	' build body.
	body = fmt(IDS_REPLY_NOTIFYADMINBODY, Array(fh.getForumName(forum_id),text))

	on error resume next
	sendEMail author_email, author_name, _
		rs("NotifyReply"), rs("NotifyReply"), subject, body

	if err<>0 then
		Response.Redirect fh.getUriFailure( _
			err.ErrorMessage& " (" &err.Description& ")")
	end if
end if


' ***********************************************************************
' >> continue.

if err<>0 then
	Response.Redirect fh.getUriFailure(err.Description)
else
	Response.Redirect fh.getUriMain( id )
end if

rs.close
set rs = nothing

' ***********************************************************************
%>
<!--#include file="../includes/cleanup.inc"-->
