<?php
if (isset($_POST)) {
  header('Content-Type: application/json');  //因為傳送資料的格式為json
  $body=file_get_contents("php://input");
  $object = json_decode($body, true);  //需要把json轉換為php看得懂的格式
  $input = $object["codeKey"];
  $filename=$object["filenamekey"];  //codescript.js在傳送GET request 時有包含一個filenamekey 以及codeKey值
  $fptr = fopen('./upload/'.$filename, "w");
  fwrite($fptr, $input);
  fclose($fptr);
  echo json_encode("SUCCESS");
}

?>
