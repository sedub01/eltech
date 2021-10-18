<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<%
	Object[][] team = new Object[][] {
		{"Билли Херрингтон", 0, "Махачкала", 15000},
		{"Антон Чехов", 1, "Санкт-Петербург", 30000},
		{"Илья Антонов", 2, "Екатеринбург", 25000},
		{"Андрей Сачков", 3, "Вологда", 19000}
	};
	String[] roles = new String[] {"Вратарь", "Нападающий", "Полузащитник", "Защитник"};
%>
<table border='1'>
	<tr>
		<td><b><%=res.getString("name") %></b></td>
		<td><b><%=res.getString("spec") %></b></td>
		<td><b><%=res.getString("city") %></b></td>
		<td><b><%=res.getString("salary") %></b></td>
	</tr>
	<%
	for (Object[] temp : team)
		if (salary == null || (int)temp[3] >= Integer.parseInt(salary))
			out.println("<tr><td>" + temp[0] + "</td><td>" + roles[(int)temp[1]] + "</td><td>"
			+ temp[2] + "</td><td>" + Integer.toString((int)temp[3]) + "</td></tr>");
	%>
</table>
