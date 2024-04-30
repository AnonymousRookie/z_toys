import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

import Layout from '@/layout'


/**
 * constantRoutes
 * a base page that does not have permission requirements
 * all roles can be accessed
 */
export const constantRoutes = [
    {
        path: '/login',
        component: () => import('@/views/login/index')
    },

]


/**
 * asyncRoutes
 * the routes that need to be dynamically loaded based on user roles
 */
export const asyncRoutes = [
    

    // 404 page must be placed at the end !!!
    { path: '*', redirect: '/404', hidden: true }
]






const createRouter = () => new Router({
    routes: constantRoutes
})

const router = createRouter()

export default router
