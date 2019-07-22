<?php
use function Kahlan\describe;
use function Kahlan\expect;
use Minbaby\Calculator\Calculator;

describe("计算", function () {
    context("前缀计算", function () {
        $data = [
            3 => "+ 1 2",
            2 => "* 1 2",
            10 => "+ + + 1 2 3 4",
            3 => "+ - * 1 2 3 4",
        ];

        foreach($data as $k => $v) {
            it ("run ==> $v", function () use ($k, $v) {
                expect($k)->toBe((new Calculator())->prefixNotation(explode(' ', $v)));
            });
        }
    });

    context("后缀计算", function () {
        $data = [
            3 => "1 2 +",
            2 => "1 2 *",
            6 => "1 2 3 * *",
        ];

        foreach($data as $k => $v) {
            it ("run ==> $v", function () use ($k, $v) {
                expect($k)->toBe((new Calculator())->postfixNotation(explode(' ', $v)));
            });
        }
    });
});