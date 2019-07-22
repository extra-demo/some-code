<?php

function __($data)
{
    $type = gettype($data);
    switch($type) {
        case "array":
            $data = implode(" ·· ", array_values($data));
            break;
        case "boolean":
        case "double":
        case "integer":
        case "string":
            $data = $data;
            break;
        case "object":
            if ($data instanceof \SplDoublyLinkedList) {
                $data = splSplDoublyLinkedListToArray($data);
            }
            $data = implode(" ·· ", (array) $data);
            break;
        default:
            $data = "====> WARNING: NOT SUPPORT <====";
    }

    static $count = 0;
    list($unixTime, $micro) = explode('.', (string) microtime(true));
    echo sprintf("[%s.%s] [%s-%d] %s\n", date('Y-m-d H:i:s', (int) $unixTime), str_pad($micro, 4, '0'), $type, $count, $data);
    $count++;
}

function splSplDoublyLinkedListToArray(\SplDoublyLinkedList $data): array
{
    $ret = [];

    foreach($data as $v) {
        $ret[] = $v;
    }

    return $ret;
}

function __r($method, $msg = '')
{
    list($unixTime, $micro) = explode('.', (string)microtime(true));
    echo sprintf("[%s.%s] [%s] %s\r", date('Y-m-d H:i:s', (int)$unixTime), str_pad($micro, 4, '0'), $method, $msg);
}
