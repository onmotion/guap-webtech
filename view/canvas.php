<?php
/**
 * Created by PhpStorm.
 * User: a.kozhevnikov
 * Date: 21/01/2017
 * Time: 12:18
 */

?>
<script type="application/javascript" src="/assets/js/main.js"></script>
<h1>Карта городов</h1>
<body>
<div class="container">
    <div class="map-wrap">
    <canvas id="canvas" width="900" height="680"></canvas>
    <div class="right">
        <p>Всего городов: <span id="numOfCities"></span></p>
        <div id="citiesList">
            <ul></ul>
        </div>
    </div>
    </div>
<div class="controls">
    <form id="searchForm" action="#">
        <label>Показать маршруты из пункта:</label>
        <select id="select-city" name="select-city"></select>
        <input type="submit" value="Показать">
    </form>

</div>
<hr>
<h3>Таблица маршрутов</h3>
    <table id="routes">
        <tr>
            <th>Пункт назначения</th>
            <th>Логин</th>
            <th>ОС</th>
            <th>Цена пути</th>
            <th>Найденный путь</th>
        </tr>

    </table>
</div>

</body>