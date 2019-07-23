<?php
namespace Minbaby\Calculator;

class Calculator {
    public function prefixNotation(array $data): int
    {
      $stack = new \SplStack();

      foreach ($data as $index => $value) {
        if (is_numeric($value) && is_numeric($stack->top())) {
            $first = $stack->pop();
            $opt = $stack->pop();
            $result = $this->opt($first, $opt, $value);
            $stack->push($result);
            continue;
        }

        $stack->push($value);
      }

      $ret = 0;
      while (!$stack->isEmpty()) {
        $count = $stack->count();
        if ($count == 1) {
            $ret = $stack->pop();
            break;
        }

        if($count < 3 && $count > 1) {
            throw new \Exception("输入表达式异常");
        }

        $first = $stack->pop();
        $second = $stack->pop();
        $opt = $stack->pop();

        $result = $this->opt($first, $opt, $second);
        $stack->push($result);
      }

      return intval($ret);
    }

    public function postfixNotation(array $data): int
    {
        $stack = new \SplStack();
        foreach ($data as $index => $value) {
            if (!is_numeric($value)) {
                $second = $stack->pop();
                $first = $stack->pop();
                $result = $this->opt($first, $value, $second);
                $stack->push($result);
                continue;
            }

            $stack->push($value);
        }
        
        if ($stack->count() != 1) {
            throw new \Exception("输入表达式异常");
        }

        return (int) $stack->pop();
    }

    public function infixNotation(array $data): int
    {
        throw new \Exception("TODO");
        return 0;
    }
    
    protected function __($data)
    {
        static $count = 0;
        echo "====> [$count] $data <====\n";
        $count++;
    }

    protected function opt($first, $opt, $second)
    {
        switch($opt) {
            case '-':
                return $first - $second;
            case '+':
                return $first + $second;
            case '*':
                return $first * $second;
            case '/':
                return $first / $second;
            default:
                new \Exception("不支持的运算符");
        }
    }
}