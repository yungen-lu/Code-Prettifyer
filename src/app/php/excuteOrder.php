<?php
if (isset($_GET)) {
    if (!file_exists('../c/parseError')&& file_exists('../c/parseError.c')) {
        shell_exec('gcc ../c/parseError.c -o ../c/parseError');
    }
}
    if (!file_exists('../c/parseError')) {  //檢查執行命令所需程式，若無則直接編譯，若失敗則回傳Opps...
        echo "Opps...";
    } else {
        $pattern = "/\w+\.[a-z]+/";
        $filename = $_GET['filenamekey'];
        $cmd = 'cppcheck '.'--enable=all '.'--suppress=missingIncludeSystem '."../upload/$filename".' 2>&1 '.'| ../c/parseError';
        if (preg_match($pattern, $filename)) {  //add regex to prevent injection attack
            $output = shell_exec($cmd);
            $arrayOfGroup=explode("#?", $output);
            $jsonGroup=[];
            for ($i = 0;$i <count($arrayOfGroup)-1;$i++) {
                $tmp=explode("#", $arrayOfGroup[$i]);
                array_push($jsonGroup, $tmp);
            }
            echo json_encode($jsonGroup);
            unlink("../upload/$filename");
        } else {
            echo "filename error";
        }
    }
