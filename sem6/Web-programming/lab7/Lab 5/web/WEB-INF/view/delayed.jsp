<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<style>
    <%@include file="assets/css/index_style.css"%>
</style>
<style>
    <%@include file="assets/css/races_style.css"%>
</style>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lab 3</title>
</head>
<body bgcolor="#efeeee">
<div class="strip">
    <div class="table-box">
        <h1 align="center">Список всех задержанных рейсов</h1>
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

