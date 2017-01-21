<?php
/**
 * Created by PhpStorm.
 * User: a.kozhevnikov
 * Date: 20/01/2017
 * Time: 22:22
 */
namespace kozhevnikov;


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

    private function makeQuery($query, $responseFormat = 'C*')
    {

        socket_write($this->socket, $query, strlen($query));

        $response = null;
        while ($out = socket_read($this->socket, 2048)) {
            $response = unpack($responseFormat, $out);
        }

        return $response;
    }

    public function getCityNum(){
        return self::makeQuery(pack('i', 1));
    }
    public function getCityName(int $cityNum){
       return self::makeQuery(pack('C*', 2, $cityNum), 'A*');
    }
    public function getRoutesForCity(int $cityNum){
       return self::makeQuery(pack('C*', 8, $cityNum), 'A*');
    }
    public function getSimpleNode(int $cityNum){
       return self::makeQuery(pack('C*', 3, $cityNum), 'I*');
    }

}