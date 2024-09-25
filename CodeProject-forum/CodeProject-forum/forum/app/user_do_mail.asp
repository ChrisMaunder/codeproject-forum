<% option explicit 

' ###########################################################################
' #
' # file:
' # 	send_mail.asp
' #
' # description:
' # 	sends a email to the author of a forum article.
' #
' # version:
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

id           = Request.QueryString("select")
subject      = Request.Form("Subject")
author_name  = Request.Form("AuthorName")
author_email = Request.Form("AuthorEmail")
text         = Request.Form("Text")

if subject="" or author_name="" or author_email="" or text="" then
	Response.Redirect fh.getUriFailure(IDS_MAIL_ERR_FIELDSMISSING)
end if

' Store in session variables to save user typing later on
Session("AuthorName") = author_name
Session("AuthorEmail") = author_email

' ***************************************************************************
' get the e-mail adress of the receiver

dim rs
set rs = fh.getArticleRs( id )

dim rec_email
dim rec_name

rec_email = rs("AuthorEMail")
rec_name  = rs("AuthorName")


' ***************************************************************************
' build body.

dim body
body = fmt(IDS_MAIL_BODY, Array(fh.getForumName(rs("ForumID")),text))


' ***************************************************************************
' send via e-mail.

on error resume next
sendEMail author_email, author_name, rec_email, rec_name, subject, body

' ***************************************************************************
' >> continue.

if err<>0 then
	Response.Redirect fh.getUriFailure( _
		err.ErrorMessage& " (" &err.Description& ")")
else
	Response.Redirect fh.getUriMain( id )
end if

rs.close
set rs = nothing

' ***************************************************************************
%>
<!--#include file="../includes/cleanup.inc"-->
