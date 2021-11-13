<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%
	Object[][] cal = new Object[][] {
		{"24.02.2020", "Динамо", "0-1"},
		{"29.02.2020", "ЦСКА", "2-0"},
		{"03.03.2020", "Спартак", "2-2"},
		{"14.03.2020", "Манчестер", "2-3"}
	};
%>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>Календарь игр</title>
	</head>
	<body>
		<%@include file="Header.jsp"%>
		<h1>Календарь игр</h1>
		<table border = '1'>
			<tr>
				<td><b>Дата</b></td>
				<td><b>Противник</b></td>
				<td><b>Счет</b></td>
			</tr>
			<%
			for (Object[] temp : cal)
				out.println("<tr><td>" + temp[0] + "</td><td>" + temp[1] + "</td><td>"
					+ temp[2] + "</td></tr>");
			%>
		</table>
	
	<%//@include file="footer.jsp"%>
	</body>
</html>

