<%
' ###########################################################################
' #
' # file:
' # 	string.inc
' #
' # description:
' # 	common local things.
' #
' # version:
' #   2000-02-21 C Maunder  Tweaked
' # 	2000-01-04 Uwe Keim   added fmt().
' # 	2000-01-02 Uwe Keim   file created from locafx.inc
' #
' ###########################################################################


' ///////////////////////////////////////////////////////////////////////////
' // string helper functions.

' Replaces malicous text with harmless equivalent
function fmtFilter( text )

	if IsNull(text) then
		fmtFilter = ""
		exit function
	end if 
	
	' Disable certain HTML
	text = Replace( text, OPENASP     , "&lt;%" )
	text = Replace( text, CLOSEASP    , "%&gt;" )
	text = Replace( text, "<script"   , "&lt;script", 1, -1, 1)
	text = Replace( text, "</script"  , "&lt;/script", 1, -1, 1)
	text = Replace( text, "<input"    , "&lt;input", 1, -1, 1)
	text = Replace( text, "</input"   , "&lt;/input", 1, -1, 1)
	text = Replace( text, "<object"   , "&lt;object", 1, -1, 1)
	text = Replace( text, "</object"  , "&lt;/object", 1, -1, 1)
	text = Replace( text, "<applet"   , "&lt;applet", 1, -1, 1)
	text = Replace( text, "</applet"  , "&lt;/applet", 1, -1, 1)
	text = Replace( text, "<form"  , "&lt;form", 1, -1, 1)
	text = Replace( text, "</form"  , "&lt;/form", 1, -1, 1)
	text = Replace( text, "<table"  , "&lt;table", 1, -1, 1)
	text = Replace( text, "</table"  , "&lt;/table", 1, -1, 1)
	text = Replace( text, "<tr"  , "&lt;tr", 1, -1, 1)
	text = Replace( text, "</tr"  , "&lt;/tr", 1, -1, 1)
	text = Replace( text, "<td"  , "&lt;td", 1, -1, 1)
	text = Replace( text, "</td"  , "&lt;/td", 1, -1, 1)
	text = Replace( text, "<select"  , "&lt;select", 1, -1, 1)
	text = Replace( text, "</select"  , "&lt;/select", 1, -1, 1)
	text = Replace( text, "<option"  , "&lt;option", 1, -1, 1)
	text = Replace( text, "</option"  , "&lt;/option", 1, -1, 1)

	' Disable any offensive words if you wish
	' ...

	fmtFilter = text
end function

' helper function to format the content of an article.
' replaces several smilies by graphical representations.
' NOTE: these images were "lend" from the lionhead forum
'       (www.lionhead.co.uk), use at your own risk!
function fmtContent( text )

	if IsNull(text) then
		fmtContent = ""
		exit function
	end if 
	
	text = fmtFilter(text)	' Filter out malcious stuff
	text = fmtML(text)	' Format line breaks

	text = Replace( text, ":-)"       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_smile.gif""    align=""absmiddle"" border=""0"">" )
	text = Replace( text, ":)"        , "<img src="""&VP_SCRIPT_IMAGES&"smiley_smile.gif""    align=""absmiddle"" border=""0"">" )

	text = Replace( text, ":-("       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_frown.gif""    align=""absmiddle"" border=""0"">" )
	text = Replace( text, ":("        , "<img src="""&VP_SCRIPT_IMAGES&"smiley_frown.gif""    align=""absmiddle"" border=""0"">" )

	text = Replace( text, ":-O"       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_redface.gif""  align=""absmiddle"" border=""0"">" )
	text = Replace( text, ":-o"       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_redface.gif""  align=""absmiddle"" border=""0"">" )
	text = Replace( text, ":-0"       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_redface.gif""  align=""absmiddle"" border=""0"">" )
	text = Replace( text, ":O "       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_redface.gif""  align=""absmiddle"" border=""0"">" )
	text = Replace( text, ":o "       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_redface.gif""  align=""absmiddle"" border=""0"">" )
	text = Replace( text, ":0 "       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_redface.gif""  align=""absmiddle"" border=""0"">" )

	text = Replace( text, ":-D "      , "<img src="""&VP_SCRIPT_IMAGES&"smiley_biggrin.gif""  align=""absmiddle"" border=""0"">" )
	text = Replace( text, ":D "       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_biggrin.gif""  align=""absmiddle"" border=""0"">" )

	text = Replace( text, ";-)"       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_wink.gif""     align=""absmiddle"" border=""0"">" )
	text = Replace( text, ";)"        , "<img src="""&VP_SCRIPT_IMAGES&"smiley_wink.gif""     align=""absmiddle"" border=""0"">" )

	text = Replace( text, ";-p"       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_tongue.gif""   align=""absmiddle"" border=""0"">" )
	text = Replace( text, ";-P"       , "<img src="""&VP_SCRIPT_IMAGES&"smiley_tongue.gif""   align=""absmiddle"" border=""0"">" )
	text = Replace( text, ";p"        , "<img src="""&VP_SCRIPT_IMAGES&"smiley_tongue.gif""   align=""absmiddle"" border=""0"">" )
	text = Replace( text, ";P"        , "<img src="""&VP_SCRIPT_IMAGES&"smiley_tongue.gif""   align=""absmiddle"" border=""0"">" )

	'text = Replace( text, ":cool:"    , "<img src="""&VP_SCRIPT_IMAGES&"smiley_cool.gif""     align=""absmiddle"" border=""0"">" )
	'text = Replace( text, ":rolleyes:", "<img src="""&VP_SCRIPT_IMAGES&"smiley_rolleyes.gif"" align=""absmiddle"" border=""0"">" )
	'text = Replace( text, ":mad:"     , "<img src="""&VP_SCRIPT_IMAGES&"smiley_mad.gif""      align=""absmiddle"" border=""0"">" )
	'text = Replace( text, ":eek:"     , "<img src="""&VP_SCRIPT_IMAGES&"smiley_eek.gif""      align=""absmiddle"" border=""0"">" )
	'text = Replace( text, ":confused:", "<img src="""&VP_SCRIPT_IMAGES&"smiley_confused.gif"" align=""absmiddle"" border=""0"">" )

	fmtContent = text
end function

' works like the sprintf-function in C++.
' takes a string with format characters and an array
' to expand.
'
' the format characters are always "%x", independ of the
' type.
'
' usage example:
'	dim str
'	str = fmt( "hello, Mr. %x, today's date is %x.", Array("Miller",Date) )
'	response.Write str
function fmt( str, args )
	dim res		' the result string.
	res = ""

	dim pos		' the current position in the args array.
	pos = 0

	dim i
	for i = 1 to Len(str)
		' found a fmt char.
		if Mid(str,i,1)="%" then
			if i<Len(str) then
				' normal percent.
				if Mid(str,i+1,1)="%" then
					res = res & "%"
					i = i + 1

				' expand from array.
				elseif Mid(str,i+1,1)="x" then
					res = res & CStr(args(pos))
					pos = pos+1
					i = i + 1
				end if
			end if

		' found a normal char.
		else
			res = res & Mid(str,i,1)
		end if
	next

	fmt = res
end function

function fmtFilterML( in_str )
	Dim str
	str = fmtFilter(in_str)
	fmtFilterML = fmtML(str)
end function

' formats a multiline (ML) string.
' replaces '\n' with '<br>'.
function fmtML( in_str )
	if IsNull(in_str) then
		fmtML = ""
		exit function
	end if 

	dim str
	if in_str<>"" then
		str = Replace( in_str, vbCrLf, vbCr )
		str = Replace( str   , vbLf  , vbCr )
		str = Replace( str   , vbCr  , "<br>" )

		fmtML = str
	else
		fmtML = in_str
	end if
end function

' as CString::Delete. returns the new string.
function delete( str, index, count )
	dim l,r
	l = Left ( str, index-1 )
	r = Right( str, Len(str)-(index+count)+1 )

	delete = l & r
end function


' ///////////////////////////////////////////////////////////////////////////
%>
