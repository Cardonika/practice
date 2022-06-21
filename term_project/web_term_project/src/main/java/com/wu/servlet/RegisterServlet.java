package com.wu.servlet;

import com.wu.dao.LogDao;
import com.wu.dao.LogDaoImpl;
import com.wu.dao.UserDao;
import com.wu.dao.UserDaoImpl;
import com.wu.domain.UserBean;
import com.wu.domain.UserLogBean;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Date;
import java.sql.SQLException;

@WebServlet(name = "RegisterServlet", urlPatterns = "/register")
public class RegisterServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req, resp);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            String username = req.getParameter("username");
            String password = req.getParameter("password");

            resp.setCharacterEncoding("utf-8");
            UserBean user = new UserBean();
            user.setUsername(username);
            user.setPassword(password);
            UserDao dao = new UserDaoImpl();
            if(dao.register(user)) {
                UserLogBean logInfo = new UserLogBean();
                String ipAddress = req.getHeader("X-FORWARDED-FOR");
                if(ipAddress == null) {
                    ipAddress = req.getRemoteAddr();
                }

                logInfo.setUsername(user.getUsername());
                logInfo.setIp(ipAddress);
                logInfo.setAction("Register");
                logInfo.setDate(new Date((new java.util.Date()).getTime()));

                LogDao logger = new LogDaoImpl();
                logger.userLog(logInfo);

                resp.setStatus(200);
            }else {
                resp.setStatus(500);
                resp.getWriter().print("用户名已存在");
            }
        }catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
