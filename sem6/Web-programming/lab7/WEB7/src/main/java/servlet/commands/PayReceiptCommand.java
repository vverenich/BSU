package servlet.commands;

import bean.UserAccount;
import model.dao.ReceiptDAO;
import model.entity.Receipt;
import utils.AppUtils;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.List;

public class PayReceiptCommand implements Command
{
    @Override
    public String getPattern() {
        return "payReceipt";
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response,
                      ServletContext servletContext) throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/payReceipt.jsp");
        UserAccount loginedUser = AppUtils.getLoginedUser(request.getSession());

        ReceiptDAO receiptDAO = new ReceiptDAO();
        List<Receipt> list = receiptDAO.payReceiptList(loginedUser.getId());
        request.setAttribute("payReceiptList", list);

        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response,
                       ServletContext servletContext) throws ServletException, IOException
    {

        UserAccount loginedUser = AppUtils.getLoginedUser(request.getSession());
        ReceiptDAO receiptDAO = new ReceiptDAO();

        int receiptId = Integer.parseInt(request.getParameter("receiptId"));
        receiptDAO.payReceiptCheck(receiptDAO.payReceiptList(loginedUser.getId()), receiptId);

        doGet(request, response, servletContext);
    }
}