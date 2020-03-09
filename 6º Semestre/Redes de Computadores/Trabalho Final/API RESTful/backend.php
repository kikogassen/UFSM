<?php 

if (isset($_POST['l2'])){

    $l2 = $_POST['l2'];
    $l2_count = count($l2);
    for($i=0; $i < $l2_count; $i++){
        echo($l2[$i] . " ");
    }
}


if (isset($_POST['l3'])){
    $l3 = $_POST['l3'];

    $l3_count = count($l3);
    for($i=0; $i < $l3_count; $i++){
        echo($l3[$i] . " ");
    }
}


?>