<?php
if (isset($_GET)) {
    $filename = $_GET['filenamekey'];
    if (!file_exists('../c/removeSpace') && file_exists('../c/removeSpace.c')) {
        shell_exec('gcc ../c/removeSpace.c -o ../c/removeSpace');
    }
    if (!file_exists('../c/formatBracket') && file_exists('../c/formatBracket.c')) {
        shell_exec('gcc ../c/formatBracket.c -o ../c/formatBracket');
    }
    if (!file_exists('../c/formatBracket') || (file_exists('../c/removeSpace')==false)) {  //檢查執行命令所需程式，若無則直接編譯，若失敗則回傳Opps
        echo "Opps...";
    } else {
        $pattern = "/\w+\.[a-z]+/";
        $cmd = "cat "."../upload/$filename "."| "."../c/removeSpace "."| "."../c/formatBracket";
        if (preg_match($pattern, $filename)) {  //add regex to prevent injection attack
            $output = shell_exec($cmd);
            echo $output;
            unlink("../upload/$filename");
        } else {
            echo "filename error";
        }
    }
}
