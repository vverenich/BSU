<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lab 3</title>
    <style>
        <%@include file="assets/css/index_style.css"%>
    </style>
    <style>
        <%@include file="assets/css/races_style.css"%>
    </style>
</head>
<body bgcolor="#efeeee">
<div class="strip" >
    <h2 align="center">Информация о бригаде выбранного рейса</h2>
    <form id="getBrigadeByRaceForm" method="post" action="${pageContext.request.contextPath}?command=getBrigadeByRaceCommand">
        <div class="form-group">
            <label>Введите id рейса</label>
            <input type="number" name="raceId" placeholder="id...">
        </div>
        <button type="submit">Отправить запрос</button>
    </form>
    <div class="input-box">
        <h1 align="left">Бригада:</h1>
    </div>
    <div class="table-box">
        <table class="table" border="1" title="id=1" >
                <thead>
                <tr>
                    <th scope="col">Id</th>
                    <th scope="col">Name</th>
                    <th scope="col">Position</th>
                </tr>
                </thead>
                <tbody>
                <c:forEach items="${emps}" var="emp">
                    <tr>
                        <th scope="col">${emp.getId()}</th>
                        <th scope="col">${emp.getName()}</th>
                        <th scope="col">${emp.getPosition()}</th>
                    </tr>
                </c:forEach>
                </tbody>
        </table>
    </div>
</div>
</body>
</html>