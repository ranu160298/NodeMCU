<?php
echo 'Success';
$data1 = $_POST['d1'];
$data2 = $_POST['d2'];
$myfile = fopen("newfile.txt", "w+") or die("Unable to open file!");
fwrite($myfile, $data1);
fwrite($myfile, "\n");
fwrite($myfile, $data2);
fclose($myfile);

?>