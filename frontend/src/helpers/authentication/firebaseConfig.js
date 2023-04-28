import * as firebase from "firebase/app";
import { getAuth,signInWithEmailAndPassword ,createUserWithEmailAndPassword,
  GoogleAuthProvider,
  FacebookAuthProvider,
  GithubAuthProvider,
  signInWithPopup
} from "firebase/auth";


const firebaseConfig = {
  apiKey: 'AIzaSyDVDXo_WL6ZnT36gKd0bC2_er_gEcyXjhc',
  authDomain: 'iotservices-378810.firebaseapp.com',
  databaseURL: '',
  projectId: 'iotservices-378810',
  storageBucket:'iotservices-378810.appspot.com',
  messagingSenderId: '384950271216',
  appId: '1:384950271216:web:7134dff81ebb71c2a49635',
  measurementId: 'G-4NR5ENJRZM'
};


// Initialize Firebase
firebase.initializeApp(firebaseConfig);

//initialize firebase auth
const authFirebase =getAuth();


export {authFirebase,signInWithEmailAndPassword,
  createUserWithEmailAndPassword,
  GoogleAuthProvider,
  FacebookAuthProvider,
  GithubAuthProvider,
  signInWithPopup
};