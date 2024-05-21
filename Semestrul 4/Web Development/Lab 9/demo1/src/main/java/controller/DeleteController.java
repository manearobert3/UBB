package controller;

import model.DBManager;
import domain.User;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;

public class DeleteController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        User user = (User) session.getAttribute("user");

        if (user == null) {
            response.sendRedirect(request.getContextPath() + "/");
            return;
        }

        int postId = Integer.parseInt(request.getParameter("id"));
        int userId = user.getId();

        DBManager dbManager = new DBManager();
        if (dbManager.isPostOwner(postId, userId)) {
            dbManager.deletePost(postId);
            response.sendRedirect(request.getHeader("referer")); // Redirect to the previous page
        } else {
            response.sendRedirect(request.getContextPath() + "/error.jsp");
        }
    }
}
