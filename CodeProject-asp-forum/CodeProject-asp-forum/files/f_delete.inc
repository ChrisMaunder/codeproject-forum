<%' delete.asp
%>

<%
' ***********************************************************************
' get.

dim id

id      = Request("del")


' ***********************************************************************
' delete.

' delete one the whole branch.

	fh.deleteArticle(id)



' ***********************************************************************
' >> continue.

Response.Redirect fh.getUriMain(0)
%>