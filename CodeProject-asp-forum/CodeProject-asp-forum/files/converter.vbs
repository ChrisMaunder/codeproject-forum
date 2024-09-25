option explicit

Const PATH = "../database/forum.mdb"

'db connection
dim m_conn
set m_conn = CreateObject("ADODB.Connection")
m_conn.Open "Provider=Microsoft.Jet.OLEDB.4.0;" &_
"Persist Security Info=False;" &_
"Data Source=" & PATH



'--------------------------------------
'insert entry
function insert(position, indent, id)
	dim rs_insert
	set rs_insert = CreateObject("ADODB.Recordset")
	rs_insert.Open "SELECT * FROM Article WHERE ForumID = "& forum_id &"AND ID = "&id, m_conn, 2, 3
	rs_insert("Position")	= position
	rs_insert("Indent")		= indent
	rs_insert.Update
	rs_insert.Close
end function
'--------------------------------------

'find position-------------------------
sub countPosition
	position = Clng(position)-1
	while Len(position) < 6
		 position = "0" & position
	wend
end sub
'--------------------------------------

'insert childs-------------------------
function insertChild(parent_id, indent)
	dim x
	dim rs_child, sql_child
	sql_child= "SELECT * From Article WHERE ForumID = "& forum_id & " AND ParentID =" &parent_id & " ORDER BY Date ASC"
	set rs_child = m_Conn.Execute(sql_child)

	'gets the position of the parent entry
	dim rs_pos, sql_pos
	sql_pos= "SELECT * From Article WHERE ForumID = "& forum_id & " AND ID =" &parent_id & " ORDER BY Date DESC"
	set rs_pos = m_Conn.Execute(sql_pos)

	dim last
	'if there are no other childs
	if (rs_child.Bof and rs_child.Eof) then
		x = "000001"
		c_position = position & x
	'if there are other childs
	else
		while not rs_child.Eof
			x = CStr(CLng(x)+1)
			while Len(x) < 6
				 x = "0" & x
			wend
			c_position = rs_pos("position") & "." & x
			insert c_position, indent, rs_child("ID")
			insertChild rs_child("ID"), indent+1
			rs_child.MoveNext
		wend
	end if
	
	dim c_position

end function


'--------------------------------------
function convert(id)
	countPosition
	insert position, 0, id
	insertChild id, 1
end function
'----------------------------------

' get the forumID---------------------------------
dim rs_forum, sql_forum
sql_forum= "SELECT DISTINCT ForumID From Article"
set rs_forum = m_Conn.Execute(sql_forum)
'-------------------------------------------------

while not rs_forum.Eof
	dim position, forum_id
	' set "position" to the start
	position = "1000000"
	forum_id = rs_forum("ForumID")

	'get the parent entries of the forum
	dim rs, sql
	sql= "SELECT * From Article WHERE ForumID = "&forum_id&" AND ParentID = 0 ORDER BY Date ASC"
	set rs = m_Conn.Execute(sql)

	while not rs.Eof
		convert rs("ID")
		rs.MoveNext
	wend
	rs_forum.MoveNext
wend

'----------------------------------------
sub trace( text )
	WScript.Echo text & vbCrLf
end sub

trace "Database-Update was successful."
