<?php
namespace Minbaby\Calculator\Tree;

class X
{
    public function mid(?Node $node)
    {
        if ($node == null) {
            return;
        }

        $this->mid($node->left);
        __($node->data);
        $this->mid($node->right);
    }

    public function first(?Node $node)
    {
        if ($node == null) {
            return;
        }

        __($node->data);
        $this->mid($node->left);
        $this->mid($node->right);
    }

    public function end(?Node $node)
    {
        if ($node == null) {
            return;
        }

        $this->mid($node->left);
        $this->mid($node->right);
        __($node->data);
    }
}