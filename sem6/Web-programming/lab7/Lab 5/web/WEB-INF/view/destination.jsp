<html lang="en">
<head>
    <meta charset="UTF-8">
    <style>
        <%@include file="assets/css/index_style.css"%>
    </style>
    <style>
        <%@include file="assets/css/races_style.css"%>
    </style>
    <title>Lab 3</title>
</head>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<body bgcolor="#efeeee">

<div class="strip">
    <h2 align="center">Смена аэропорта назначения</h2>
    <form id="cancelRaceForm" method="POST" action="${pageContext.request.contextPath}?command=changeDestinationCommand">
        <div class="form-group">
            <label>Введите id рейса</label>
            <input type="number" name="raceId" placeholder="id...">
        </div>
        <div class="form-group">
            <label>Введите новое назначение рейса</label>
            <input name="destination" placeholder="id...">
        </div>
        <button type="submit">Изменить</button>
    </form>

    <div class="table-box">
        <table class="table" border="1" >
            <thead>
            <tr>
                <th scope="col">Id</th>
                <th scope="col">Brigade</th>
                <th scope="col">Capacity</th>
                <th scope="col">Destination</th>
                <th scope="col">Plane</th>
                <th scope="col">Status</th>

            </tr>
            </thead>
            <tbody>
            <c:forEach items="${raceList}" var="race">
                <tr>
                    <th scope="col">${race.getId()}</th>
                    <th scope="col">${race.getBrigadeId()}</th>
                    <th scope="col">${race.getCapacity()}</th>
                    <th scope="col">${race.getDestination()}</th>
                    <th scope="col">${race.getPlaneId()}</th>
                    <th scope="col">${race.getStatus()}</th>
                </tr>
            </c:forEach>
            </tbody>
        </table>
    </div>
</div>
</body>
</html>
