<?php

function __($data)
{
    $type = gettype($data);
    switch($type) {
        case "array":
            $data = implode(" ·· ", $data);
            break;
        case "boolean":
        case "double":
        case "string":
            $data = $data;
            break;
        case "object":
            $data = implode(" ·· ", (array) $data);
            break;
        default:
            $data = "====> WARNING: NOT SUPPORT <====";
    }

    static $count = 0;
    list($unixTime, $micro) = explode('.', (string) microtime(true));
    echo sprintf("[%s.%s] [%s] %s\n", date('Y-m-d H:i:s', (int) $unixTime), str_pad($micro, 4, '0'), $type, $data);
    $count++;
}

function _logR($method, $msg = '')
{
    list($unixTime, $micro) = explode('.', (string)microtime(true));
    echo sprintf("[%s.%s] [%s] %s\r", date('Y-m-d H:i:s', (int)$unixTime), str_pad($micro, 4, '0'), $method, $msg);
}
