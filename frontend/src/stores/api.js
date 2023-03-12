import { defineStore } from 'pinia'
import axios from "@/helpers/utils/axiosInstance";


export const useApiStore = defineStore('api', {
    state: () => ({
        
    }),
    actions: {
        async getIntent(text){

            var data = JSON.stringify({
                "query": text
              });            

           const response = await axios.post('/api/v1/ai/',data=data,
           {
            headers: {
                'Content-Type': 'application/json'

            }
           });
            console.log(response.data);

            return response.data;


        },
        async getKnowledge(text){
            var data = JSON.stringify({
                "question": text
              });  
              
              const response = await axios.post('/api/v1/knowledge/',data=data,{
                headers: {
                    'Content-Type': 'application/json'
    
                }
              })
              console.log(response.data);

            return response.data;


        },
        async getVoiceTranscript(text){
            var data = JSON.stringify({
                "text": text
              });  
            const response = await axios.post('/api/v1/texttospeech/',data=data,{
                headers: {
                    'Content-Type': 'application/json'
                }
            })
            

            return response.data;
        },
        async getWeather(place){
            var data = JSON.stringify({"city":place});

            const response = await axios.post('/api/v1/weather/',data=data,{
                headers: {
                    'Content-Type': 'application/json'
                }
                    }
                    )
            console.log(response.data);

            return response.data;

        }
        
    }

})