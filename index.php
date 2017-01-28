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
    $class_name = strtolower(str_replace('\\', '/', $class_name));
    $path = realpath(__DIR__ . (strstr($class_name, '/') . '.php'));
    if ($path){
        try{
            require $path;
        }catch (\Exception $e){
            exit($e->getMessage());
        }
    }
});

use kozhevnikov\controller\Socket;

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
            break;
        case 'getCityName':
            if (!isset($_GET['param'])){
                throw new \Exception('Отсутствует обязательный параметр param.');
            }
            $resp = $client->getCityName((int)$_GET['param']);
            break;
        case 'getNodeCon':
            if (!isset($_GET['param'])){
                throw new \Exception('Отсутствует обязательный параметр param.');
            }
            $resp = $client->getNodeCon((int)$_GET['param']);
            break;
        case 'getCityNum':
            $resp = $client->getCityNum();
            break;
        case 'reset':
            $resp = $client->reset();
            break;
        case 'getRoutes':
            if (!isset($_GET['param'])){
                throw new \Exception('Отсутствует обязательный параметр param.');
            }
            $resp = $client->getRoutes((int)$_GET['param'][0], (int)$_GET['param'][1]);
            $resp = $resp['tripPrice'] == -1 ? null : $resp;
            break;
        default:
            echo 'Unknown command';
            return 0;
    }


    header('Content-Type: application/json');
    echo json_encode($resp, JSON_UNESCAPED_UNICODE);
    return 0;
}

render('canvas');
return 0;