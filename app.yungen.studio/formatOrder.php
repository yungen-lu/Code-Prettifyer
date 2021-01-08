<?php
if (isset($_GET)){
    $filename = $_GET['filenamekey'];
    if((file_exists('./app/removeSpace')==false)&& file_exists('./app/removeSpace.c')){
        shell_exec('gcc ./app/removeSpace.c -o ./app/removeSpace');
    }
    if((file_exists('./app/formatBracket')==false)&& file_exists('./app/formatBracket.c')){
        shell_exec('gcc ./app/formatBracket.c -o ./app/formatBracket');
    }
    if ((file_exists('./app/formatBracket')==false)||(file_exists('./app/removeSpace')==false)) {  //檢查執行命令所需程式，若無則直接編譯，若失敗則回傳Opps
    echo "Opps...";
    }else{
    $cmd = "cat "."./upload/$filename "."| "."./app/removeSpace "."| "."./app/formatBracket";
    $output = shell_exec($cmd);
    echo $output;
    unlink("./upload/$filename");
    }
}
?>
