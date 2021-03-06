// import { CodeJar } from 'https://medv.io/codejar/codejar.js';
// import { withLineNumbers } from "https://medv.io/codejar/linenumbers.js";
// import {axios} from 'axios'
const axios = require('axios').default;
import { CodeJar } from 'codejar';
import { withLineNumbers } from 'codejar/linenumbers';
import Toastify from 'toastify-js';
import 'toastify-js/src/toastify.css';
import hljs from 'highlight.js/lib/core';
import c from 'highlight.js/lib/languages/c';
import 'highlight.js/styles/atom-one-dark.css'
import '../src/css/style.css'
hljs.registerLanguage('c', c);
const highlight = (editor) => {
  editor.textContent = editor.textContent;
  hljs.highlightBlock(editor);
};

const editor = document.querySelector('.editor');
const jar = new CodeJar(editor, withLineNumbers(highlight));
export { jar };
let b1 = document.querySelector('#button1');
let b2 = document.querySelector('#button2');
let b3 = document.querySelector('#filesubmit');

b1.addEventListener('click', sendb1Req);
b2.addEventListener('click', sendb2Req);
b3.addEventListener('change', sendb3Req);
function getFilename() {
  let filePath = document.querySelector('#filesubmit').value;
  // let pathName=document.querySelector('#fileupload').value;
  // let lastDot = filePath.lastIndexOf('.');
  // let filename = filePath.substr(0, lastDot);
  // return filename;
  return filePath.substr(filePath.lastIndexOf('\\') + 1);
}

function sendb1Req() {
  let code = jar.toString(); //用codejar的API將使用者輸入的程式碼給code這個變數
  let codeObject = {
    codeKey: code, //將code變數放在codeObject這個object裡面
    filenamekey: 'tmpfile.c',
  };
  axios
    .post('app/php/postData.php', codeObject) //傳送POST request給'postData.php'其中包含codeObject
    .then((res) => {
      console.log(res.data);
      return axios.get('app/php/formatOrder.php', {
        //接受到伺服器的response後再傳送GET request 給'formatOrder.php'
        params: { filenamekey: 'tmpfile.c' },
      });
    })
    .then((res) => {
      console.log(res.data);
      jar.updateCode(res.data); //將回傳的資料（格式化過的程式碼）更新編輯器內的程式碼
    })
    .catch((err) => {
      console.log('ERR'); //假如在其中過程失敗的話在console中輸出'ERR'
      console.log(err);
    });
}
function sendb2Req() {
  let code = jar.toString();
  let codeObject = {
    codeKey: code,
    filenamekey: 'tmpfile.c',
  };
  axios
    .post('app/php/postData.php', codeObject)
    .then((res) => {
      console.log(res.data);
      return axios.get('app/php/excuteOrder.php', {
        params: { filenamekey: 'tmpfile.c' }, // todo
      });
    })
    .then((res) => {
      console.log(res.data);
      toastFunc(res.data);
    })
    .catch((err) => {
      console.log('ERR');
      console.log(err);
    });
}
function sendb3Req() {
  let formElement = document.getElementById('filesubmit').files[0];
  const formData = new FormData();
  formData.append('filesubmit', formElement);
  axios
    .post('app/php/uploadData.php', formData)
    .then((res) => {
      console.log(res.data);
      let filename = getFilename();
      return axios.get(`app/php/excuteOrder.php`, {
        params: { filenamekey: filename },
      });
    })
    .then((res) => {
      console.log(res.data);
      toastFunc(res.data);
    })
    .catch((err) => {
      console.log('ERR');
      console.log(err);
    });
}
function toastFunc(Context) {
  for (let i = 0; i < Context.length; i++) {
    console.log(Context[i][2]);
    // toastr[Context[i][2]](Context[i][3], 'Line: ' + Context[i][0]);
    toastifyOptions.text = concatToastText(Context[i][0],Context[i][3]);
    toastifyOptions.className = Context[i][2];
    Toastify(toastifyOptions).showToast();
  }
}
function concatToastText(a,b) {
  const output = `Line:${a}<br>${b}`;
  return output;
}
let toastifyOptions = {
  text: 'SUCC',
  duration: -1,
  className: 'info',
  // destination: "https://github.com/apvarun/toastify-js",
  // newWindow: true,
  close: true,
  gravity: 'top', // `top` or `bottom`
  position: 'right', // `left`, `center` or `right`
  // backgroundColor: "linear-gradient(to right, #00b09b, #96c93d)",
  stopOnFocus: true, // Prevents dismissing of toast on hover
  // onClick: function(){} // Callback after click
};
// Toastify(toastifyOptions).showToast();
