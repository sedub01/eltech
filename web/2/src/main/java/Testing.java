import java.io.IOException;
import java.io.PrintWriter;
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
		// Задание типа кодировки для параметров запроса
		request.setCharacterEncoding("utf-8");
		// Чтение параметра name из запроса
		String salary = request.getParameter("salary");
		// Задание типа содержимого для ответа (в том числе кодировки)
		response.setContentType("text/html;charset=UTF-8");
		// Получение потока для вывода ответа
		PrintWriter out = response.getWriter();
		try {
			// Создание HTML-страницы
			out.println("<html>");
			out.println("<head><title>Список моих футболистов</title></head>");
			out.println("<body>");
			out.println("<h1>Вот мои футболисты" + ((salary == null)? " ": " с зарплатой >= " 
					+ salary + "$") + "</h1>");
			out.println("<table border='1'>");
			out.println("<tr><td><b>Имя фамилия</b></td>"
					+ "<td><b>Специальность</b></td>"
					+ "<td><b>Город</b></td>"
					+ "<td><b>Зарплата</b></td></tr>");
			
			for (Object[] temp : team)
				if (salary == null || (int)temp[3] >= Integer.parseInt(salary))
					out.println("<tr><td>" + temp[0] + "</td><td>" + roles[(int)temp[1]] + "</td><td>"
					+ temp[2] + "</td><td>" + Integer.toString((int)temp[3]) + "</td></tr>");
			out.println("</table>");
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