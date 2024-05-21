package controller;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;

public class LogoutController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false); // Get the current session, but don't create a new one if it doesn't exist
        if (session != null) {
            session.invalidate(); // Invalidate the session
        }
        response.sendRedirect(request.getContextPath() + "/"); // Redirect to the login page or home page
    }
}
