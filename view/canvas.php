<?php
/**
 * Created by PhpStorm.
 * User: a.kozhevnikov
 * Date: 21/01/2017
 * Time: 12:18
 */

?>
<script type="application/javascript" src="/assets/js/main.js?v=6"></script>

<h1>Карта городов</h1>
<div class="container">
    <div class="map-wrap">
        <canvas id="canvas" width="1220" height="780"></canvas>
        <canvas id="canvas2" width="1220" height="780"></canvas>
        <canvas id="canvas3" width="1220" height="780"></canvas>
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
    <a id="reset" href="#">Сбросить вычисления</a>
    <a id="download" target="_blank" href="/download/progBigWorld.zip">Скачать программу</a>
    <hr>
    <h3>Таблица маршрутов</h3>
    <table id="routes">
        <thead>
        <tr>
            <th>Пункт назначения</th>
            <th>Логин</th>
            <th>ОС</th>
            <th>Цена пути</th>
            <th>Найденный путь</th>
            <th><i class="icon-eye"></i></th>
        </tr>
        </thead>
        <tbody></tbody>
    </table>
</div>