<?php
/**
 * Created by PhpStorm.
 * User: a.kozhevnikov
 * Date: 20/01/2017
 * Time: 22:22
 */
namespace kozhevnikov\controller;


class Socket
{

    private $service_port = 8422;
    private $address = '127.0.0.1';
    private $socket;

    function __construct() {
        /* Создаём  TCP/IP сокет. */
        $this->socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        if ($this->socket === false) {
            throw new \Exception("Не удалось выполнить socket_create(): причина: " . socket_strerror(socket_last_error()));
        }

        if (socket_connect($this->socket, $this->address, $this->service_port) === false) {
            throw new \Exception("Не удалось выполнить socket_connect().\nПричина: " . socket_strerror(socket_last_error($this->socket)));
        }

    }

    function __destruct() {
        socket_close($this->socket);
    }

    private function makeQuery($query, $responseFormat)
    {

        socket_write($this->socket, $query, strlen($query));

        $response = null;
        while ($out = socket_read($this->socket, 1024)) {
            $response = unpack($responseFormat, $out);
        }

        return $response;
    }
    //получить количество городов
    public function getCityNum(){
        return self::makeQuery(pack('i', 1), 'Cquantity');
    }
    //сбросить расчеты
    public function reset(){
        return self::makeQuery(pack('i', 10), 'Cquantity');
    }
    //получить название города
    public function getCityName(int $cityNum){
       return self::makeQuery(pack('C*', 2, $cityNum), 'A*name');
    }
    //получить маршрут для города
    public function getRoutesForCity(int $cityNum){
       return self::makeQuery(pack('C*', 8, $cityNum), 'A*');
    }
    //получить 1 узел
    public function getSimpleNode(int $cityNum){
       return self::makeQuery(pack('C*', 3, $cityNum), 'Inum/IxPos/IyPos/I*');
    }
    //получить связи для узла
    public function getNodeCon(int $cityNum){
       return self::makeQuery(pack('C*', 4, $cityNum), 's*');
    }
    //получить маршрут из from в to
    public function getRoutes(int $from, int $to){
       return self::makeQuery(pack('CSS', 9, $from, $to), 'A12pcName/A20osName/stripPrice/s*');
    }

}