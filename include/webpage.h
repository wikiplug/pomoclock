//-------------------------SERVIDOR WEB. POMOCLOCK------------------------------------------------------
const char pomoclock[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Pomoclock</title>
    <!-- FONT AWESOME -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.1.1/css/all.min.css">
    <!-- FONT WORK SANS -->
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300&family=Roboto:wght@300;400;500&family=Work+Sans:wght@100;200;300&display=swap" rel="stylesheet">
    <!-- CUSTOM CSS -->
    <link rel="stylesheet" href="styles.css">
    <link rel="stylesheet" href="https://unpkg.com/boxicons@2.0.9/css/boxicons.min.css">
    <!-- JQUERY -->
    <script src="https://code.jquery.com/jquery-3.6.1.min.js"></script>
    
    <!------------ CSS----------------->    
<style>
* {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}

body {
    color: rgb(0, 0, 0);
    background-color: hsl(206, 27%, 80%);
    font-family: 'Poppins', sans-serif;
    margin: auto;
}

a {
    color: rgb(0, 0, 0);
    text-decoration: none;
}

ul { 
    list-style: none;
}

.container2 {
    width: 90%;
    margin: auto;
}

/* Navigation */
.nav-main {
    background-color: hwb(207 58% 31%);
    font-size: 25px;
    display: flex;
    justify-content: space-between;
    align-items: center;
    height: 100px;
    padding: 20px 0;
    margin-bottom: 70px;
}

.nav-brand {
    margin-top: 35px;
    width: 250px;
    height: 250px;
}

/* Nav Left */
.nav-main ul {
    display: flex;
}

.nav-main ul li {
    padding: 20px;
}

.nav-main ul li a:hover {
    border-bottom: 2px solid rgb(0, 0, 0); 
}

.nav-main ul.nav-menu {
    flex: 1;
    margin-left: 20px;
}

/* SHOWCASE */


.grid ul figure{
    margin: 0;
    padding: 0;
}

.grid ul {
    list-style: none;
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 80px;
}

.grid ul li {
    width: 25%;
}

.grid ul li figure {
    position: relative;
    padding: 20px;
}

.grid ul li figcaption {
    display: none;
    position: absolute;
    top: 20px;
    left: 15px;
    bottom: 20px;
    right: 70px;
    background: rgba(0, 0, 0, 0.8);
    text-align: center;
    padding: 15px;
    border-radius: 10px;
}

.grid p{
    color: #ffffff;
}

.grid ul li figure:hover figcaption{
    display: block;
}

p{
    animation-duration: 3s;
    animation-name: slidein;
}

@keyframes slidein {

    from {
        margin-left: 100%;
        width: 15%;
    }

    to{
        margin-left: 0%;
        width: 100%;
    }
}  

.grid img {
    width: 210px;
    height: 210px;
}

.contacto {
    margin: 50px;
}

.contacto p{
    text-align: center;
    font-size: 30px;
    margin-bottom: 30px;
}

.links {
    display: flex;
    align-items: center;
    justify-content: center;
}

.links a{
    margin: 0 30px;
}

.links a i{
    font-size: 3rem;
}

.proyecto h2{
    color: black 
}
.proyecto p{
    color:rgba(0, 0, 0, 0.8)
}
.proyecto a{
    color:rgba(0, 0, 0, 0.8)
}
.proyecto a:hover{
    border-bottom: 2px solid rgba(0, 0, 0, 0.8);
}

.grupo h2{
    color: black 
}
.grupo p{
    color:rgba(0, 0, 0, 0.8)
}
.grupo a{
    color:rgba(0, 0, 0, 0.8)
}
.grupo a:hover{
    border-bottom: 2px solid rgba(0, 0, 0, 0.8);
}

.escuela h2{
    color: black 
}
.escuela p{
    color:rgba(0, 0, 0, 0.8)
}
.escuela a{
    color:rgba(0, 0, 0, 0.8)
}
.escuela a:hover{
    border-bottom: 2px solid rgba(0, 0, 0, 0.8);
}


.proyecto {
    margin-top: 50px;
    width: 100%;
    height: 160px;
    background-color: hwb(207 58% 31%);
    border-radius: 7px;
}

.grupo {
    margin-top: 50px;
    width: 100%;
    height: 160px;
    background-color: hwb(207 58% 31%);
    border-radius: 7px;
}

.escuela {
    margin-top: 25px;
    width: 100%;
    height: 160px;
    background-color: hwb(207 58% 31%);
    border-radius: 7px;
}

.menubtn {
    position: absolute;
    cursor: pointer;
    top: 20px;
    right: 25px;
    z-index: 2;
    text-align: center;
}


.secciontoggleclima {
    align-items: center;
    justify-content: center;
    background: hsl(206, 27%, 80%);
    margin-top: 50px;
    margin-left: 600px;
}

.secciontoggleclima .titulo {
    background: rgb(0, 0, 0);
    width: 400px;
    border-radius: 7px;
}

.secciontoggleclima #dynRectangle1
    {
        width:0px;
        height:12px;
        top: 9px;
        background-color: rgb(0, 0, 0);
        z-index: -1;
        margin-top: 1px;
        border: 2px solid black;
        margin-left: 105px;
    }
.secciontoggleclima  #dynRectangle2
      {
        width:1px;
        height:12px;
        top: 9px;
        background-color: rgb(0, 0, 0);
        z-index: -1;
        margin-top: 1px;
        border: 2px solid black;
        margin-left: 105px;
    }
.secciontoggleclima  body   {background-color: hwb(0 0% 100%)}
.secciontoggleclima    h1     {font-size: 40px; color: hwb(0 0% 100%)(0, 0, 0); text-align:center; }
.secciontoggleclima    h2     {font-size: 25px; color: rgb(0, 0, 0)argin-top: 20px; text-align:center;}
.secciontoggleclima    h3     {font-size: 17px; color:hwb(0 0% 100%); text-align:center;}

.secciontoggleclima    div.h1 {background-color: #fcfcfc; width: 700px; font-size: 24px; border-radius: 7px; color: hsl(0, 0%, 0%); height: 280px;}


.secciontoggletime .time-display1{
    background-color: #fcfcfc;
    font-size: 24px; 
    border-radius: 7px; 
    color: hsl(0, 0%, 0%); 
    height: 170px;
    width: 700px;
    margin-top: 50px;
    align-items: center;
    text-align: center;
    margin-left: 600px;
}

.set-time1 {
    background-color:   rgb(125, 137, 147);
    border-color:  #cdbfbfd6;
    color: rgb(0, 0, 0);
    width: 155px;
    height: 35px;
    border-radius: 5px;
    font-size: 18px;
    font-weight:500;
    margin: 10px;
}
.set-time1:hover{
    background-color:  hsl(203, 12%, 79%);
}

.set-time2 {
    margin-top: -25px;
}

.secciontogglealarma {
    align-items: center;
    justify-content: center;
    background:hsl(206, 27%, 80%);;
    margin-top: 50px;
    margin-left: 700px;
}


.secciontogglealarma .container{
    align-content: center;
    text-align: center;
}


.secciontogglealarma .time-display{
    align-content: center;
    background: #ffffff;
    width: 700px;
    height: 350px;
    border-radius: 7px;
    padding-left: 5px;
    padding-right: 5px; 
    text-align: center;
    align-content: center;
    margin-left: -100px;
}


.secciontogglealarma .timer{
    width: 100px;
    height: 100px;
    margin-top: 7px;
    margin-right: 10px;
    margin-left: 15px;
}

.secciontogglealarma hr{
    color: white;
}

.secciontogglealarma #clock{
    font-size: 3rem;
    font-weight: bold;
    color: #000000;
    margin-left: 5px;

}

.secciontogglealarma label{
    color: #000000;
    margin-bottom: 20px;
    margin-top: 10px;
    padding-top: 50px;
    font-size: 24px;
}

.secciontogglealarma h3{
    margin-left: 38px;
}

.secciontogglealarma .alarm-heading{
    color: rgb(0, 0, 0);
    margin-bottom: 20px;
    margin-top: 10px;
    padding-top: 15px;
    font-size: 24px;
}

.secciontogglealarma .set-alarm-field{
    margin-top: -20px;
    height: 20px;
    padding-top: 0px;
    margin-bottom: 30px;
}

.secciontogglealarma .set-alarm-field .minuto{
    margin-top: 10px;
    height: 25px;
    width: 75px;
}

.secciontogglealarma .set-alarm-field .segundos{
    margin-top: 10px;
    height: 25px;
    width: 75px;

}

.secciontogglealarma .set-alarm-field .alarm{
    margin-top: 10px;
    height: 25px;
    width: 75px;

}

.secciontogglealarma .set-alarm-field .hora{
    height: 25px;
    width: 75px;
}

.secciontogglealarma .controls button{
    background-color:   rgb(125, 137, 147);;
    border-color: rgb(125, 137, 147);
    color: #000000;
    width: 155px;
    height: 35px;
    border-radius: 5px;
    font-size: 18px;
    font-weight:500;
    margin: 5px;
}

.secciontogglealarma .controls button:hover{
    background-color:  hsl(207, 9%, 62%);
}

.secciontogglealarma #myList{
    list-style-type: none;
    
}

.secciontogglealarma #myList li{
    font-size: 24px;
    color: rgb(0, 0, 0);
    background-color:  rgb(125, 137, 147);
    height: 50px;
    margin-left: 100px;
    border-radius: 4px;
    padding-left: 16px;
    padding-top: 5px;
    width: 280px;
    margin-bottom: 10px;
    margin-left: px;
    
}


.secciontogglealarma .time-list span{
    width: 180px;
    margin-right: 18px;
}

.secciontogglealarma .time-list button{
    background-color:  rgb(125, 137, 147);
    border-color:  hsl(208, 9%, 73%);
    border-radius: 3px;
    border-width: 2px;
    height: 40px;
    font-size: 16px;
    color: rgb(0, 0, 0);
    margin-right: 20px;

}
</style>
</head>
 <!------------ HTML----------------->
<body>
    <nav class="nav-main">

        <img src="img/pomoimg.png" alt="Pomoclock LOGO" class="nav-brand">
        <ul class="nav-menu">
            <li>
                <a href="index.html#proyectocon">Proyecto</a>
            </li>
            <li>
                <a href="index.html#grupocon">Grupo</a>
            </li>
            <li>
                <a href="index.html#escuelacon">Escuela</a>
            </li>
            <li>
                <a href="index.html#contactocon">Contacto</a>
            </li>
        </ul>
        <ul class="nav-menu-right">
            <li>
                <a href="#">
                    <i class="fas fa-search"></i>
                </a>
            </li>
        </ul>

    </nav>

    <section class="secciontoggleclima" id="secciontoggle1">

        <div class="h1"> 
            <h1>Temperatura - Pomoclock</h1>
            <h2>
                Temperatura: <span style="color:rgb(0, 0, 0)" id="Tempvalue">0</span> C<br>
                Humedad: <span style="color:rgb(0, 0, 0)" id="Humvalue">0</span> % <br
            </h2>
            <h3>
                0 C &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;
                &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 50 C
                <div id="dynRectangle1"></div><br>
                0 % &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;
                &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 100 %
                <div id="dynRectangle2"></div><br>
            </h3>

        </div>
        
    </section>

    <section class="secciontoggletime" id="secciontoggle2">

        <div class="time-display1">

              <form class= "tiempo" action="tiempo" method="get"> 
            <label class="time-heading1"><h3>Pomoclock - HORA</h3><label><br>
                <div class="set-time2">
                    <input class="hora" type="number" name="t_hour" id="t_hour" placeholder="Hora" max="23" min="00">
                    <input class="minuto" type="number" name="t_min" id="t_min" placeholder="Minuto" max="59" min="00">
                     <button type="set" class="set-time1" name="set-time1" value="1">Setear</button>
                </div>
            </form> 
        </div>
        
    </section>

    <section class="secciontogglealarma" id="secciontoggle3">

        <div class="time-display">
            <img class="timer" src="https://cdn.icon-icons.com/icons2/2469/PNG/512/alarm_clock_icon_149537.png">
            <div id="clock"></div>

                <form class= "alarma" action="alarma" method="get" >
                    <label class="alarm-heading1"><h3>Pomoclock - Alarmas</h3><label><br>
                    <div class="set-alarm-field">
                        <input class="hora" type="number" name="a_hour" id="a_hour" placeholder="Hora" max="23" min="00">
                        <input class="minuto" type="number" name="a_min" id="a_min" placeholder="Minuto" max="59" min="00">
                        <input class="alarm" type="number" name="alarm" id="alarm" placeholder="Alarma" max="4" min="1">
                    </div>
                    <div class="controls">
                        <button type="set" class="state" name="state" value="1">Programar Alarma</button>
                        <button type="clear" class="state" name="state" value="0" >Quitar Alarma</button>
                    </div>
                </form>     
        </div>
    </section>

    <div class="container2">
        <!-- INFORMACIÓN -->

        <section class="proyecto">

             <div class="contenido">
                <h2> <a name="proyectocon"></a> Proyecto</h2>
                <p>El proyecto consiste en un reloj multifunción, el cual, además de mostrar la hora en un display de 7 segmentos,
                    tendrá la función de alarma con posibilidad de programar hasta 6 alarmas, un timer y función pomodoro programable.</p> 
                      
                <p> POMOCLOCK tiene como fin satisfacer la necesidad de nuestro consumidor, mejorando su calidad en corto o largo plazo
                    y poder ser el producto que solucione las necesidades insatisfechas del mercado. </p>
                <p>   Tiene como propósito implementar un método de organización y estudio en los relojes inteligentes.   </p>                                                             
                
             </div>

        </section>

        <section class="grupo">

            <div class="contenido2">
                <h2> <a name="grupocon"></a> Grupo</h2>
                <p>
                   Joaquín Cardenas: Encargado en la programación orientada a objetos. Programación del microcontrolador.</p>
                   
                   <p> Dana Egochine: Encargada en la programación orientada a objetos y programación del Wi-Fi Manager.</p>
                   
                    <p> Facundo Flores: Encargado de investigación y programación del Wi-Fi Manager.</p>
                   
                        <p> Mateo Fernandez: Encargado de diseñar la estructura del proyecto.</p>
                        
                            <p> Pablo Iñiguez: Encargado de la creación de la página web. Encargado de los informes y del manual.</p>
                
            </div>

        </section>

        <section class="escuela">

            <div class="contenido3">
                <h2> <a name="escuelacon"></a> Escuela</h2>
                <p>La localización de desarrollo de nuestro emprendimiento empezó en el establecimiento escolar (E. E. S. T Nº2 Paula A. de Sarmiento),
                esto a causa de que uno de los motivos principales fue impartida por la materia “proyecto y diseño electrónico”, además 
                en el establecimiento contamos con variedad de computadoras, a disposición de los alumnos para poder trabajar y realizar
                 la programación del proyecto en cuestión (Pomoclock), así como también poder desarrollar el gabinete necesario para el trabajo,
                  este será desarrollado en impresión 3d, ya que la escuela cuenta con impresoras 3D lo que nos permita avanzar con esta tarea.
                </p>
            </div>
            
        </section>

        <section class="contacto">
            
            <p>  <a name="contactocon"></a> Seguinos</p>
        
            <div class="links">
                
                <a href="https://www.instagram.com/pomocl0ck/">
                    <i class="fa-brands fa-instagram"></i>
                </a>
                <a href="#">
                    <i class="fa-brands fa-twitter"></i>
                </a>
                <a href="#">
                    <i class="fa-brands fa-facebook"></i>
                </a>

            </div>
            
        </section>

    </div>
 <!------------ JAVASCRIPT----------------->    
<script>
    InitWebSocket()
  function InitWebSocket()
  {
    websock = new WebSocket('ws://'+window.location.hostname+':81/');
    websock.onmessage=function(evt)
    {
       JSONobj = JSON.parse(evt.data);
       document.getElementById('Tempvalue').innerHTML = JSONobj.TEMP;
       var temp = parseInt(JSONobj.TEMP * 9.5);
       document.getElementById("dynRectangle1").style.width = temp+"px";
       
       document.getElementById('Humvalue').innerHTML = JSONobj.HUM;
       var hum = parseInt(JSONobj.HUM * 4.8);
       document.getElementById("dynRectangle2").style.width = hum+"px";

       document.getElementById('FANbtn').innerHTML = JSONobj.LEDonoff;
    }
  }
  //----------------------------------------------------
  function fanONOFF()
  {
    FANbtn = 'LEDonoff=ON';
    if(document.getElementById('FANbtn').innerHTML == 'ON')
    {
      FANbtn = 'LEDonoff=OFF';
    }
    websock.send(FANbtn);
  }

    const display = document.getElementById('clock');


// set audio for alarm
const audio = new Audio('https://assets.mixkit.co/sfx/preview/mixkit-alarm-digital-clock-beep-989.mp3');
audio.loop = true;


let alarmTime = null;
let alarmTimeout = null;


const myList = document.querySelector('#myList');
const addAlarm = document.querySelector('.alarma')


const alarmList = [];  // Stores all the alarms being set 
// let count =1;


// Plays the alarm audio at correct time
function ringing(now){
    audio.play();
    alert(`Hey! it is ${now}`)
}


// updates time every second 
function updateTime() {
    var today = new Date();
    const hour = formatTime(today.getHours());
    const minutes = formatTime(today.getMinutes());
    const seconds = formatTime(today.getSeconds());
    const now = `${hour}:${minutes}:${seconds}`;

    display.innerText=`${hour}:${minutes}:${seconds}`;
    
//     check if the alarmList includes the current time , "now"
//     if yes, ringing() is called
    if(alarmList.includes(now) ){
        ringing(now);
    } 
}


// set the correct format of time
// converts "1:2:3" to "01:02:03"
function formatTime(time) {
    if ( time < 10 && time.length != 2) {
        return '0' + time;
    }
    return time;
}


// function to clear/stop the currently playing alarm
function clearAlarm() {
    audio.pause();
    if (alarmTimeout) {
        clearTimeout(alarmTimeout);
        alert('Alarm cleared');
    }
}      


// removes an alarm from the unordered list and the webpage when "Delete Alarm" is clicked
myList.addEventListener('click', e=> {
    console.log("removing element")
    if(e.target.classList.contains("deleteAlarm")){
        e.target.parentElement.remove();
    }    
})


// removes an alarm from the array when "Delete Alarm" is clicked
remove = (value) => {
    let newList = alarmList.filter((time) => time != value);
    alarmList.length = 0;                  // Clear contents
    alarmList.push.apply(alarmList, newList);
    
    console.log("newList", newList);
    console.log("alarmList", alarmList);
}


// Adds newAlarm to the unordered list as a new list item on webpage
function showNewAlarm(newAlarm){
    const html =`
    <li class = "time-list">        
        <span class="time">${newAlarm}</span>
        <button class="deleteAlarm time-control" id="delete-button" onclick = "remove(this.value)" value=${newAlarm}>Borrar alarma</button>       
    </li>`
    myList.innerHTML += html
};


// event to set a new alarm whenever the form is submitted 
addAlarm.addEventListener('submit', e=> {
    e.preventDefault();
    // const newAlarm = addAlarm.alarmTime.value;
    let new_h=formatTime(addAlarm.a_hour.value);
    if(new_h === '0'){
        new_h = '00'
    }
    let new_m=formatTime(addAlarm.a_min.value);
    if(new_m === '0'){
        new_m = '00'
    }
    let new_s=formatTime(addAlarm.a_sec.value);
    if(new_s === '0'){
        new_s = '00'
    }
    
    const newAlarm = `${new_h}:${new_m}:${new_s}`

//     add newAlarm to alarmList
    if(isNaN(newAlarm)){
        if(!alarmList.includes(newAlarm)){
            alarmList.push(newAlarm);
            console.log(alarmList);
            console.log(alarmList.length);
            showNewAlarm(newAlarm);
            addAlarm.reset();
        } else{
            alert(`La alarma para las ${newAlarm} ya fue programada`);
        }
    } else{
        alert("Tiempo incorrecto")
    }        
})


// calls updateTime() every second
setInterval(updateTime, 1000);

</script>

</body>
</html>

)=====";