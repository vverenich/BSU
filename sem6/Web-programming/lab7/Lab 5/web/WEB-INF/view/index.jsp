<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html lang="en">
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<head>
    <meta charset="UTF-8">
    <title>Airport</title>
    <style>
        <%@include file="assets/css/index_style.css"%>
    </style>
    <style>
        <%@include file="assets/css/races_style.css"%>
    </style>
</head>

<body class="normalize">
<div class="header"></div>
<div class="content">
    <div class="strip">
        <h1>Авиакомпания</h1>
        <h2>Администратор осуществляет назначение Самолета на Рейс с
        учетом вместимости и дальности полета и назначает на Рейс одну из летных
        Бригад. Бригада формируется Командиром и состоит из пилотов, штурмана,
        радиста, стюардесс. Администратор может отменить Рейс из-за погодных
        условий, либо изменить в полете Аэропорт назначения из-за технических
        неисправностей.</h2>
        <h3>
            <br>Функционал включает в себя возможность:
        </h3>
        <ul>
            <li>
                <a class="nav-link" href="${pageContext.request.contextPath}?command=brigadePageCommand">1) Вывести информацию о бригаде заданного рейса.</a>
            </li>
            <li>
                <a class="nav-link" href="${pageContext.request.contextPath}?command=getAllRacesPageCommand">2) Вывести список всех рейсов.</a>
            </li>
            <li>
                <a class="nav-link" href="${pageContext.request.contextPath}?command=destinationPageCommand"> 3) Изменить аэропорт назначения рейса.</a>
            </li>
            <li>
                <a class="nav-link" href="${pageContext.request.contextPath}?command=cancelRacePageCommand">4) Отменить рейс.</a>
            </li>
            <li>
                <a class="nav-link" href="${pageContext.request.contextPath}?command=getDelayedRacesPageCommand">5) Вывести информацию о задержанных рейсах.</a>
            </li>
        </ul>
    </div>
</div>
</body>
</html>
