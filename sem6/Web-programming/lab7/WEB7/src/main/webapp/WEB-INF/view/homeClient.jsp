<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>


<fmt:setBundle basename="bundle"/>
<jsp:include page="_menu.jsp"></jsp:include>

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


<h1 align = "center"><fmt:message key="index.welcome"/></h1>
<p align = "center"><fmt:message key="home.happy"/></p>
<p align = "center"><fmt:message key="home.lastVisit"/> ${cookie['lastEnterTime'].getValue()}</p>
<p align = "center"><fmt:message key="home.visitCount"/> ${cookie['usageCount'].getValue()}</p>



<div class="md-padding">
    <div class="container-fluid">
        <div class="row">
            <div class ="col-md-4">
                <a href="${pageContext.request.contextPath}/serv?command=createBooking">
                    <div class="card h-100">
                        <div class="card-body">
                            <h5 class="card-title"><fmt:message key="home.create"/></h5>
                        </div>
                    </div>
                </a>
            </div>
            <div class ="col-md-4">
                <a href="${pageContext.request.contextPath}/serv?command=printRooms">
                    <div class="card h-100">
                        <div class="card-body">
                            <h5 class="card-title"><fmt:message key="home.allRooms"/></h5>
                        </div>
                    </div>
                </a>
            </div>
            <div class ="col-md-4">
                <a href="${pageContext.request.contextPath}/serv?command=payReceipt">
                    <div class="card h-100">
                        <div class="card-body">
                            <h5 class="card-title"><fmt:message key="home.pay"/></h5>
                        </div>
                    </div>
                </a>
            </div>
            <div class ="col-md-4">
                <a href="${pageContext.request.contextPath}/serv?command=unpaidReceipts">
                    <div class="card h-100">
                        <div class="card-body">
                            <h5 class="card-title"><fmt:message key="home.unpaid"/></h5>
                        </div>
                    </div>
                </a>
            </div>
            <div class ="col-md-4">
                <a href="${pageContext.request.contextPath}/serv?command=confirmBooking">
                    <div class="card h-100">
                        <div class="card-body">
                            <h5 class="card-title"><fmt:message key="home.confirm"/></h5>
                        </div>
                    </div>
                </a>
            </div>
            <div class ="col-md-4">
                <a href="${pageContext.request.contextPath}/serv?command=unconfirmedBookings">
                    <div class="card h-100">
                        <div class="card-body ">
                            <h5 class="card-title"><fmt:message key="home.unconfirmed"/></h5>
                        </div>
                    </div>
                </a>
            </div>
        </div>
    </div>
</div>


</body>
</html>
