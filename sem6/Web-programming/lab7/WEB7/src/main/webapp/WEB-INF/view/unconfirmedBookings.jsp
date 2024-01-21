<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>

<fmt:setBundle basename="bundle"/>

<head>
    <meta charset="UTF-8" />
    <title>KKW Hotel</title>
    <link rel="stylesheet"
          href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css"
          integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l"
          crossorigin="anonymous">
    <style>
        <%@include file="styles.css"%>
    </style>
</head>
<body>




<a href="${pageContext.request.contextPath}/serv?command=home"><h3 align = "center"><fmt:message key="index.kkwhotel" /></h3></a>
<p align = "center"><fmt:message key="unconfirmed.all" /></p>

<div class="sm-padding">
    <div class="container-fluid">
        <div class="row">
            <div class ="col-md-10 offset-md-1">
                <div class="card  h-100">
                    <div class="card-body">
                        <table class="table">
                            <thead>
                            <tr>
                                <th scope="col"><fmt:message key="table.ID" /></th>
                                <th scope="col"><fmt:message key="table.Type" /></th>
                                <th scope="col"><fmt:message key="table.guests" /></th>
                                <th scope="col"><fmt:message key="table.arrivalTime" /></th>
                                <th scope="col"><fmt:message key="table.departureTime" /></th>
                                <th scope="col"><fmt:message key="table.status" /></th>
                                <th scope="col"><fmt:message key="table.clientID" /></th>
                            </tr>
                            </thead>
                            <tbody>
                            <c:forEach items="${unconfirmedBookingsList}" var="booking">
                                <tr>
                                    <td scope="col">${booking.getId()}</td>
                                    <td scope="col">${booking.getType()}</td>
                                    <td scope="col">${booking.getGuests()}</td>
                                    <td scope="col">${booking.getArrivalTime().toString()}</td>
                                    <td scope="col">${booking.getDepartureTime().toString()}</td>
                                    <td scope="col">${booking.getIsConfirmed()}</td>
                                    <td scope="col">${booking.getClientId().getId()}</td>
                                </tr>
                            </c:forEach>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
</body>
</html>