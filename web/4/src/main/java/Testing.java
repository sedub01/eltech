import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.ResourceBundle;

import jakarta.servlet.ServletException;
//import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;


//@WebServlet("/TeamList")
/**
 * Servlet implementation class Testing
 */
public class Testing extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private Object[][] team;
	private String[] roles;
	ResourceBundle res;
	String salary, lang;
	/**
	* @see HttpServlet#HttpServlet()
	*/
	public Testing() {
		super();
		team = new Object[][] {
			{"Билли Херрингтон", 0, "Махачкала", 15000},
			{"Антон Чехов", 1, "Санкт-Петербург", 30000},
			{"Илья Антонов", 2, "Екатеринбург", 25000},
			{"Андрей Сачков", 3, "Вологда", 19000}
		};
		roles = new String[] {"Вратарь", "Нападающий", "Полузащитник", "Защитник"};
	}
	/**
	* Processes requests for both HTTP <code>GET</code> and <code>POST</code>
	methods.
	*
	* @param request servlet request
	* @param response servlet response
	* @throws ServletException if a servlet-specific error occurs
	* @throws IOException if an I/O error occurs
	*/
	protected void processRequest(HttpServletRequest request, HttpServletResponse
	response)
	throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");
		salary = request.getParameter("salary");
		lang = request.getParameter("lang");
		response.setContentType("text/html;charset=UTF-8");
		
		if (lang == null) lang = "ru";
		if (!"en".equalsIgnoreCase(lang) && !"ru".equalsIgnoreCase(lang)) {
			response.sendError(HttpServletResponse.SC_NOT_ACCEPTABLE,
			"Параметр lang может принимать значения ru или en вместо \"" + lang + "\"");
			return;
		}
		res = ResourceBundle.getBundle("team", ("ru".equals(lang))? 
				Locale.getDefault() : Locale.ENGLISH);
		PrintWriter out = response.getWriter();
		try {
			// Создание HTML-страницы
			out.println("<html>");
			out.println("<head><title>Список моих футболистов</title></head>");
			out.println("<body>");
			out.println("<h1>" + res.getString("title") + ((salary == null)? "": 
				res.getString("condition") + salary + "$") + "</h1>");
			out.println("<table border='1'>");
			out.println("<tr><td><b>" + res.getString("name") + "</b></td>"
					+ "<td><b>" + res.getString("spec") + "</b></td>"
					+ "<td><b>" + res.getString("city") + "</b></td>"
					+ "<td><b>" + res.getString("salary") + "</b></td></tr>");
			
			for (Object[] temp : team)
				if (salary == null || (int)temp[3] >= Integer.parseInt(salary))
					out.println("<tr><td>" + temp[0] + "</td><td>" + roles[(int)temp[1]] + "</td><td>"
					+ temp[2] + "</td><td>" + Integer.toString((int)temp[3]) + "</td></tr>");
			out.println("</table>");
			
			String notlang = (lang.equals("ru"))? "en" : "ru";
			out.println("<form method=\"post\">"
					+ "<p><select name = \"lang\">"
					+ "<option value = \"" + lang + "\">" + lang + "</option>"
					+ "<option value = \""+notlang+"\">"+notlang + "</option>" 
					+ "</select>"
					+ "<input type=\"Submit\" value=\"Submit\"/></p>"
					+ "</form>");
			out.println("</body>");
			out.println("</html>");
		} finally {
			// Закрытие потока вывода
			out.close();
		}
	}
	/**
	* Handles the HTTP
	* <code>GET</code> method.
	*
	* @param request servlet request
	* @param response servlet response
	* @throws ServletException if a servlet-specific error occurs
	* @throws IOException if an I/O error occurs
	*/
	@Override
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
	throws ServletException, IOException {
		processRequest(request, response);
	}
	/**
	* Handles the HTTP
	* <code>POST</code> method.
	* @param request servlet request
	* @param response servlet response
	* @throws ServletException if a servlet-specific error occurs
	* @throws IOException if an I/O error occurs
	*/
	@Override
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
	throws ServletException, IOException {
		processRequest(request, response);
	}
}