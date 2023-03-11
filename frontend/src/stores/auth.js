import { defineStore } from 'pinia'

export  const useAuthStore = defineStore('auth',{
  state:()=>{
    return{
      token: null,
      isAuthenticated: false,
    }
  },
  actions:{
    initialStore(){
      const token = localStorage.getItem('token')
      if(token){
        this.token = token
        this.isAuthenticated = true
      }else{
        this.token = null
        this.isAuthenticated = false
      }


    },
    setToken(token){
      localStorage.setItem('token',token)
      this.token = token
      this.isAuthenticated = true
    },
    logout(){
      localStorage.removeItem('token')
      this.token = null
      this.isAuthenticated = false
    }



  }
})