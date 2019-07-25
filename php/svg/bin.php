<?php

require_once __DIR__ . '/vendor/autoload.php';

$svg = new \SVG\SVG(600, 400);

$data = [
    'SourceCodePro-Regular' => 'SourceCodePro-Regular.otf',
    'PingFangTC-Regular' => 'PingFang.ttc',
    'GB18030Bitmap' => 'NISC18030.ttf',
];

$height = 50;
foreach($data as $key => $value) {
    // 这个地方的字体似乎是系统字体库？
    $font = new \SVG\Nodes\Structures\SVGFont($key, $value);
    $svg->getDocument()->addChild($font);
    $svg->getDocument()->addChild(
        (new \SVG\Nodes\Texts\SVGText($key . '中国 98642', 50, $height))
            ->setFont($font)
            ->setSize(30)
            ->setStyle('stroke', '#f00')
            ->setStyle('stroke-width', 1)
        );
    $height += 50;
}

$rect = new \SVG\Nodes\Shapes\SVGRect(50, $height+50, 100, 100);
$svg->getDocument()->addChild($rect);

$ellipse = new \SVG\Nodes\Shapes\SVGEllipse(50, $height+50, 10, 10);
$ellipse->setStyle('stroke', '#0f0');
$svg->getDocument()->addChild($ellipse);



file_put_contents(sprintf("%s/cache/%s.svg", __DIR__, time()), $svg);