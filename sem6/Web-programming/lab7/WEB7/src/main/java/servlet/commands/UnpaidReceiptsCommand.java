package servlet.commands;

import model.dao.ReceiptDAO;
import model.entity.Receipt;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class UnpaidReceiptsCommand implements Command
{
    @Override
    public String getPattern() {
        return "unpaidReceipts";
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException
    {
        RequestDispatcher dispatcher = servletContext.getRequestDispatcher("/WEB-INF/view/unpaidReceipts.jsp");

        ReceiptDAO receiptDAO = new ReceiptDAO();
        List<Receipt> list = receiptDAO.getNotPaidReceipts();
        request.setAttribute("unpaidReceiptsList", list);

        dispatcher.forward(request, response);
    }
}
