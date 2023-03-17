import axios from 'axios';
import { useAuthStore } from '@/stores/auth';

const baseURL = 'http://188.166.217.138:8000/';

const axiosInstance = axios.create({
  baseURL,


});

axiosInstance.interceptors.request.use((config) => {
  const authStore = useAuthStore();
  if (authStore.isAuthenticated) {
    config.headers.Authorization = `Token ${authStore.token}`;
  }
  return config;
});

export default axiosInstance;