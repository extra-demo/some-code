<?php

include 'helpers.php';

class Convert {

    static $L0 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0];

    static $L1 = ['+', '-'];

    static $L2 = ['*', '/'];

    public function run()
    {
        $infixNotation = "1+2*3+4/(5-6)*(7+8)/9";
        __($this->converInfixToPrefix($infixNotation));
    }

    protected function converInfixToPrefix(string $infixNotation): string
    {
        $data = str_split($infixNotation);
        __($data);
        foreach($data as $index => $value) {
            if ($this->isNumberic($value)) {
                
            }
        }
        return "abab";
    }

    protected function isNumberic(string $value): bool
    {
        return in_array($value, static::L0);
    }

    protected function isOperator(string $value): bool
    {
        return in_array($value, static::L1 + static::L2);
    }

    protected function greeter(string $optFirst, string $optSecond): bool
    {
        if (in_array($optFirst, static::L2) && in_array($optSecond, static::L1)) {
            return true;
        }

        return false;
    }
}

(new Convert())->run();