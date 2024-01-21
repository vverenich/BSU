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


<a href="${pageContext.request.contextPath}/serv?command=home">
    <h3 align = "center"><fmt:message key="index.kkwhotel" /></h3></a>
<p align = "center"><fmt:message key="allRooms.show" />
</p>

<div class="sm-padding">
    <div class="container-fluid">
        <div class="row">
            <div class="col-md-3">
                <div class="card ">
                    <div class="card-body">
                        <div class="page-form" >
                            <form id="type-rooms-form"  method="post"
                                  action="${pageContext.request.contextPath}/serv?command=printRooms"></form>
                        </div>
                    </div>
                </div>
            </div>
            <div class ="col-md-9 ">
                <div class="card">
                    <div class="card-body">
                            <table class="table">
                                <thead>
                                <tr>
                                    <th scope="col"><fmt:message key="table.ID" /></th>
                                    <th scope="col"><fmt:message key="table.Type" /></th>
                                    <th scope="col"><fmt:message key="table.Capacity" /></th>
                                    <th scope="col"><fmt:message key="table.perNight" /></th>
                                </tr>
                                </thead>
                                <tbody>
                                <c:forEach items="${printRoomsList}" var="room">
                                    <tr>
                                        <td scope="col">${room.getId()}</td>
                                        <td scope="col">${room.getType()}</td>
                                        <td scope="col">${room.getCapacity()}</td>
                                        <td scope="col">${room.getPrice()}</td>
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

<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-validate/1.19.0/jquery.validate.min.js"></script>
<script src="script/script.js"></script>
</body>
</html>