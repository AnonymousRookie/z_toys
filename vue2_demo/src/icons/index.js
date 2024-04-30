import Vue from 'vue'
import SvgIcon from '@/components/SvgIcon'

// register globally
Vue.component('svg-icon', SvgIcon)

// 3个参数的含义：引入资源的目录、是否需要遍历子目录、匹配文件的规则
const req = require.context('./svg', false, /\.svg$/)
// 导入所有的svg文件
const requireAll = requireContext => requireContext.keys().map(requireContext)
requireAll(req)

console.log('register svg-icon globally')
