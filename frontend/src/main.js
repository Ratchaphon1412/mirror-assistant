import { createApp} from 'vue'

import { createPinia } from 'pinia'


import App from './App.vue'
import router from './router'
import VueSpeech from 'vue-speech'

import './assets/main.css'

import 'bootstrap-icons/font/bootstrap-icons.css'

const app = createApp(App)


app.use(createPinia());

app.use(VueSpeech)
app.use(router)

app.mount('#app')
