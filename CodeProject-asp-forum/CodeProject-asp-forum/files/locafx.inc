<!--#include file="config.inc"-->
<!--#include file="forum.inc"-->
<!--#include file="email.inc"-->

<%
' ###########################################################################
' #
' # file:
' # 	locafx.inc
' #
' # description:
' # 	common local things.
' #
' # version:
' # 	1.00  1999-12-08 Uwe Keim   file created.
' #
' ###########################################################################

	   
' ///////////////////////////////////////////////////////////////////////////
' // helper functions.

' helper founction to format the content of an article.
' replaces several smilies by graphical representations.
' NOTE: these images were "lend" from the lionhead forum
'       (www.lionhead.co.uk), use at your own risk!
function fmtContent( text )
	text = fmtML( text )

'	text = Replace( text, ":-)", "<img src=""data/smiley_smile.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ":)" , "<img src=""data/smiley_smile.gif"" align=""absmiddle"" border=""0"">" )

'	text = Replace( text, ":-(", "<img src=""data/smiley_frown.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ":(" , "<img src=""data/smiley_frown.gif"" align=""absmiddle"" border=""0"">" )

'	text = Replace( text, ":-O", "<img src=""data/smiley_redface.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ":-o", "<img src=""data/smiley_redface.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ":-0", "<img src=""data/smiley_redface.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ":O" , "<img src=""data/smiley_redface.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ":o" , "<img src=""data/smiley_redface.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ":0" , "<img src=""data/smiley_redface.gif"" align=""absmiddle"" border=""0"">" )

'	text = Replace( text, ":-D", "<img src=""data/smiley_biggrin.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ":D" , "<img src=""data/smiley_biggrin.gif"" align=""absmiddle"" border=""0"">" )

'	text = Replace( text, ";-)", "<img src=""data/smiley_wink.gif"" align=""absmiddle"" border=""0"">" )
'	text = Replace( text, ";)" , "<img src=""data/smiley_wink.gif"" align=""absmiddle"" border=""0"">" )

	fmtContent = text
end function

' delivers url information of the current page.
private function myselfComplete
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
private function myself
	myself = Request.ServerVariables("SCRIPT_NAME")
end function

' formats a multiline (ML) string.
' replaces '\n' with '<br>'.
private function fmtML( in_str )
	if IsNull(in_str) then
		fmtML = ""
		exit function
	end if 

	dim str
	if in_str<>"" then
		str = Replace( in_str, vbCr+vbLf, vbCr )
		str = Replace( str   , vbLf     , vbCr )
		str = Replace( str   , vbCr     , "<br>" )

		fmtML = str
	else
		fmtML = in_str
	end if
end function

' as CString::Delete. returns the new string.
function Delete( str, index, count )
	dim l,r
	l = Left ( str, index-1 )
	r = Right( str, Len(str)-(index+count)+1 )

	Delete = l & r
end function
%>

<%
sub trace( str )
	Response.Write str
end sub

sub traceX( str )
	trace str
	Response.End
end sub
%>

<%
' ***************************************************************************
' executable code.

' creates an instance of the forum class on every page.
dim fh
set fh = new Forum
fh.init
%>
