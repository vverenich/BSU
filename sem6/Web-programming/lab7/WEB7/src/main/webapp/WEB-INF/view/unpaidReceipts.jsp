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
<p align = "center"><fmt:message key="unpaid.All" /></p>

<div class="sm-padding">
    <div class="container-fluid">
        <div class="row">
            <div class ="col-md-10 offset-md-1">
                <div class="card h-100">
                    <div class="card-body">
                        <tabletag:unpaid admin="true">
                        </tabletag:unpaid>
                    </div>
                    <form class="form-signin" method="post"
                          action="${pageContext.request.contextPath}/serv?command=unpaidReceipts">
                        <button class="btn btn-lg btn-dark btn-block" type="submit">Save</button>
                    </form>
                </div>
            </div>
        </div>
    </div>
</div>
</body>
</html>