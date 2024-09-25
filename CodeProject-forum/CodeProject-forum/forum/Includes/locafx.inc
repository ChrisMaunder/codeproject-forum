<%
' ###########################################################################
' #
' # file:
' # 	locafx.inc
' #
' # description:
' # 	Creates a forum object and initialises it.
' # 	Include this file in every page that uses the forum object
' #
' # version:
' # 	2000-02-06 Uwe Keim   removed resource.inc.
' # 	2000-01-02 Uwe Keim   moved functions to common.inc and string.inc.
' # 	1999-12-29 Uwe Keim   added VP_FORUM to paths.
' # 	1999-12-08 Uwe Keim   file created.
' #
' # copyright:
' #		Written by Uwe Keim <keim@zeta-software.de>
' #		Adapted by Chris Maunder <cmaunder@mail.com>
' #		Copyright (c) 1998-2000. All Rights Reserved.
' # 
' #     Check the Code Project (http://www.codeproject.com) for the latest.
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
%>

<!--#include file="config.asp"-->
<!--#include file="forum.inc" -->

<%
' ///////////////////////////////////////////////////////////////////////////
' // executable code.

' creates an instance of the forum class on every page.
dim fh
set fh = new Forum

' ///////////////////////////////////////////////////////////////////////////
%>
