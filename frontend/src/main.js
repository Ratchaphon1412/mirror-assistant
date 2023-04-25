import { createApp} from 'vue'

import { createPinia } from 'pinia'


import App from './App.vue'
import router from './router'
import 'bootstrap-icons/font/bootstrap-icons.css'
import {initializeApp} from 'firebase/app'
import './assets/main.css'

const firebaseConfig = {
    apiKey: "AIzaSyDVDXo_WL6ZnT36gKd0bC2_er_gEcyXjhc",
    authDomain: "iotservices-378810.firebaseapp.com",
    projectId: "iotservices-378810",
    storageBucket: "iotservices-378810.appspot.com",
    messagingSenderId: "384950271216",
    appId: "1:384950271216:web:7134dff81ebb71c2a49635",
    measurementId: "G-4NR5ENJRZM"
  };

initializeApp(firebaseConfig);

const app = createApp(App)


app.use(createPinia());


app.use(router)


app.mount('#app')
