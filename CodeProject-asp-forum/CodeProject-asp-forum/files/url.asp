<%	option explicit

	dim url
	url = "http://www.elke.de?a=aal&e"
	'url = "http://www.elke.de?if===&&&"

	Dim d
	Set d = CreateObject("Scripting.Dictionary")


	sub trace
		dim x,a,b,s
		b = d.Items
		a = d.Keys

		For x = 0 To d.Count -1
			s = s & a(x) & "&nbsp;&nbsp;" & b(x) & "<br>"
		Next
		Response.Write s
	end sub

	'--------------------------------------------------------------------------------
	' build the internal map of name-value pairs from a given url.
	function fromURL(url)

		dim url_element

		if InStr(url, "?") then
			
			url_element = split(url, "?")

			'if the url has no parameters
			if url_element(1) = "" then
				exit function
			'if the url has parameters
			else
				dim params
				dim item
				params = split(url_element(1), "&")

				dim x

				For each x in params
					if InStr(x, "=") then
						item = split(x, "=")
						
						'add key-item to object
						d.Add item(0), item(1)
					end if
				Next

			end if
		end if

	end function
	
	fromURL(url)
	'trace

	'--------------------------------------------------------------------------------
	' returns all values of the internal map url-encoded
	' in the form "name=value&name=value&name=value&" etc.
	' you can append this directly to an url.
	
	function toUrl
		dim x,s,a,b
		a = d.Keys
		b = d.Items

		For x = 0 To d.Count -1
			s = s & a(x) & "=" & Server.URLEncode(b(x)) & "&"
		Next
		toUrl = s
		
	end function
	'Response.Write toUrl

	'--------------------------------------------------------------------------------
	' the same as "toUrl" except that the value of the
	' map-entry specified by "name" is replaced by "new_value".
	
	function toUrlValue(key,new_item)
		toUrl
		dim x,s,a,b

		if not d.Exists(key)then
			d.Add key, new_item
		end if

		a = d.Keys
		b = d.Items

		

		For x = 0 To d.Count -1
			
			if a(x)=key then
				s = s & a(x) & "=" & Server.URLEncode(new_item) & "&"
			else
				s = s & a(x) & "=" & Server.URLEncode(b(x)) & "&"
			end if

		Next
		
		toUrlValue = s
		
	end function
	'Response.Write "<b>" &toUrlValue("forumid","3")	&"</b>"	
	Response.Write toUrlValue("forumid","3")

	'--------------------------------------------------------------------------------
	' the same as "toUrl" except that the value of the
	' map-entry specified by "name1" is replaced by "new_value1" and
	' the value of "name2" is replaced by "new_value2".
	function toUrlValue2( key1, new_item1, key2, new_item2 )
		dim x,s,a,b
		a = d.Keys
		b = d.Items

		For x = 0 To d.Count -1
			if a(x)=key1 then
				s = s & a(x) & "=" & Server.URLEncode(new_item1) & "&"
			elseif a(x)=key2 then
				s = s & a(x) & "=" & Server.URLEncode(new_item2) & "&"
			else
				s = s & a(x) & "=" & Server.URLEncode(b(x)) & "&"
			end if
		Next
		
		toUrlValue2 = s
	end function

	'Response.Write toUrlValue2("b", "elkebbbeeeh", "c", "romulus und remüs") & "<br>"
	'trace
%>