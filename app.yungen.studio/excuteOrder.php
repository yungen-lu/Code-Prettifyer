<?php
if (isset($_GET))
    if((file_exists('./app/parseError')==false)&& file_exists('./app/parseError.c')){
        shell_exec('gcc ./app/parseError.c -o ./app/parseError');
    }
    if (file_exists('./app/parseError')==false) {  //檢查執行命令所需程式，若無則直接編譯，若失敗則回傳Opps...
    echo "Opps...";
    }else{
    $filename = $_GET['filenamekey'];
    $cmd = 'cppcheck '.'--enable=all '.'--suppress=missingIncludeSystem '."./upload/$filename".' 2>&1 '.'| ./app/parseError';
    $output = shell_exec($cmd);
    $arrayOfGroup=explode("#?",$output);
    $jsonGroup=[];
    for($i = 0;$i <count($arrayOfGroup)-1;$i++){
        $tmp=explode("#",$arrayOfGroup[$i]);
        array_push($jsonGroup,$tmp);
    }
    echo json_encode($jsonGroup);
    unlink("./upload/$filename");
    }

?>
