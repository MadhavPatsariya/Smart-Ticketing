  // Your web app's Firebase configuration
  // For Firebase JS SDK v7.20.0 and later, measurementId is optional
  var firebaseConfig = {
    apiKey: "AIzaSyA7fPFqck3UXEh2nr1aYCJD-I9kQ4P4k-M",
    authDomain: "bus-ticketing-system-edb5a.firebaseapp.com",
    databaseURL: "https://bus-ticketing-system-edb5a-default-rtdb.firebaseio.com",
    projectId: "bus-ticketing-system-edb5a",
    storageBucket: "bus-ticketing-system-edb5a.appspot.com",
    messagingSenderId: "1093925298421",
    appId: "1:1093925298421:web:8b4ecc76fd62de29b665bc",
    measurementId: "G-XJ8R594DT9"
  };
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);
  //firebase.analytics();
  const auth = firebase.auth()
  const db = firebase.database()
  

