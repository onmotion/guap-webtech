<?php
/**
 * Created by PhpStorm.
 * User: a.kozhevnikov
 * Date: 20/01/2017
 * Time: 22:22
 */

ini_set('display_errors', 1);
ini_set('error_reporting', E_ALL);

spl_autoload_register(function ($class_name) {
    $parts = explode('\\', $class_name);
    require end($parts) . '.php';
});

use kozhevnikov\Socket;

function render($view){
    include 'view/layout.php';
}

$client = new Socket();
if (isset($_GET['type'])){

    $resp = null;

    switch ($_GET['type']){
        case 'getSimpleNode':
            if (!isset($_GET['param'])){
                throw new \Exception('Отсутствует обязательный параметр param.');
            }
            $resp = $client->getSimpleNode((int)$_GET['param']);
//            if (count($resp) == 7){
//                $resp = array_combine(['num', 'xPos', 'yPos'], $resp);
//            }
            break;
        case 'getCityName':
            if (!isset($_GET['param'])){
                throw new \Exception('Отсутствует обязательный параметр param.');
            }
            $resp = $client->getCityName((int)$_GET['param']);
            if ($resp){
                $resp = array_combine(['name'], $resp);
            }
            break;

        case 'getCityNum':
            $resp = $client->getCityNum();
            if ($resp){
                $resp = array_combine(['quantity', 'ext'], $resp);
            }
            break;
        default:
            echo 'Unknown command';
            return 0;
    }


    header('Content-Type: application/json');
    echo json_encode($resp, JSON_UNESCAPED_UNICODE);
    return 0;
}
$resp = $client->getCityNum();

//echo "Количество зарегестрированных городов на сервере: " . array_shift($resp);
render('canvas');
return 0;