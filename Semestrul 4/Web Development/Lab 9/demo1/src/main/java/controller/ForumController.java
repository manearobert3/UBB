package controller;

import domain.Topic;
import model.DBManager;
import domain.User;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ForumController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        DBManager dbManager = new DBManager();
        ArrayList<Topic> topics = dbManager.getAllTopics();
        request.setAttribute("topics", topics);
        request.getRequestDispatcher("forum.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        if ("newTopic".equals(action)) {
            String title = request.getParameter("title");
            String content = request.getParameter("content"); // New content parameter
            User user = (User) request.getSession().getAttribute("user");
            if (user != null) {
                int userId = user.getId();
                DBManager dbManager = new DBManager();
                dbManager.createTopic(title, content, userId);
                response.sendRedirect("forum");
            } else {
                response.sendRedirect("login.jsp");
            }
        }
    }
}
