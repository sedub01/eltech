<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<% String notlang = (lang.equals("ru"))? "en" : "ru"; %>

<form method="post">
	<p><select name = "lang">
	<option value = <%=lang %>><%=lang %></option>
	<option value = <%=notlang %>><%=notlang %></option>
	</select>
	<input type="Submit" value="Submit"/></p>
</form>