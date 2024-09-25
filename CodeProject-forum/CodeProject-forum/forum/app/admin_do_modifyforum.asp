<% option explicit 

' ###########################################################################
' #
' # file:
' # 	modify_forum.asp
' #
' # description:
' # 	modifies the properties of an existing forum.
' #
' # version:
' # 	2000-01-07 Uwe Keim   file created.
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
dim shortname
dim name
dim description
dim notify_reply
dim notify_new

forum_id     = Request.Form("forumid")
shortname    = Request.Form("Shortname")
name         = Request.Form("ForumName")
description  = Request.Form("Description")
notify_reply = Request.Form("NotifyReply")
notify_new	 = Request.Form("NotifyNew")

if forum_id="" or name="" then
	Response.Redirect fh.getUriFailure(IDS_ADMIN_ERR_FIELDSMISSING)
end if


' ***********************************************************************
' modify.

'on error resume next

fh.modifyForum _
	forum_id, _
	shortname, _
	name, _
	description, _
	notify_reply, _
	notify_new


' ***********************************************************************
' >> continue.

if err<>0 then
	Response.Redirect fh.getUriFailure(err.Description)
else
	Response.Redirect fh.getUriMain( 0 )
end if


' ***********************************************************************
%>
<!--#include file="../includes/cleanup.inc"-->
