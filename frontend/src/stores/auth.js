import { defineStore } from 'pinia'
import axios from 'axios'


export const useAuthStore = defineStore('auth', {
  state: () => ({
    user: null,
  }),
  actions: {
    async loginWithGitHub() {
      const clientId = '3df6ccacb2da539b3638';
      const redirectUri = 'http://localhost:5173/login';
      const scope = 'user:email'; 
      const url = `https://github.com/login/oauth/authorize?client_id=${clientId}&redirect_uri=${redirectUri}&scope=${scope}`;

      // Redirect the user to the GitHub login page
      window.location.href = url;
    },
    async handleLogin(code) {
      const clientId = '3df6ccacb2da539b3638';
      const clientSecret = 'c8fdd575162054e1ec5e8f6c4728d2ddc75da143';
      const redirectUri = 'http://localhost:5173/';
      const url = `https://github.com/login/oauth/access_token?client_id=${clientId}&client_secret=${clientSecret}&code=${code}&redirect_uri=${redirectUri}`;
      console.log(url);

      // Exchange the authorization code for an access token
     

      await axios.post(url,{
      
        headers: {
          'Access-Control-Allow-Origin': '*',

          'Content-Type': 'application/json',
          'Accept': 'application/json',
        },
        mode:'cors',
       
      credentials: "include",
      referrerPolicy: "origin",
      })
      .then(response => {
        const accessToken = response.data;
        jsonAccessToken = JSON.stringify(accessToken);
        console.log(jsonAccessToken);
        // do something with the access token
      })
      .catch(error => {
        console.error(error);
      });

     
    },
    async logout() {
      this.setUser(null);
    },
    async sendLoginSuccessToDjango() {
      // Send a login success signal to Django Allauth
      const response = await fetch('/accounts/github/login/success/', {
        method: 'POST'
      });
    }
  },
  mutations: {
    setUser(user) {
      this.user = user;
    }
  }
});
