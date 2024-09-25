<%
' ###########################################################################
' #
' # file:
' # 	config.inc
' #
' # description:
' # 	Forum configuration file. This file allows you to set things such as
' #     the location of files used in the script, as well as strings used
' #     in the scripts.
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

' ////////////////////////////////////////////////////////////////////////////
' // Text.

const WELCOME   = "Welcome to the Code Project discussion boards"


' ////////////////////////////////////////////////////////////////////////////
' // path settings.

' these settings are necessary to point all URLs to the forum files.
' adjust them accordingly!

' virtual path to forum base.
' always WITH slash at end.
Dim VP_FORUM, VP_FORUM_DB

' virtual path to forum base. Always WITH slash at end!
VP_FORUM = BASE_DIR & "forum/"

' virtual path to forum database file
VP_FORUM_DB = BASE_DIR & "forum/data/forum.mdb"


' ////////////////////////////////////////////////////////////////////////////
' // passwords.

const DB_ID = ""				' database user-id
const DB_PW = ""				' and password.
const ADMIN_PW = "12345678"		' admin mode password for forum


' ////////////////////////////////////////////////////////////////////////////
' // the addresses of the pages.

' when you change the name and/or location of the real files,
' you have to modify the asp filenames in the following constants.

' visual pages.
const PAGE_FORUM_ADMIN_MODIFY        = "admin_modify.asp"
const PAGE_FORUM_ADMIN_MODIFYFORUM   = "admin_modifyforum.asp"

const PAGE_FORUM_OWNER_MODIFY        = "owner_modify.asp"
const PAGE_FORUM_OWNER_MODIFYPW      = "owner_modify_pw.asp"
const PAGE_FORUM_OWNER_DELETEPW      = "owner_delete_pw.asp"

const PAGE_FORUM_USER_MAIL           = "user_mail.asp"
const PAGE_FORUM_USER_NEW            = "user_new.asp"
const PAGE_FORUM_USER_REPLY          = "user_reply.asp"

' processing pages.
const PAGE_FORUM_DOFILTERMESSAGES    = "app/do_filtermessages.asp"
const PAGE_FORUM_DOFILTERKEYWORDS    = "app/do_filterkeywords.asp"

const PAGE_FORUM_ADMIN_DODELETE      = "app/admin_do_delete.asp"
const PAGE_FORUM_ADMIN_DOMODIFY      = "app/admin_do_modify.asp"
const PAGE_FORUM_ADMIN_DOMODIFYFORUM = "app/admin_do_modifyforum.asp"

const PAGE_FORUM_OWNER_DODELETE      = "app/owner_do_delete.asp"
const PAGE_FORUM_OWNER_DOMODIFY      = "app/owner_do_modify.asp"

const PAGE_FORUM_USER_DOMAIL         = "app/user_do_mail.asp"
const PAGE_FORUM_USER_DONEW          = "app/user_do_new.asp"
const PAGE_FORUM_USER_DOREPLY        = "app/user_do_reply.asp"

' misc pages.
const PAGE_FORUM_FAILURE             = "failure.asp"


' ///////////////////////////////////////////////////////////////////////////
' // string resources.

' insert_reply page.
const    IDS_REPLY_ERR_FIELDSMISSING = "not all fields were filled"
function IDS_REPLY_NOTIFYBODY
	IDS_REPLY_NOTIFYBODY = _
		"Answer to your message in the forum '%x':" &vbCrLf& _
		""   &vbCrLf& _
		"%x" &vbCrLf& _
		""   &vbCrLf& _
		"---------------------------------------------------------------" &vbCrLf& _
		"This message was created with the CodeProject forum" &vbCrLf& _
		"http://www.codeproject.com" &VP_FORUM &vbCrLf& _
		"" &vbCrLf
end function
function IDS_REPLY_NOTIFYADMINBODY
	IDS_REPLY_NOTIFYADMINBODY = _
		"Answer to message in the forum '%x':" &vbCrLf& _
		""   &vbCrLf& _
		"%x" &vbCrLf& _
		""   &vbCrLf& _
		"---------------------------------------------------------------" &vbCrLf& _
		"This message was created with the CodeProject forum" &vbCrLf& _
		"http://www.codeproject.com" &VP_FORUM &vbCrLf& _
		"" &vbCrLf
end function

' send_mail page.
const    IDS_MAIL_ERR_FIELDSMISSING = "not all fields were filled"
function IDS_MAIL_BODY
	IDS_MAIL_BODY = _
		"Answer to your message in the forum '%x':" &vbCrLf& _
		""   &vbCrLf& _
		"%x" &vbCrLf& _
		""   &vbCrLf& _
		"---------------------------------------------------------------" &vbCrLf& _
		"This message was created with the CodeProject forum" &vbCrLf& _
		"http://www.codeproject.com" &VP_FORUM  &vbCrLf& _
		"" &vbCrLf
end function

' insert_modify page.
const    IDS_MODIFY_ERR_FIELDSMISSING = "not all fields were filled"

' modify_admin page.
const    IDS_ADMIN_ERR_FIELDSMISSING = "not all fields were filled"

' insert_new page.
const    IDS_NEW_ERR_FIELDSMISSING = "not all fields were filled"
function IDS_NEW_NOTIFYADMINBODY
	IDS_NEW_NOTIFYADMINBODY = _
		"New message in the forum '%x':" &vbCrLf& _
		""   &vbCrLf& _
		"%x" &vbCrLf& _
		""   &vbCrLf& _
		"---------------------------------------------------------------" &vbCrLf& _
		"This message was created with the CodeProject forum" &vbCrLf& _
		"http://www.codeproject.com" &VP_FORUM &vbCrLf& _
		"" &vbCrLf
end function

' javascript alert messages (used on multiple formular-pages).
const    IDS_JS_NEEDSUBJECT         = "Please enter a subject"
const    IDS_JS_NEEDMSG             = "Please enter a message"
const    IDS_JS_NEEDAUTHOR          = "Please enter your name"
const    IDS_JS_NEEDEMAIL           = "Please enter your e-mail address"
const    IDS_JS_NEEDFORUMNAME       = "Please enter a name"

' main.inc page.
const    IDS_FORUM_LIST_COLSUBJECT        = "Subject"
const    IDS_FORUM_LIST_COLAUTHOR         = "Author"
const    IDS_FORUM_LIST_COLDATE           = "Date"

const    IDS_FORUM_LIST_ADMINFORUM        = "Administer this forum"
const    IDS_FORUM_LIST_NEW               = "New message"
const    IDS_FORUM_LIST_REPLY             = "Reply"
const    IDS_FORUM_LIST_MAIL              = "Email author of message"
const    IDS_FORUM_LIST_OWNERMODIFY       = "Modify"
const    IDS_FORUM_LIST_OWNERDELETE       = "Delete"

const    IDS_FORUM_LIST_ADMINMODIFY       = "Modify this message"
const    IDS_FORUM_LIST_ADMINDEL          = "Delete this message"
const    IDS_FORUM_LIST_ADMINDELRECURSIVE = "Delete this message and all child messages"

const    IDS_FORUM_NEW_TITLE              = "Add a new message to the discussions"
const    IDS_FORUM_REPLY_TITLE            = "Reply to this current thread"
const    IDS_FORUM_MAIL_TITLE             = "Email a reply to the author of this message"
const    IDS_FORUM_FIRST_TITLE            = "Go to the first page of messages"
const    IDS_FORUM_PREV_TITLE             = "Go to the previous page of messages"
const    IDS_FORUM_NEXT_TITLE             = "Go to the next page of messages"
const    IDS_FORUM_LAST_TITLE             = "Go to the last page of messages"

' misc messages.
const    IDS_FORUM_WRONGPASSWORD          = "Wrong password"


' ////////////////////////////////////////////////////////////////////////////
%>
