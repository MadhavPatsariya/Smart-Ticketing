var data = {}
auth.onAuthStateChanged( user => {

  if(user){
    document.querySelector("#content").innerHTML=`
                <form id="add-cafe-form">
                    <input name="name" typ="text" placeholder="Filter By Name">
                    <input name="city" typ="text" placeholder="Filter By Month">
                    <button >Filter</button>
                </form>
                <div class='head'>
                <h3 class='Head-Date'>Date</h3>
                <h3 class='Head-ID'>Unique ID</h3>
                <h3 class='Head-Name'>Name</h3>
                </div>

                <ul id="cafe-list"></ul>
                <i><span id="RE" style="color:#555"> </span></i><br><br>

                <button id="logout">Logout</button>`
    const cafes=document.querySelector("#cafe-list");
    const RE=document.querySelector("#RE");



    //Reading data
    // db.collection("cafes").get().then(snapshot => {
    //   snapshot.docs.forEach(doc => {
    //     render(doc);
    //   });
    //
    // });

    function render(doc){
      console.log(doc);
      let li = document.createElement('li');
      let a = document.createElement('span');
      let b = document.createElement('span');
      let c = document.createElement('span');
      //let d = document.createElement('span');
      let cross = document.createElement('div');

      li.setAttribute('data-id',doc.id);
      a.textContent= doc['id'];
      b.textContent= doc['Unique ID'];
      c.textContent= doc['Name of Customer'];
      //d.textContent= doc['Event'];
      //city.textContent= doc.data().city;
      cross.textContent= 'x';

      li.appendChild(a);
      li.appendChild(b);
      li.appendChild(c);
      //li.appendChild(d);
      //li.appendChild(city);
      //li.appendChild(cross);

      cafes.appendChild(li);
      //deleting data
      cross.addEventListener('click', (e) =>{
        let id= e.target.parentElement.getAttribute('data-id');
        db.collection('cafes').doc(id).delete();
      });
    }


    //saving data
    const form= document.querySelector("#add-cafe-form")

    form.addEventListener('submit',(e)=>{
      e.preventDefault();
      cafes.innerHTML = "";
      // db.collection('cafes').add({
      //   name:form.name.value,
      //   city:form.city.value,
      // }).then(() => {
      //   form.reset();
      // });
      var count=0;
      for (const doc in data){
        if ((!form.name.value || data[doc]['Name of Customer'].startsWith(form.name.value)) && (!form.city.value || data[doc]['id'].startsWith(form.city.value)))
        {
          render(data[doc]);
          count++;
        }
      };
      RE.innerHTML=count+" Results"
      //form.reset()
    });

    //updating all values
    //db.collection("cafes").doc(document-id).set({....});

    //updating only mentioned attr
    //db.collection("cafes").doc(document-id).update({....});

    //real-time updates
    var starCountRef = firebase.database().ref('1T9zqgWL7rD2tDc6JNRkblhtbVxiD1-tKLe4YBN74UqU/Sheet1/');
    starCountRef.on('value', (snapshot) => {
    data = snapshot.val();
    console.log(data)
    var count =0;
    for (const doc in data){
      count++;

           render(data[doc]);
         };
         RE.innerHTML=count+" Results"
    //updateStarCount(postElement, data);
      });
    // db.collection("cafes").orderBy('name').onSnapshot(snapshot => {
    //   let changes= snapshot.docChanges();
    //   changes.forEach(change => {
    //     if(change.type == 'added'){
    //       render(change.doc);
    //     }else if (change.type == 'removed') {
    //       let id= cafes.querySelector('[data-id='+ change.doc.id +']');
    //       cafes.removeChild(id);
    //     }
    //   })
    // });

    const logout= document.querySelector('#logout');
    logout.addEventListener('click', (e) => {
      e.preventDefault();
      auth.signOut();
    });

  } else {
    document.querySelector("#content").innerHTML=`
    <form id="signup-form">
      <div class="input-field">
        <input type="email" id="signup-email" placeholder="Email" required />
      </div>
      <div class="input-field">
        <input type="password" placeholder="Choose password" id="signup-password" required />
      </div>

      <button class="btn yellow darken-2 z-depth-0">Sign up</button>
    </form>
    <HR>
    <form id="login-form">
      <div class="input-field">
        <input type="email" placeholder="Email" id="login-email" required />

      </div>
      <div class="input-field">
        <input type="password" id="login-password" placeholder="Pass" required />
      </div>
      <button class="btn yellow darken-2 z-depth-0">Login</button>
    </form>`;

    //Authentication

    //login
    const loginform= document.querySelector('#login-form');

    loginform.addEventListener('submit', (e) => {
      e.preventDefault();

      const email= loginform['login-email'].value;
      const password= loginform['login-password'].value;

      auth.signInWithEmailAndPassword(email,password).then( cred => {

        console.log(cred.user);
        loginform.reset();
      });
    });


    //signup
    const signupform= document.querySelector('#signup-form');

    signupform.addEventListener('submit', (e) => {
      e.preventDefault();

      const email= signupform['signup-email'].value;
      const password= signupform['signup-password'].value;

      auth.createUserWithEmailAndPassword(email,password).then(cred => {
        signupform.reset();
      });

    });

  }

});
