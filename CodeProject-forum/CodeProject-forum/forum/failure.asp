<%
' ###########################################################################
' #
' # file:
' # 	failure.asp
' #
' # description:
' # 	page displayed to the user when an error occurs.
' #
' # version:
' # 	1.00  1999-12-29 Uwe Keim   file created.
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

' --------------------------------------
' get any error text passed to this page.
dim err_txt
err_txt = Request.QueryString("et")
if err_txt="" then err_txt = "unknown"

Dim strTitle, strDesc, strUpdate, forum_id, forum_name
strTitle   = "An Error occured!"
strUpdate  = "15 Jun 2000"
forum_id   = ""
forum_name = ""
strDesc    = ""
%>

<!-- #include file="includes/header.asp" -->

		<p>Your changes were not saved.</p>

		<p>Error description:</p>
		<blockquote>
			<p><b><%=err_txt%></b></p>
		</blockquote>

		<hr noshade size="1" color="#C0C0C0">

		<p>Probably you did not fill in	all fields correctly, or you may have forgotten to fill 
		in some of the fields.</p>

		<p>If you activate Javascript in your browser, you get feedback immediately 
		before submiting.</p>

		<p>Please press the <a href="javascript:history.back()"><b>back</b></a>-button 
		in your browser, check your settings and then retry.</p>

<!--#include file="includes/footer.asp" -->
