import { createApp} from 'vue'

import { createPinia } from 'pinia'


import App from './App.vue'
import router from './router'
import VueSpeech from 'vue-speech'
import 'mapbox-gl/dist/mapbox-gl.css';
import './assets/main.css'


const app = createApp(App)


app.use(createPinia());

app.use(VueSpeech)
app.use(router)


app.mount('#app')
