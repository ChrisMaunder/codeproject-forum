<%
' ###########################################################################
' #
' # file:
' # 	common.inc
' #
' # description:
' # 	Common constants and routines for use throughout a site.
' #
' # version:
' #		2000-05-31 C Maunder  Added datetimeToSql
' # 	2000-04-27 C Maunder  Modified for use with published forum
' # 	2000-01-30 Uwe Keim   added "assert" function.
' # 	2000-01-02 Uwe Keim   file created from locafx.inc
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

' ///////////////////////////////////////////////////////////////////////////
' // Constants.

Dim QUOT, OPENASP, CLOSEASP
QUOT = CHR(34)
OPENASP = "<" & CHR(37)
CLOSEASP = CHR(37) & ">"

const adOpenForwardOnly = 0
const adOpenDynamic     = 2
const adOpenStatic      = 3
const adLockOptimistic  = 3


' ///////////////////////////////////////////////////////////////////////////
' // diagnostic/debugging functions.

' if "condition" is false then an error is raised.
sub assert( byval condition )
	if not CBool(condition) then
		Err.Raise 10000, "", "assertion failed", "", ""
	end if
end sub

' ///////////////////////////////////////////////////////////////////////////
' // helper functions.

' delivers url information of the current page.
function myselfComplete
	dim protocol
	if LCase(Request.ServerVariables("HTTPS"))="on" then
		protocol = "https://"
	else
		protocol = "http://"
	end if

	myselfComplete = protocol & _
		Request.ServerVariables("HTTP_HOST") & _
		Request.ServerVariables("HTTP_URL")
end function

' delivers url information of the current page.
function myself
	myself = Request.ServerVariables("SCRIPT_NAME")
end function

' generates a random number.
function getRndNr
	Randomize Time
	getRndNr = CStr(CLng(Rnd*CDbl(1000000000)))
end function

' formats a date to be inserted into sql.
' returns a string.
' format: mm/dd/yyyy.
function dateToSql( dt )
	dim dd, mm, yyyy

	dd   = CStr( DatePart("d"   , dt) )
	mm   = CStr( DatePart("m"   , dt) )
	yyyy = CStr( DatePart("yyyy", dt) )

	dateToSql = mm& "/" &dd& "/" &yyyy
end function

' formats a date to be inserted into sql.
' returns a string.
' format: mm/dd/yyyy.
function datetimeToSql( dt )
	dim dd, mm, yyyy, mn, hr

	dd   = CStr( DatePart("d"   , dt) )
	mm   = CStr( DatePart("m"   , dt) )
	yyyy = CStr( DatePart("yyyy", dt) )
	mn   = CStr( DatePart("n"   , dt) )
	hr   = CStr( DatePart("h"   , dt) )
	if mn < 10 Then mn = "0" & mn

	datetimeToSql = mm& "/" &dd& "/" &yyyy & " " & hr & ":" & mn
end function


' Outputs the date as a string
' DateVal is the date (returned from Date())
' Abbrev - if True, date is like is 22 Feb 2000, otherwise Tuesday, 22 February 2000
Function DateString(DateVal, Abbrev)
Dim intDate, strDay, strMonth, strYear

	if Not IsDate(DateVal) Then
		DateString = DateVal
		exit function
	End if
	
    intDate  = Day(DateVal)
    strYear  = Year(DateVal)
    
    if Abbrev Then
        strMonth = MonthName(Month(DateVal), True)
        DateString = intDate & " " & MonthName(Month(DateVal), True) & " " & strYear
    Else
        strMonth = MonthName(Month(DateVal))
        strDay   = WeekDayName(WeekDay(DateVal), False, vbSunday)

        Dim suffix
        suffix   = "th"
        Select Case intDate
            case 1,21,31 : suffix = "st"
            case 2,22    : suffix = "nd"
            case 3,23    : suffix = "rd"
        End Select

        DateString  = strDay & " " & intDate & suffix & " " & strMonth & ", " & strYear
    End If
End Function


' Outputs the date as a string
' DateVal is the date (returned from Now())
Function DateTimeString(DateTimeVal, Abbrev)
  
    Dim intMinute, intHour, intDay, strMonth, strYear

	if Not IsDate(DateTimeVal) Then
		DateTimeString = DateTimeVal
		exit function
	End if
	
	intMinute = Minute(DateTimeVal)
	if intMinute < 10 Then intMinute = "0" & CStr(intMinute)
	intHour   = Hour(DateTimeVal) 

    if Abbrev Then
        intDay    = Day(DateTimeVal)
        strMonth  = MonthName(Month(DateTimeVal), True)
        strYear   = Right(Year(DateTimeVal),2)
        DateTimeString = intHour& ":" & intMinute & " " & intDay & " " & strMonth & " " & strYear
    Else
        DateTimeString = intHour& ":" & intMinute & " " & DateString(DateTimeVal, False)
    End If    
        
End Function
' ///////////////////////////////////////////////////////////////////////////
%>
