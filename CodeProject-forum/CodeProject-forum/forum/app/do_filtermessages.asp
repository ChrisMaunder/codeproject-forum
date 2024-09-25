<% option explicit 

' ###########################################################################
' #
' # file:
' # 	do_filtermessages.asp
' #
' # description:
' # 	sets up the date filter.
' #
' # version:
' # 	2000-02-19 Uwe Keim   file created.
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

' ///////////////////////////////////////////////////////////////////////////
' // get and set.

' Messages per page
Session("MPP") = Request.Form("perpage")
Response.Cookies("MPP") = Session("MPP")
Response.Cookies("MPP").expires = Date()+365	
fh.setArticlesPerPage(Session("MPP"))

' Start date for filtering
Session("datefilter") = Request.Form("datefilter")
Response.Cookies("datefilter") = Session("datefilter")
Response.Cookies("datefilter").expires = Date()+365	
fh.setDateFilterStart Session("datefilter"), Session("LastVisit")

' Expand threads?
Session("expand") = Request.Form("expand")
Response.Cookies("expand") = Session("expand")
Response.Cookies("expand").expires = Date()+365	
fh.setExpandedView(Request.Form("expand"))

' ///////////////////////////////////////////////////////////////////////////
' // >> continue >>.

Response.Redirect fh.getUriMain(0)


' ///////////////////////////////////////////////////////////////////////////
%>
<!--#include file="../includes/cleanup.inc"-->
