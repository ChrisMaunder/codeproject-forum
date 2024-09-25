<% option explicit 

' ###########################################################################
' #
' # file:
' # 	insert_modify.asp
' #
' # description:
' # 	modifies an existing message in a forum.
' #
' # version:
' # 	2000-02-06 Uwe Keim   password support added.
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

dim id
dim subject
dim author_name
dim author_email
dim text
dim email_notify
dim password

id           = Request.Form("id")
subject      = Request.Form("Subject")
author_name  = Request.Form("AuthorName")
author_email = Request.Form("AuthorEmail")
text         = Request.Form("Text")
email_notify = Request.Form("email_notify")
password     = Request.Form("ArticlePassword")

if id="" or subject="" or author_name="" or author_email="" or text="" then
	Response.Redirect fh.getUriFailure(IDS_MODIFY_ERR_FIELDSMISSING)
end if


' ***************************************************************************
' modify.

on error resume next

fh.modifyArticle _
	id, _
	subject, _
	author_name, _
	author_email, _
	text, _
	email_notify, _
	password


' ***************************************************************************
' >> continue.

if err<>0 then
	Response.Redirect fh.getUriFailure(err.Description)
else
	Response.Redirect fh.getUriMain( id )
end if


' ***************************************************************************
%>
<!--#include file="../includes/cleanup.inc"-->
