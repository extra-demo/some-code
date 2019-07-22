<?php
use function Kahlan\describe;
use function Kahlan\expect;
use Minbaby\Calculator\Convert;

describe("转换", function () {
    context("中缀转后缀", function () {
        $data = [
            "1 + 2" => "1 2 +",
            "1 + 2 * 3" => "1 2 3 * +",
            "1 + 2 * 3 / 2" => "1 2 3 * 2 / +",
            "( 1 + 1 ) * 3" => '1 1 + 3 *',
            "( 1 + 2 ) * ( 3 + 4 )" => '1 2 + 3 4 + *',
        ];

        foreach($data as $k => $v) {
            it ("from:{$k} ==> to:{$v}", function () use ($k, $v) {
                $result = (new Convert())->convertInfixToPostfix(explode(' ', $k));
                $target = implode(' ', $result);
                expect($v)->toBe($target);
            });
        }
    });

    context("中缀转前缀", function () {
        $data = [
            "1 + 2" => "+ 1 2",
            "1 * 2" => "* 1 2",
            "( 1 + 2 ) * ( 3 + 4 )" => "* + 1 2 + 3 4",
            "( 1 + 2 ) * 3 + 4" => "+ * + 1 2 3 4",
        ];

        foreach($data as $k => $v) {
            it ("from:{$k} ==> to:{$v}", function () use ($k, $v) {
                $result = (new Convert())-> converInfixToPrefix(explode(' ', $k));
                $target = implode(' ', $result);
                expect($v)->toBe($target);
            });
        }
    });
});