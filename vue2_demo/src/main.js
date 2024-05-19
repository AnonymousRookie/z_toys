import Vue from 'vue'
import App from './App.vue'

import Element from 'element-ui'
import './styles/element-variables.scss'

import store from './store'
import router from './router'
import Cookies from 'js-cookie'

import './icons'
import './permission' // permission control


/**
 * If you don't want to use mock-server
 * you want to use MockJs for mock api
 * you can execute: mockXHR()
 *
 * Currently MockJs will be used in the production environment,
 * please remove it before going online ! ! !
 */
console.log('process.env.NODE_ENV:', process.env.NODE_ENV)

// 只在开发模式下使用mock
if (process.env.NODE_ENV === 'development') {
  const { mockXHR } = require('../mock')
  mockXHR()
}

Vue.use(Element, {
  // set element-ui default size
  size: Cookies.get('size') || 'medium'
})

Vue.config.productionTip = false

new Vue({
  el: '#app',
  router,
  store,
  render: h => h(App),
})
