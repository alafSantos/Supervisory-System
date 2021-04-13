import axios from 'axios';

export default ({ Vue, router }) => {
  const vue = Vue.prototype;
  vue.$axios = axios.create({
    baseURL: process.env.api,
  });
  vue.$axios.interceptors.response.use((response) => {
    vue.$q.loading.hide();
    console.log(response);
    const { message } = response.data;
    if (message) {
      vue.$q.notify({
        message,
      });
    }
    return response;
  }, async (error) => {
    vue.$q.loading.hide();
    console.log(error);
    const { status } = error.response;
    const { response } = error;
    console.log(response);
    if (status === 422) { // there's an error on the data passed to the api
      const errors = response.data.message;
      vue.$q.dialog({
        title: 'Atenção',
        message: errors,
      });
    } else if (status === 401) {
      localStorage.clear();
      router.push({ name: 'login' });
    } else {
      vue.$q.notify({
        color: 'warning',
        icon: 'warning',
        textColor: 'white',
        message: 'Não foi possível realizar esta ação. Tente novamente mais tarde.',
      });
    }
  });

  vue.$axios.interceptors.request.use(async (request) => {
    request.headers.common['X-Requested-With'] = 'XMLHttpRequest';
    request.headers.common['Content-Type'] = 'Application/json';
    const token = localStorage.getItem(process.env.storage);
    if (token) request.headers.common.Authorization = `Bearer ${token}`;
    vue.$q.loading.show();
    return request;
  }, (error) => {
    vue.$q.loading.hide();
    return Promise.reject(error);
  });
};
