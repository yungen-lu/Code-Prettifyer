## Code-Prettifyer

### 簡介

一個簡單的網站讓使用者能檢查、格式化程式碼。使用 php 作為後端。

### Build the web page

```shell
npm install
// for development
npm run build-test
// for production
npm run build
```

### Compile C code

```shell
gcc ./dist/app/c/formatBracket.c -o ./dist/app/c/formatBracket
gcc ./dist/app/c/parseError.c -o ./dist/app/c/parseError
gcc ./dist/app/c/removeSpace.c -o ./dist/app/c/removeSpace
```

### Run with Docker and docker-compose

Create Docker network

```shell
docker network create web
```

Run with docker-compose

```shell
docker-compose up -d
```



### 更詳細的說明

Blog post : https://blog.yungen.studio/content/posts/code-prettifyer/

