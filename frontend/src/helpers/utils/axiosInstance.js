import axios from 'axios';
import { useAuthStore } from '@/stores/auth';

const baseURL = 'https://ratchaphon1412.co/';

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