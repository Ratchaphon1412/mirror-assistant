import { defineStore } from 'pinia'
import {authFirebase,
  signInWithEmailAndPassword,
  createUserWithEmailAndPassword,
  GoogleAuthProvider,
  FacebookAuthProvider,
  GithubAuthProvider,
  signInWithPopup
 } from '@/helpers/authentication/firebaseConfig.js'


import axios from "@/helpers/utils/axiosInstance";

export  const useAuthStore = defineStore('auth',{
  state:()=>{
    return{
      token:null,
      user:null,
      isAuthenticated:false
    }
  },
  actions:{
    async login(email,password){
    
        await signInWithEmailAndPassword (authFirebase,email,password).then(async (userCredential) => {
          console.log(userCredential)
          // Signed in
          
          this.token = await authFirebase.currentUser.getIdToken()
           
          console.log(this.token);
          const response = await axios.post('/api/users/firebase/auth/',{"token":this.token})
          console.log(response.data);
          this.isAuthenticated = true
          this.$router.push({ name: "ai" });
          // ...
        }).catch((error) => {
          const errorCode = error.code;
          const errorMessage = error.message;
          console.log(errorCode);
          console.log(errorMessage);
          // ..
        }
        );
       
       
        
       
    },
    async register(email,password,confirm_password){
        try{
          if(password === confirm_password){
            await createUserWithEmailAndPassword(authFirebase,email,password).then(async (userCredential)=>{
              const user = userCredential.user;
              this.token = await user.getIdToken()
              console.log(user);
            })
           
            
          }

        } catch(error) {
          throw error
        }

    },
    async loginGoogle(){
      const provider = new GoogleAuthProvider();
      await signInWithPopup(authFirebase,provider).then(async (result) => {
        const credential =  GoogleAuthProvider.credentialFromResult(result);
        this.token = await authFirebase.currentUser.getIdToken();
        console.log(this.token);
        const response = await axios.post('/api/users/firebase/auth/',{"token":this.token})
        console.log(response.data);
        this.isAuthenticated = 
        this.$router.push({ name: "ai" });
        const user = result.user;
        console.log(user);
        // ...
      }).catch((error) => {
        const errorCode = error.code;
        const errorMessage = error.message;
        const email = error.email;
        const credential = error.credential;
        console.log(errorCode);
        console.log(errorMessage);
        console.log(email);
        console.log(credential);
        // ...
      });
    },
    async  loginFacebook(){
      const provider = new FacebookAuthProvider();
      await signInWithPopup(authFirebase,provider).then(async (result) => {
        const credential =  FacebookAuthProvider.credentialFromResult(result);
        console.log(credential)
        this.token = await authFirebase.currentUser.getIdToken();
        console.log(this.token);
        const response = await axios.post('/api/users/firebase/auth/',{"token":this.token})
        console.log(response.data);
        this.isAuthenticated = true
        this.$router.push({ name: "ai" });
        const user = result.user;
        console.log(user);

      }).catch((error) => {
        const errorCode = error.code;
        const errorMessage = error.message;
        const email = error.email;
        const credential = error.credential;
        console.log(errorCode);
        console.log(errorMessage);
        console.log(email);
        console.log(credential);
      });


    },
    async loginGithub(){


      const provider = new GithubAuthProvider();
      await signInWithPopup(authFirebase,provider).then(async (result) => {
        console.log(result)
        const credential =  GithubAuthProvider.credentialFromResult(result);
        
        this.token = await authFirebase.currentUser.getIdToken();
        console.log(this.token);
        const response = await axios.post('/api/users/firebase/auth/',{"token":this.token})
        console.log(response.data);
        this.isAuthenticated = true
        this.$router.push({ name: "ai" });
        const user = result.user;
        console.log(user);


      })
    }
  },

})