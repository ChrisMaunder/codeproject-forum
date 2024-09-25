<%
' ###########################################################################
' #
' # file:
' # 	forum.inc
' #
' # description:
' # 	This file contains the definition of the forum class.
' # 	This class is a wrapper class for the main forum ActiveX control, and is 
' # 	the main communication point that contains all forum-related functionality. 
' # 	You never communicate with the forum ActiveX control directly, 	but always 
' # 	indirectly via this class.
' #
' # version:
' #     2000-06-01 C Maunder  Modified setDateFilterStart to use filter type
' #                           Modified getUriUserMailCur and getUriUserReplyCur
' #                           to accept article ID parameter. Added constants.
' #                           GetURiMain adds in anchor point. Added GetURIRow.
' # 	2000-04-06 C Maunder  Added support for messages-per-page and thread 
' #                           expansion. Added getSelectedArticleRsCount, Extra 
' #                           comments
' # 	2000-02-06 Uwe Keim   extended for password support.
' # 	                      rearanged uri functions.
' # 	2000-01-12 Uwe Keim   improved the gerUriXxx functions.
' # 	2000-01-07 Uwe Keim   getUriAdminForum() and related functions added.
' # 	2000-01-01 Uwe Keim   getArticleAnchor() added.
' # 	1999-12-15 Uwe Keim   createForum() added.
' # 	1999-12-10 Uwe Keim   commented heavily.
' # 	1999-12-08 Uwe Keim   file created.
' #
' ###########################################################################
  
' ///////////////////////////////////////////////////////////////////////////
' // Constants.

' "View" options. Other view modes will be added
const expandNone            = "0"
const expandCollapse        = "1"	' NOT YET IMPLEMENTED
const expandPreview         = "2"

' "View messages since..." filter options
const datefilterLastVisit   = "0"
const datefilterLastDay     = "1"
const datefilterLastWeek    = "2"
const datefilterLastMonth   = "3"
const datefilterLastQuarter = "4"
const datefilterLastHalf    = "5"
const datefilterLastYear    = "6"
const datefilterAll         = "100"

' ///////////////////////////////////////////////////////////////////////////
' // helper class for forum.

' this class is the main communication point that contains all forum-related
' functionality. you never communicate with the forum-active-x directly, 
' but always indirectly with this class.

class Forum

	' ---------------------------------------------
	' constructor.

	public sub Class_Initialize()
		set m_Conn = openDb
		set m_Ax   = Server.CreateObject("AspForum.Forum2.1")

		m_Ax.DbConnStr = DB(VP_FORUM_DB)
		m_Ax.DbID      = DB_ID
		m_Ax.DbPW      = DB_PW

		' read in all parameters from the current page's url.
		fromUrl( myselfComplete )

		' the main page where this forum is displayed.
		if m_Ax.Value("main")="" then
			m_Ax.Value("main") = myself
		end if

		' insert date-filters into active-x.
		setDateFilterStart m_Ax.Value("df"), Session("LastVisit")
		m_Ax.FilterEndDate   = dateToSQL(Now+1000)

		' insert keyword-filters into active-x.
		m_Ax.FilterKeywords  = m_Ax.Value("kw")
	end sub

	' ---------------------------------------------
	' destructor.

	public sub Class_Terminate()
		m_Conn.Close
		set m_Conn = nothing
		set m_Ax = nothing
	end sub

	' ---------------------------------------------
	' public functions dealing with the CURRENT forum.

	' this functions "open" a current forum. all articles
	' are read into memory and sorted in correct order.
	'
	' an internal "file pointer" is positioned right at the
	' beginning of the list. call moveNext() to advance
	' this pointer, until endOfList()
	'
	' you can then call the getCurXxx() functions
	' ('Cur' for current) which all apply to the article
	' at the current file pointer position.
	public sub readArticles( forum_id )
		m_Ax.value("forumid") = forum_id
		m_Ax.ForumID = CLng(forum_id)
		m_Ax.ReadArticles DB(VP_FORUM_DB), DB_ID, DB_PW
	end sub
	
	' returns the total number of articles for
	' a specified forum.
	public function getCommentCount( forum_id )
		dim rs
		set rs = m_Conn.Execute( "SELECT COUNT(*) FROM Article WHERE ForumID=" &forum_id )

		if not (rs.BOF and rs.EOF) then
			getCommentCount = rs(0)
		else
			getCommentCount = 0
		end if

		rs.close
		set rs = nothing
	end function
	
	' returns the total number of articles for
	' a specified forum.
	public function getNewCommentCount( forum_id, StartDate )
		dim rs
		set rs = m_Conn.Execute( "SELECT COUNT(*) FROM Article WHERE ForumID=" & forum_id &_
                        		 " AND (Date>=#" & StartDate & "#)")

		if not (rs.BOF and rs.EOF) then
			getNewCommentCount = rs(0)
		else
			getNewCommentCount = 0
		end if

		rs.close
		set rs = nothing
	end function
	
	' Set the first record to retrieve
	public sub SetRetrieveStart(start)
	    m_Ax.RetrieveStart = start
	end sub

    ' Set the number of records to retrieve
    public sub SetRetrieveCount(count)
        m_Ax.RetrieveCount = count
    end sub

	' advance the file pointer to the next article.
	public sub moveNext()
		m_Ax.moveNext
	end sub

	' check whether the file pointer is beyond the
	' last article.
	public function endOfList()
		endOfList = m_Ax.EndOfList
	end function

	' checks, whether the forum is currently in admin mode.
	' in admin mode, you can modify and delete articles.
	public function isInAdminMode()
		isInAdminMode = false

		if Request("ad")<>"" then
			if CStr(Request("ad"))=CStr(ADMIN_PW) then
				isInAdminMode = true
			end if
		end if
	end function

	' checks whether the article at the current file pointer
	' position has child articles.
	public function hasChilds()
		hasChilds = m_Ax.hasChilds
	end function

	' returns the article-id of the article 
	' at the current file pointer position.
	public function getCurID()
		getCurID = m_Ax.getCurID
	end function

	' gets the number of child-articles (direct and indirect)
	' of the article at the current file pointer position (including
	' this article).
	public function getCurArticleCount()
		getCurArticleCount = m_Ax.GetCurArticleCount
	end function

	' returns the indent-level of the article at 
	' the current file pointer position.
	' returns a number, starting at zero (or was it 1???).
	public function getCurIndentLevel()
		getCurIndentLevel = m_Ax.getCurIndentLevel
	end function

	' ---------------------------------------------
	' public misc functions.

	' retrieves the number of articles per page.
	public function getArticlesPerPage()
		getArticlesPerPage = m_Ax.value("app")
	end function

	' sets the number of articles per page.
	public sub setArticlesPerPage( ArticlesPerPage )
		m_Ax.value("app") = ArticlesPerPage
	end sub

	' retrieves the type of thread view.
	public function getExpandedView()
		getExpandedView = m_Ax.value("exp")
	end function

	' sets the type of thread view.
	public sub setExpandedView( bExpanded )
		m_Ax.value("exp") = bExpanded
	end sub

	' retrieves first row to display.
	public function getFirstRow()
		getFirstRow = m_Ax.value("fr")
	end function

	' sets first row to display.
	public sub setFirstRow( first_row )
		m_Ax.value("fr") = first_row
	end sub

	' retrieves the date-filters start date.
	public function getDateFilterStart()
		getDateFilterStart = m_Ax.FilterStartDate
	end function

	' retrieves the date-filters start date type.
	public function getDateFilterStartType()
		getDateFilterStartType = m_Ax.Value("df")
	end function

	' sets the date-filters start date.
	public sub setDateFilterStart( DateFilterType, lastvisit )
	
	    if DateFilterType = datefilterLastVisit and Not IsDate(lastvisit) then
	        DateFilterType = datefilterAll
	    End If
	    
	    Dim StartDate
	    Select case DateFilterType
	    
	        case datefilterLastVisit
	            StartDate = LastVisit
	            
	        case datefilterLastDay
	            StartDate = Now-1
	            
	        case datefilterLastWeek
	            StartDate = Now-7
	            
	        case datefilterLastMonth
	            StartDate = Now-30
	            
	        case datefilterLastQuarter
	            StartDate = Now-90
	            
	        case datefilterLastHalf
	            StartDate = Now-180
	            
	        case datefilterLastYear
	            StartDate = Now-365
	            
	        case else
	            StartDate = #1/1/1999#
	        
	    End Select
	        
		m_Ax.Value("df") = DateFilterType
		m_Ax.FilterStartDate = datetimeToSql(StartDate)
	end sub

	' retrieves the date-filters start date.
	public function getKeywordsFilter()
		getKeywordsFilter = m_Ax.value("kw")
	end function

	' sets the the keyword filter.
	public sub setKeywordsFilter( fltr )
		m_Ax.value("kw") = fltr
	end sub

	' check whether the a given password is valid for
	' a given article id.
	public function isArticlePwValid( message_id, password )
		' empty password never valid.
		if password="" then
			isArticlePwValid = false

		else
			dim rs
			set rs = m_Conn.Execute("SELECT * FROM Article " & _
				"WHERE ID=" & message_id & " AND " & _
				"Password='" & password & "'")
			
			if rs.Bof and rs.Eof then
				isArticlePwValid = false
			else
				' check case.
				if rs("Password")=password then
					isArticlePwValid = true
				else
					isArticlePwValid = false
				end if
			end if
		end if
	end function

	' get the id of a forum from its short-name.
	' returns null if not found.
	' you may need to strengthen the sql query (the 'LIKE')
	' when you have forums with similar names.
	public function getForumId( forum_name )
		dim rs
		set rs = m_Conn.Execute( "SELECT * FROM Forum " & _
			"WHERE Shortname LIKE '%" &forum_name& "%'" )

		if not (rs.BOF and rs.EOF) then
			getForumId = rs("ID")
		else
			getForumId = null
		end if
		
		rs.close
		set rs = nothing
	end function

	' dto. as getForumId(), just from long name.
	public function getForumIdFromLongName( forum_name )
		dim rs
		set rs = m_Conn.Execute( "SELECT * FROM Forum " & _
			"WHERE Name = '" &forum_name& "'" )

		if not (rs.BOF and rs.EOF) then
			getForumIdFromLongName = rs("ID")
		else
			getForumIdFromLongName = null
		end if

		rs.close
		set rs = nothing
	end function

	' returns the long name of a forum, given the id of a forum.
	public function getForumName( forum_id )
		dim rs
		set rs = m_Conn.Execute( "SELECT * FROM Forum WHERE ID=" &forum_id )
		getForumName = rs("Name")
		rs.close
		set rs = nothing		
	end function

	' returns the long name of a forum, given the id of a forum.
	public sub getForumDetails( forum_id, forum_name, forum_desc )
		dim rs
		set rs = m_Conn.Execute( "SELECT * FROM Forum WHERE ID=" &forum_id )
		forum_name = rs("Name")
		forum_desc = rs("Description")
		rs.close
		set rs = nothing		
	end sub

	' gets the recordset of an article, given the id of the article.
	public function getArticleRs( article_id )
		set getArticleRs = m_Conn.Execute( _
			"SELECT * FROM Article WHERE ID=" &article_id )
	end function

	' gets the recordset of an article, given a forum ID.
	public function getSelectedArticleRs( forum_id, StartDate, EndDate, KeyWords )
	    Dim strSQL
	    strSQL = "SELECT * FROM Article WHERE ForumID=" & forum_id
	    
	    if StartDate <> "" Then strSQL = strSQL & " AND (Date>=#" & StartDate & "#)"
	    if EndDate   <> "" Then strSQL = strSQL & " AND (Date<=#" & EndDate & "#)"
	    if KeyWords  <> "" Then
	        strSQL = strSQL & " AND (Subject LIKE '%" & KeyWords & "%' OR " &_
			                        "AuthorName LIKE '%" & KeyWords & "%' OR " &_
			                        "Text LIKE '%" & KeyWords & "%')"
        End If
        			                        
		set getArticleRs = m_Conn.Execute( strSQL )

	end function
	
	' gets the recordset of an article, given a forum ID.
	public function getSelectedArticleRsCount( forum_id, StartDate, EndDate, KeyWords )
	    Dim strSQL
	    strSQL = "SELECT COUNT(*) FROM Article WHERE ForumID=" & forum_id
	    
	    if StartDate <> "" Then strSQL = strSQL & " AND (Date>=#" & StartDate & "#)"
	    if EndDate   <> "" Then strSQL = strSQL & " AND (Date<=#" & EndDate & "#)"
	    if KeyWords  <> "" Then
	        strSQL = strSQL & " AND (Subject LIKE '%" & KeyWords & "%' OR " &_
			                        "AuthorName LIKE '%" & KeyWords & "%' OR " &_
			                        "Text LIKE '%" & KeyWords & "%')"
        End If
        			                        
		dim rs
		set rs = m_Conn.Execute( strSQL )
		if Not rs.eof and Not rs.bof Then
			getSelectedArticleRsCount = rs(0)
		else
            getSelectedArticleRsCount = 0
        end if
        rs.close
        set rs = nothing            
	end function


	' gets the recordset of a forum, given the id of the forum.
	public function getForumRs( forum_id )
		set getForumRs = m_Conn.Execute( _
			"SELECT * FROM Forum WHERE ID=" &forum_id )
	end function

	' gets the recordset with all forums.
	public function getForumsRs()
		set getForumsRs = m_Conn.Execute( "SELECT * FROM Forum" )
	end function

	' ·····················

	' creates a forum with a long name.
	' returns the id of the forum.
	' if the forum already exists, only its it
	' is returned.
	public function createForum( forum_long_name )
		dim rs
		set rs = m_Conn.Execute( "SELECT * FROM Forum " & _
			"WHERE Name LIKE '%" &forum_long_name& "%'" )

		if not (rs.BOF and rs.EOF) then
			createForum = rs("ID")
		else
			rs.Close

			set rs = Server.CreateObject("ADODB.Recordset")
			rs.Open "Forum", m_Conn, adOpenDynamic, adLockOptimistic

			rs.AddNew
			rs("Name")        = forum_long_name
			rs.Update
			
			createForum = rs("ID")
		end if
		rs.close
		set rs = nothing
	end function

	' insert a child-article for an already present article.
	' set 'parent_id' to zero for inserting a root article
	' for the given forum.
	public function insertChild( parent_id, forum_id, subject, author_name, _
		author_email, text, email_notify, password )

		dim rs
		set rs = Server.CreateObject("ADODB.Recordset")
		rs.Open "Article", m_Conn, adOpenDynamic, adLockOptimistic

		rs.AddNew
		rs("ParentID")    = parent_id
		rs("ForumID")     = forum_id
		rs("Subject")     = subject
		rs("AuthorName")  = author_name
		rs("AuthorEmail") = author_email
		rs("Date")        = Now()
		rs("Text")        = text
		rs("Notify")      = email_notify
		rs("Password")    = password
		rs.Update

		' mark the added article as selected.
		m_Ax.value("select") = rs("ID")

		insertChild = rs("ID")
		
		rs.close
        set rs = nothing
	end function

	' modifes an already present article.
	public sub modifyArticle( article_id, subject, author_name, _
		author_email, text, email_notify, password )

		dim rs
		set rs = Server.CreateObject("ADODB.Recordset")
		rs.Open "SELECT * FROM Article WHERE Article.ID=" &article_id, _
			m_Conn, adOpenDynamic, adLockOptimistic

		rs("Subject")     = subject
		rs("AuthorName")  = author_name
		rs("AuthorEmail") = author_email
		rs("Text")        = text
		rs("Notify")      = email_notify
		rs("Password")    = password

		rs.Update
		
		rs.close
		set rs = nothing
	end sub

	' modifies the properties of an existing forum.
	public sub modifyForum( forum_id, shortname, name, description, _
		notify_new, notify_reply )

		dim rs
		set rs = Server.CreateObject("ADODB.Recordset")
		rs.Open "SELECT * FROM Forum WHERE Forum.ID=" &forum_id, _
			m_Conn, adOpenDynamic, adLockOptimistic

		rs("Shortname")   = shortname
		rs("Name")        = name
		rs("Description") = description
		rs("NotifyNew")   = notify_new
		rs("NotifyReply") = notify_reply

		rs.Update
		
		rs.close
		set rs = nothing
	end sub

	' ·····················

	' deletes an article, given the article id of this article.
	' if "del_single" is true, only the given article is deleted,
	' its childs are moved to top-level.
	' if "del_single" is false, the given article and all its
	' childs are deleted.
	public sub deleteArticle( article_id, del_single )
		m_Ax.deleteId article_id, del_single
	end sub

	' creates the name of an achor for referencing at
	' different places. do a text-search for all callers.
	public function getArticleAnchor( anchor_name )
		getArticleAnchor = "xx" &anchor_name& "xx"
	end function

	' ---------------------------------------------
	' public and private url-parameter functions.

	' beside the core-functionality of reading articles
	' and sorting them to make up the tree, the forum active-x
	' has some functions to store mapped value-name pairs.
	' (like key-value pairs in a std::map<>).
	'
	' the active-x can url-encode these internal values and connect
	' them in order to be appended as parameters to an url.
	' in opposite, it can read the parameters from an url and
	' build up its internal map from these parameters.
	'
	' the following functions aid in this.

	' build the internal map of name-value pairs from a given url.
	private sub fromUrl( url )
		m_Ax.fromUrl url
	end sub

	' returns all values of the internal map url-encoded
	' in the form "name=value&name=value&name=value&" etc.
	' you can append this directly to an url.
	public function toUrl()
		toUrl = m_Ax.toUrl
	end function

	' the same as "toUrl" except that the value of the
	' map-entry specified by "name" is replaced by "new_value".
	public function toUrlValue( name, new_value )
		toUrlValue = m_Ax.toUrlValue(name, new_value)
	end function

	' the same as "toUrl" except that the value of the
	' map-entry specified by "name1" is replaced by "new_value1" and
	' the value of "name2" is replaced by "new_value2".
	private function toUrlValue2( name1, new_value1, name2, new_value2 )
		toUrlValue2 = m_Ax.toUrlValue2(name1, new_value1, name2, new_value2)
	end function

	' ---------------------------------------------
	' private helper functions.

	' opens the database connection.
	private function openDb()
		set openDb = Server.CreateObject("ADODB.Connection")
		openDb.Open DB(VP_FORUM_DB), DB_ID, DB_PW
	end function

	' appends an anchor-link "#xxx" to an url.
	private function appendAnchor( byval url, byval anchor_name )

		'-temp: exit until it works.
		'appendAnchor = url
		'exit function

		' remove any '?' or '&' at the end.
		while Len(url)>0 and _
			(Right(url,1)="&" or Right(url,1)="?")
			url = delete(url, Len(url), 1)
		wend
		
		' append the anchor.
		url = url& "#" &anchor_name
		appendAnchor = url
	end function

	' ---------------------------------------------
	' public uri functions.

	' these functions should be used whenever you need a <a href="...">
	' tag. instead of specifying an asp page and adding some cryptic
	' parameters, you call one of these functions.
	' with this approach, you can centralize the url-parameters
	' in one place.
	'
	' the VP_FORUM constant and the PAGE_XXX constants are defined in 'config.inc' 
	' and must be adjusted as to your needs.

	' ···························
	' visual pages.

	' url for filtering by date.
	public function getUriDoFilterMessages()
		getUriDoFilterMessages = VP_FORUM & PAGE_FORUM_DOFILTERMESSAGES &"?" & toUrl
	end function

	' url for filtering by keyword(s).
	public function getUriDoFilterByKeywords()
		getUriDoFilterByKeywords = VP_FORUM & PAGE_FORUM_DOFILTERKEYWORDS &"?" & toUrl
	end function

	' url for modifying a forum's properties.
	public function getUriAdminModifyForum( forum_id )
		getUriAdminModifyForum =  VP_FORUM& PAGE_FORUM_ADMIN_MODIFYFORUM &"?" & _
			toUrlValue("forumid",forum_id)
	end function

	public function getUriAdminModifyCur( article_id )
		getUriAdminModifyCur = VP_FORUM & PAGE_FORUM_ADMIN_MODIFY & "?" & _
			toUrlValue2("modify",article_id, "select",article_id)
	end function

	'

	public function getUriOwnerModify()
		getUriOwnerModify = VP_FORUM & PAGE_FORUM_OWNER_MODIFY & "?" & toUrl
	end function

	public function getUriOwnerModifyCurPw( message_id )
		getUriOwnerModifyCurPw = VP_FORUM & PAGE_FORUM_OWNER_MODIFYPW & "?" &_
		    toUrlValue("select", message_id)
	end function

	public function getUriOwnerDeleteCurPw( message_id )
		getUriOwnerDeleteCurPw = VP_FORUM & PAGE_FORUM_OWNER_DELETEPW & "?" &_
		     toUrlValue("select", message_id)
	end function

	'

	public function getUriUserMailCur( article_id )
		getUriUserMailCur = VP_FORUM & PAGE_FORUM_USER_MAIL & "?" &_
		    toUrlValue("select", article_id)
	end function

	public function getUriUserNew( forum_id )
		getUriUserNew = VP_FORUM & PAGE_FORUM_USER_NEW & "?" & _
			toUrlValue("forumid",forum_id)
	end function

	public function getUriUserReplyCur( article_id )
		getUriUserReplyCur = VP_FORUM & PAGE_FORUM_USER_REPLY & "?" &_
		    toUrlValue("select", article_id)
	end function

	' ···························
	' processing pages.

	public function getUriAdminDoDeleteCur( message_id )
		getUriAdminDoDeleteCur = VP_FORUM & PAGE_FORUM_ADMIN_DODELETE &"?" & _
			toUrlValue2("delkind","one", "del", message_id)
	end function

	public function getUriAdminDoDeleteCurSubs( message_id )
		getUriAdminDoDeleteCurSubs = VP_FORUM & PAGE_FORUM_ADMIN_DODELETE &"?" & _
			toUrlValue2("delkind","branch", "del",message_id)
	end function

	public function getUriAdminDoModify()
		getUriAdminDoModify = VP_FORUM & PAGE_FORUM_ADMIN_DOMODIFY &"?" & toUrl
	end function

	public function getUriAdminDoModifyForum( forum_id )
		getUriAdminDoModifyForum = VP_FORUM & PAGE_FORUM_ADMIN_DOMODIFYFORUM &"?"& _
			toUrlValue("forumid",forum_id)
	end function

	'

	public function getUriOwnerDoDelete()
		getUriOwnerDoDelete = VP_FORUM & PAGE_FORUM_OWNER_DODELETE &"?" & toUrl
	end function

	public function getUriOwnerDoModify()
		getUriOwnerDoModify = VP_FORUM & PAGE_FORUM_OWNER_DOMODIFY &"?" & toUrl
	end function

	'

	public function getUriUserDoMail()
		getUriUserDoMail = VP_FORUM & PAGE_FORUM_USER_DOMAIL & "?" & toUrl
	end function

	public function getUriUserDoNew()
		getUriUserDoNew = VP_FORUM & PAGE_FORUM_USER_DONEW & "?" & toUrl
	end function

	public function getUriUserDoReply()
		getUriUserDoReply = VP_FORUM & PAGE_FORUM_USER_DOREPLY & "?" & toUrl
	end function

	' ···························
	' misc pages.

	' general failure information page.
	public function getUriFailure( error_text )
		getUriFailure = VP_FORUM & PAGE_FORUM_FAILURE & "?et=" & _
			Server.UrlEncode(error_text)
	end function

	' url for selecting the current message.
	public function getUriSelectCur()
		dim result
		result = m_Ax.Value("main")&"?" & toUrlValue("select",getCurID)

		getUriSelectCur = appendAnchor( result, getArticleAnchor(getCurID) )
	end function
	
	' the url of the main page (the list of articles).
	public function getUriMain( article_id )
		dim result
		result = m_Ax.Value("main")&"?" &toUrl
		
		' This causes problems. eg. ?topic=37#xx0xx => topic = "37xx0xx"
		'getUriMain = appendAnchor(result,getArticleAnchor(article_id))
		
		' This causes problems (keywords are left blank)
		'getUriMain = m_Ax.Value("main")& "#" &getArticleAnchor(article_id) _
		'                               & "?" &toUrl
		' Do this until we get it to work
		getUriMain = result
	end function
	
	public function getUriRow( article_id, first_row )
		dim result
		result = m_Ax.Value("main")&"?" & toUrlValue("fr", first_row)
	
		getUriRow = appendAnchor(result,getArticleAnchor(article_id))
		'getUriRow = result
	end function
		
	' ---------------------------------------------
	' private variables.

	private m_Conn		' the database-connection.
	private m_Ax		' the connection to the active-x object.

	' ---------------------------------------------
end class


' ///////////////////////////////////////////////////////////////////////////
%>