<?php
namespace Minbaby\Calculator\Tree;

class Node
{
    public $left;
    public $right;
    public $data;

    public function __construct(?Node $left = null, ?Node $right = null, $data = null)
    {
        $this->left = $left;
        $this->right = $right;
        $this->data = $data;
    }
}