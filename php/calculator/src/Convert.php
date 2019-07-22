<?php
namespace Minbaby\Calculator;

class Convert {

    const L0 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0];

    const L1 = ['+', '-'];

    const L2 = ['*', '/'];

    const L3 = ['(', ')'];

    public function converInfixToPrefix(array $infixNotation): array
    {
        $numStack = new \SplStack();
        $optStack = new \SplStack();

        $reverse = array_reverse($infixNotation);

        foreach($reverse as $v) {
            if ($v === ')') {
                $optStack->push($v);
                continue;
            }

            if ($v === '(') {
                while(!$optStack->isEmpty()) {
                    $top = $optStack->pop();
                    if ($top === ')') {
                        continue;
                    }
                    $numStack->push($top);
                }
                continue;
            }


            if ($this->isNumberic($v)) {
                $numStack->push($v);
                continue;
            }

            if ($this->isOperator($v)) {
                while (true) {
                    if ($optStack->isEmpty() || $optStack->top() === ')') {
                        $optStack->push($v);
                        break;
                    }

                    if (!$this->less($v, $optStack->top())) {
                        $optStack->push($v);
                        break;
                    } 

                    $numStack->push($optStack->pop());
                }

                continue;
            }

            throw new \Exception("unknow value {$v}");
        }

        while(!$optStack->isEmpty()) {
            $numStack->push($optStack->pop());
        }

        return splSplDoublyLinkedListToArray($numStack);
    }

    public function convertInfixToPostfix(array $infixNotation): array
    {
        $numStack = new \SplQueue();
        $optStack = new \SplStack();

        foreach ($infixNotation as $v) {
            if ($this->isNumberic($v)) {
                $numStack->push($v);
                continue;
            }

            if ($v == '(') {
                $optStack->push($v);
                continue;
            }
            
            if ($v === ')') {
                while(!$optStack->isEmpty()) {
                    $top = $optStack->pop();
                    if ($top === '(') {
                        continue;
                    }
                    $numStack->push($top);
                }
                continue;
            }

            if ($this->isOperator($v)) {
                while (true) {
                    if ($optStack->isEmpty() || $optStack->top() === '(') {
                        $optStack->push($v);
                        break;
                    }
                    if ($this->greeter($v, $optStack->top())) {
                        $optStack->push($v);
                        break;
                    }

                     $numStack->push($optStack->pop());
                }
                continue;
            }

            throw new \Exception("unknow value {$v}");
        }

        while(!$optStack->isEmpty()) {
            $numStack->push($optStack->pop());
        }

        return splSplDoublyLinkedListToArray($numStack);
    }

    protected function isNumberic(string $value): bool
    {
        // __(array_merge([__METHOD__], func_get_args()));
        return is_numeric($value);
    }

    protected function isKuoHao(string $value): bool
    {
        // __(array_merge([__METHOD__], func_get_args()));
        return in_array($value, static::L3) || in_array($value, static::L3);
    }

    protected function isOperator(string $value): bool
    {
        // __(array_merge([__METHOD__], func_get_args()));
        return in_array($value, array_merge(static::L1, static::L2));
    }

    protected function greeter(string $optFirst, string $optSecond): bool
    {
        // __(array_merge([__METHOD__], func_get_args()));
       return in_array($optFirst, static::L2) && in_array($optSecond, static::L1);
    }


    protected function less(string $optFirst, string $optSecond): bool
    {
        // __(array_merge([__METHOD__], func_get_args()));
       return in_array($optFirst, static::L1) && in_array($optSecond, static::L2);
    }
}