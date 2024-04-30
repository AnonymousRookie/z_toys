'use strict'

const path = require('path')

const defaultSettings = require('./src/settings.js')

const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true
})

function resolve(dir) {
  return path.join(__dirname, dir)
}

const name = defaultSettings.title

// If your port is set to 80,
// use administrator privileges to execute the command line.
// For example, Mac: sudo npm run
// You can change the port by the following method:
// port = 9527 npm run dev OR npm run dev --port = 9527
const port = process.env.port || process.env.npm_config_port || 9527 // dev port

// All configuration item explanations can be find in https://cli.vuejs.org/config/
module.exports = {
  /**
   * You will need to set publicPath if you plan to deploy your site under a sub path,
   * for example GitHub Pages. If you plan to deploy your site to https://foo.github.io/bar/,
   * then publicPath should be set to "/bar/".
   * In most cases please use '/' !!!
   * Detail: https://cli.vuejs.org/config/#publicpath
   */
  publicPath: '/',
  // build时输出的文件目录
  outputDir: 'dist',
  // 放置静态文件夹目录
  assetsDir: 'static',
  lintOnSave: process.env.NODE_ENV === 'development',
  /* 生产环境是否要生成sourceMap，
   * 启用有助于开发者调试代码，但是会导致构建后的代码文件体积增大，影响页面加载速度。
   */
  productionSourceMap: false,

  // dev环境下，webpack-dev-server相关配置
  devServer: {
    // 开发运行时的端口
    port: port,
    // pnpm run serve时是否直接打开浏览器
    open: false,
  },

  // 如果要新增/修改webpack的plugins或者rules，有2种方式：configureWebpack、chainWebpack
  configureWebpack: {
    
  },
  chainWebpack(config) {
    // set svg-sprite-loader
    config.module
    .rule('svg')
    .exclude.add(resolve('src/icons'))
    .end()
  config.module
    .rule('icons')
    .test(/\.svg$/)
    .include.add(resolve('src/icons'))
    .end()
    .use('svg-sprite-loader')
    .loader('svg-sprite-loader')
    .options({
      symbolId: 'icon-[name]'
    })
    .end()
  },
}