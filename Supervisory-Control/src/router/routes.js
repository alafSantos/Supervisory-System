const routes = [
  {
    path: '/',
    component: () => import('layouts/MainLayout.vue'),
    children: [
      {
        path: '',
        component: () => import('pages/Login.vue'),
        name: 'login',
        meta: { screen: 'Login' },
      },
    ],
  },
  {
    path: '/modulos',
    component: () => import('layouts/Layout.vue'),
    children: [
      {
        path: '/md1',
        name: 'MD1',
        component: () => import('pages/modulos/md1.vue'),
        meta: { screen: 'MD1', requiresLogin: true },
      },
      {
        path: '/md2',
        name: 'MD2',
        component: () => import('pages/modulos/md2.vue'),
        meta: { screen: 'MD2', requiresLogin: true },
      },
      {
        path: '/md3',
        name: 'MD3',
        component: () => import('pages/modulos/md3.vue'),
        meta: { screen: 'MD3', requiresLogin: true },
      },
      {
        path: '/md4',
        name: 'MD4',
        component: () => import('pages/modulos/md4.vue'),
        meta: { screen: 'MD4', requiresLogin: true },
      },
      {
        path: '/md5',
        name: 'MD5',
        component: () => import('pages/modulos/md5.vue'),
        meta: { screen: 'MD5', requiresLogin: true },
      },
      {
        path: '/md6',
        name: 'MD6',
        component: () => import('pages/modulos/md6.vue'),
        meta: { screen: 'MD6', requiresLogin: true },
      },
      {
        path: '/md7',
        name: 'MD7',
        component: () => import('pages/modulos/md7.vue'),
        meta: { screen: 'MD7', requiresLogin: true },
      },
      {
        path: '/md8',
        name: 'MD8',
        component: () => import('pages/modulos/md8.vue'),
        meta: { screen: 'MD8', requiresLogin: true },
      },
      {
        path: '/md9',
        name: 'MD9',
        component: () => import('pages/modulos/md9.vue'),
        meta: { screen: 'MD9', requiresLogin: true },
      },
    ],
  },
];

// Always leave this as last one
if (process.env.MODE !== 'ssr') {
  routes.push({
    path: '*',
    component: () => import('pages/Error404.vue'),
  });
}

export default routes;
