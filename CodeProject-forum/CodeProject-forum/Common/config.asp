<%
' ###########################################################################
' #
' # file:
' # 	config.inc
' #
' # description:
' # 	Common server configuration settings.
' #
' # version:
' # 	2000-04-27 C Maunder  Modified for use with published forum
' # 	1999-12-10 Uwe Keim   file created.
' #
' # copyright:
' #		Written by Uwe Keim <keim@zeta-software.de>
' #		Adapted by Chris Maunder <cmaunder@mail.com>
' #		Copyright (c) 1998-2000. All Rights Reserved.
' # 
' #		Check the Code Project (http://www.codeproject.com) for the latest.
' # 
' #		These scripts may be used in any way you desire PROVIDING the 
' #		'"powered by CodeProject" logo remains in the top left corner of the
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

' ////////////////////////////////////////////////////////////////////////////
' // Your server details.

const SITE_NAME = "the Code Project"			' Your site name
const BASE_DIR  = "/asp/CodeProject-forum/"		' The directory you have these scripts in
const SITE_URL  = "http://www.codedproject.com"		' Your site URL
const SITE_LOGO = "CPLogo.gif"				' Your site logo - store in images directory

' ////////////////////////////////////////////////////////////////////////////
' // mail settings.
' // If you have no mail server or don't have the JMail component (or an
' // equivalent) then ignore this. If you do have a mail component installed
' // then see the Email.inc file in this directory.

const MAIL_SVR    = "my_mail_server.com"		' the mailserver.
const MAIL_PORT   = 25
const MAIL_PREFIX = "[CodeProject] "			' added as a prefix to all mail


' ////////////////////////////////////////////////////////////////////////////
' // path settings - always WITH slash at end.

Dim VP_SCRIPT_COMMON, VP_SCRIPT_IMAGES
VP_SCRIPT_COMMON = BASE_DIR & "common/"
VP_SCRIPT_IMAGES = BASE_DIR & "images/"


' ////////////////////////////////////////////////////////////////////////////
' // color settings.

const COLOR_SELECTED_BG    = "#99CCFF"	' background color of the headline of a selected article.
const COLOR_SELECTED_FG    = "darkblue"  '"#FFFFFF"	' foreground color of the headline of a selected article.

const COLOR_CONTENT_BG     = "#D5EAFF"	' background color of the content(body) of a selected article.
const COLOR_CONTENT_FG     = "#000000"	' foreground color of the content(body) of a selected article.

const COLOR_NONSELECTED_BG = "#FEF9E7"	' background color of the headline of a not-selected article.
const COLOR_NONSELECTED_FG = "#000000"	' foreground color of the headline of a not-selected article.

const COLOR_NONSELECTED_CONTENT_BG = "#FEF9E7" ' background color of the content(body) of a non-selected article.
const COLOR_EXPANDNONSELECTED_CONTENT_BG = "#FBEDBB" ' background color of the header a non-selected article in expanded view.


' ////////////////////////////////////////////////////////////////////////////
' // database connection

' database connection string - for simplicity we use Access to access the databases
function DB( DBVirtualPath )
	DB = "Provider=Microsoft.Jet.OLEDB.4.0;" &_
	     "Persist Security Info=False;" &_
	     "Data Source=" &Server.MapPath(DBVirtualPath)
end function


' ////////////////////////////////////////////////////////////////////////////
%>
