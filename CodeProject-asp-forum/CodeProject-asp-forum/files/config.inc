<%
' ###########################################################################
' #
' # file:
' # 	config.inc
' #
' # description:
' # 	configuration.
' #
' # version:
' # 	1.00  1999-12-10 Uwe Keim   file created.
' #
' ###########################################################################


' ////////////////////////////////////////////////////////////////////////////
' // mail settings.


const MAIL_SVR  = "mail.imos.net"				' the mailserver.
const MAIL_PORT = "25"


' ////////////////////////////////////////////////////////////////////////////
' // color settings.

const COLOR_SELECTED_BG    = "#53B398"	' background color of the headline of a selected article.
const COLOR_SELECTED_FG    = "#000000"	' fontcolor of the headline of a selected article.

const COLOR_CONTENT_BG     = "#B7DFD5"	' background color of the content(body) of a selected article.
const COLOR_CONTENT_FG     = "#0000FF"	' fontcolor of the content(body) of a selected article.

const COLOR_NONSELECTED_BG = "#EDF8F4"	' background color of the headline of a not-selected article.
const COLOR_NONSELECTED_FG = "#000000"	' foreground color of the headline of a not-selected article.

const COLOR_HEADER_BG	   = "#B7DFD5"	' background color of the headline "subject-author-date"

const COLOR_REPLY_BG	   = "#00896E"	' background color of the reply-header
const COLOR_REPLY_FONT	   = "#FFFFFF"	' font color of the reply-header


' font variables *************************************************************


const FONT_REPLY_FORM1 = "<font face=""Verdana, Arial, Helvetica, sans-serif"" size=""1"" color=""#000000"">"
const FONT_REPLY_FORM2 = "<font face=""Verdana, Arial, Helvetica, sans-serif"" size=""2"" color=""#000000"">"
const FONT_REPLY_FORM3 = "<font face=""Verdana, Arial, Helvetica, sans-serif"" size=""3"" color=""#000000"">"
const FONT_REPLY_FORM4 = "<font face=""Verdana, Arial, Helvetica, sans-serif"" size=""4"" color=""#000000"">"

const FONT1 = "<font face=""Verdana, Arial, Helvetica, sans-serif"" size=""1"" color=""#000000"">"
const FONT2 = "<font face=""Verdana, Arial, Helvetica, sans-serif"" size=""2"" color=""#000000"">"
const FONT3 = "<font face=""Verdana, Arial, Helvetica, sans-serif"" size=""3"" color=""#000000"">"
const FONT4 = "<font face=""Verdana, Arial, Helvetica, sans-serif"" size=""4"" color=""#000000"">"



' ****************************************************************************


' ////////////////////////////////////////////////////////////////////////////
' // forum-database configuration.

' database connection string.
function DB
	DB = "Provider=Microsoft.Jet.OLEDB.4.0;" &_
		"Persist Security Info=False;" &_
		"Data Source=" &Server.MapPath("database/forum.mdb")
end function

const DB_ID = ""		' database user-id
const DB_PW = ""		' and password.

' password used for switching the forum into the admin mode.
const ADMIN_PW = "12345"


' ////////////////////////////////////////////////////////////////////////////

const ANSWERTEXT	 = "Diese Nachricht wurde automatisch vom Owener Forum erzeugt"
const BASICURL	 = "http://localhost"

%>
