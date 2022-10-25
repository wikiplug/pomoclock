//=====================
//HTML code for webpage
//=====================
const char webpageCont[] PROGMEM = 
R"=====(
<!DOCTYPE html>
<html lang="en">
<!--------------------------CSS------------------------->
<head>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Poppins:wght@300&family=Roboto:wght@300;400;500&family=Work+Sans:wght@100;200;300&display=swap');

        *{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Poppins', sans-serif;
            }

        body, .titulo, .contenido {
            display: flex;
            align-items: center;
            justify-content: center;
                }

        body {
            background: #43AFFC;
            min-height: 100vh;
            }

        .titulo {
    background: #ffff;
    width: 440px;
    border-radius: 10px;
    flex-direction: column;
    padding: 30px 30px 38px;
}

.titulo img {
    max-width: 103px;
}

.titulo h1 {
    font-size: 38px;
    font-weight: 500;
    margin: 30px 0;
}

.titulo .contenido {
    width: 100%;
    justify-content: space-between;
}

.titulo .contenido.disable {
    opacity: 0.5;
    pointer-events: none;
}

.contenido .columna {
    border-radius: 5px;
    border: 1px solid #999;
    width: calc(100% / 3 - 5px);
    padding: 0 10px;
}

.columna select {
    outline: none;
    border: none;
    height: 53px;
    width: 100%;
    font-size: 19px;
}

.titulo button {
    width: 100%;
    outline: none;
    border: none;
    margin-top: 20px;
    font-size: 20px;
    padding: 17px 0;
    border-radius: 5px;
    background: #43AFFC;
    color: #ffff;
    cursor: pointer;
}
    </style>
</head>
<!--------------------------HTML------------------------->
<body>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Alarma - Pomoclock</title>
    <div class="titulo">
        <img src="img/alarma.img.png" alt="">
        <h1>00:00:00</h1>
        <div class="contenido">
            <div class="columna">
                <select>
                    <option value="Hora" selected hidden>Hora</option>
                </select>
            </div>
            <div class="columna">
                <select>
                    <option value="Minuto" selected hidden>Minuto</option>
                </select>
            </div>
            <div class="columna">
                <select>
                    <option value="AM/PM" selected hidden>AM/PM</option>
                </select>
            </div>
        </div>
        <button>Crear Alarma</button>
    </div>

    <script>
        const tiempoActual = document.querySelector("h1"),
contenido = document.querySelector(".contenido"),
seleccionMenu = document.querySelectorAll("select"),
botonAlarma = document.querySelector("button");

let tiempoAlarma, crearAlarmaEs,
ringtone = new Audio("./img/ringtone.mp3");

for (let i = 12; i > 0; i--) {
    i = i < 10 ? `0${i}` : i;
    let option = `<option value="${i}">${i}</option>`;
    seleccionMenu[0].firstElementChild.insertAdjacentHTML("afterend", option);
} 

for (let i = 59; i > 0; i--) {
    i = i < 10 ? `0${i}` : i;
    let option = `<option value="${i}">${i}</option>`;
    seleccionMenu[1].firstElementChild.insertAdjacentHTML("afterend", option);
} 

for (let i = 2; i > 0; i--) {
    let ampm = i == 1 ? "AM" : "PM";
    let option = `<option value="${ampm}">${ampm}</option>`;
    seleccionMenu[2].firstElementChild.insertAdjacentHTML("afterend", option);
} 

setInterval(() => {
    let date = new Date(),
    h = date.getHours(),
    m = date.getMinutes(),
    s = date.getSeconds(),
    ampm = "AM";

    if (h >= 12){
        h = h - 12;
        ampm = "PM";
    }

    h = h == 0 ? h = 12 : h;

    h = h < 10 ? "0" + h : h;
    m = m < 10 ? "0" + m : m;
    s = s < 10 ? "0" + s : s;
    tiempoActual.innerText = `${h}:${m}:${s} ${ampm}`;

    if(tiempoAlarma == `${h}:${m} ${ampm}`){
        ringtone.play();
        ringtone.loop = true;
    }
}, 1000);

function crearAlarma() {

    if(crearAlarmaEs) {
        tiempoAlarma = "";
        ringtone.pause();
        contenido.classList.remove("disable");
        botonAlarma.innerText = "Crear alarma";
        return crearAlarmaEs = false;
    }

    let tiempo = `${seleccionMenu[0].value}:${seleccionMenu[1].value} ${seleccionMenu[2].value}`;

    if(tiempo.includes("Hora") || tiempo.includes("Minuto") || tiempo.includes("AM/PM")){
        return alert("Porfavor, elegí un tiempo válido.")
    }

    crearAlarmaEs = true;
    tiempoAlarma = tiempo;
    contenido.classList.add("disable")
    botonAlarma.innerText = "Deshacer alarma"
}

botonAlarma.addEventListener("click", crearAlarma);

    </script>

</body>
</html>
)=====";