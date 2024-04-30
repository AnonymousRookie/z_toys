import Vue from 'vue'
import App from './App.vue'

import Element from 'element-ui'

import router from './router'
import Cookies from 'js-cookie'

import './icons'

Vue.use(Element, {
  // set element-ui default size
  size: Cookies.get('size') || 'medium'
})

Vue.config.productionTip = false

new Vue({
  el: '#app',
  router,
  render: h => h(App),
})
