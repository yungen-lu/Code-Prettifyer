<?php
if ($_FILES['filesubmit']['error'] === UPLOAD_ERR_OK) {  //檢查有沒有上傳成功
  if (!is_dir("../upload")) {  //若upload資料夾不存在的話就新增一個
    mkdir("../upload", 0755, true);
  }

    $pattern = "/\w+\.[a-z]+/";
    if (file_exists('../upload/' . $_FILES['filesubmit']['name']) && preg_match($pattern, $_FILES['filesubmit']['name'])) {
        unlink('../upload/' . $_FILES['filesubmit']['name']);  //若檔案存在的話刪除
        $file = $_FILES['filesubmit']['tmp_name'];
        $dest = '../upload/' . $_FILES['filesubmit']['name'];
        move_uploaded_file($file, $dest);  //將檔案從暫存移動到upload/
        echo json_encode("SUCCESS!");
    } else {
        echo "filename error";
    }
}
