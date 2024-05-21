package controller;

import domain.Post;
import domain.Topic;
import model.DBManager;
import domain.User;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class TopicController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        int topicId = Integer.parseInt(request.getParameter("id"));
        DBManager dbManager = new DBManager();
        Topic topic = dbManager.getTopicById(topicId);
        List<Post> posts = dbManager.getPostsByTopicId(topicId);
        request.setAttribute("topic", topic);
        request.setAttribute("posts", posts);
        request.getRequestDispatcher("topic.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        if ("newPost".equals(action)) {
            String content = request.getParameter("content");
            int topicId = Integer.parseInt(request.getParameter("topicId"));
            User user = (User) request.getSession().getAttribute("user");
            if (user != null) {
                int userId = user.getId();
                DBManager dbManager = new DBManager();
                dbManager.createPost(content, topicId, userId);
                response.sendRedirect("topic?id=" + topicId);
            } else {
                response.sendRedirect("login.jsp");
            }
        }
    }
}
