<%
' ###########################################################################
' #
' # file:
' # 	Lastvisit.asp
' #
' # description:
' # 	Last date visited by viewer.
' #
' # version:
' # 	2000-01-02 C Maunder   file created from locafx.inc
' #
' # copyright:
' #		Written by Chris Maunder <cmaunder@mail.com>
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

' Date of last visit
Dim VisitDT
VisitDT = Session("LastVisit")

' If no date in Session object, then request it from the cookies
if VisitDT = "" or Not IsDate(VisitDT) Then 
	VisitDT = Request.Cookies("LastVisit")
	
	' If no previous visit date set then set it as a long time ago
	if VisitDT = "" or Not IsDate(VisitDT) Then VisitDT = CDate("1/1/1999 12:00")
	Session("LastVisit") = VisitDT					' Store in session
	
	Response.Cookies("LastVisit") = Now()			' Store today's date for next time
	Response.Cookies("LastVisit").expires = Date()+180	
End If
%>