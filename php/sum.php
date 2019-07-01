<?php

function cal(string $data)
{
    $opts = [
        '+',
        '-',
        '/',
        '*'
    ];

    $kh = [
        '(',
        ')'
    ];
    
    $arr = str_split($data);

    $stack = new SplStack();

    foreach($arr as $item){
        $new = null;
        if ($stack->isEmpty()) {
            _("empty==>" . $new);
        } else {
            $top = $stack->top();
            if (in_array($top, $opts)) {
                $opt = $stack->pop();
                $num = $stack->pop();
                $new = opt($num, $opt, $item);
                _("nul==>" . $num);
                _("new==>" . $new);
            } elseif ($item == ')') {
                // while(true) {
                //     $
                // }
            }
        }

        if ($new == null){
            $stack->push($item);
            _("push==>" . $item);
            continue;
        }

        $stack->push($new);
        _("new==>" . $new);
    }
    return $stack->pop();
}

function _($data)
{
    // echo "$data\n";
}


function opt($first, $opt, $second)
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
    }
}



// var_dump(cal("1/3/3/3/3"));
var_dump(cal("1/(3/3+1)"));