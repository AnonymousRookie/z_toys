# vue2_demo

## Project setup
```
pnpm install
```

### Compiles and hot-reloads for development
```
pnpm run serve
```

### Compiles and minifies for production
```
pnpm run build
```

### Lints and fixes files
```
pnpm run lint
```

### Customize configuration
See [Configuration Reference](https://cli.vuejs.org/config/).






# 安装过程记录

## node 版本

v16.20.0

## package-lock和package.json

package-lock就是锁定安装时的包版本号，需要上传到git上，以保证其他人在install时候，大家的依赖版本相同。

^向上尖号是定义向后（新）兼容依赖，在大版本上相同，就允许下载最新的包。同一个大版本不同版本号之间存在差异，导致依赖库包行为特征有时候不兼容。

所以npm最新的版本就开始自动生成package-lock.json功能，目的就是确保所有库包与你上次安装的完全一样。

package.json文件只能锁定大版本，即版本号的第一位，不能锁定后面的小版本，你每次npm install时候拉取的该大版本下面最新的版本

一般为了稳定性考虑我们不能随意升级依赖包，因为如果换包导致兼容性bug出现很难排查，所以package-lock.json就是来解决包锁定不升级问题的。

如果要升级package-lock.json里面的库包，怎么操作呢？

```sh
npm install XXX@x.x.x  
```

## dependencies与devDependencies

- 使用命令--save或者不写，都会把信息记录到dependencies中，dependencies中记录的都是项目在运行时需要的文件；

- 使用命令--save-dev，会把信息记录到devDependencies中，devDependencies中记录的是项目在开发过程中需要使用的一些文件，在项目最终运行时是不需要的。


## 安装命令

```sh
npm i element-ui -S
npm install vue-router@3
npm install vuex@3
npm install axios
npm install js-cookie@2
npm install sass-loader node-sass --save-dev
npm install svg-sprite-loader@4 --save-dev
npm install webpack@^5.0.0 --save-dev
```


