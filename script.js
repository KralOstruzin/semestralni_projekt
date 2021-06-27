
document.querySelector(".tlacitko").addEventListener("click", function () {
    pocasi.vyhledávání();
  });

let pocasi = {
    apiKey : "a7b08b2690bedbf404529e629a6dc21b",
    nactenipocasi: function (mesto) {    
        fetch(
            "http://api.openweathermap.org/data/2.5/weather?q="
            + mesto
            + "&units=metric&appid="
            + this.apiKey
        )
    .then((response) => response.json())
    .then((data) =>this.zobrazdata(data));
    },
    zobrazdata: function(data) {
            const {name} = data;
            localStorage.setItem("mesto",name); 
            
            const {icon, description} = data.weather[0];
            localStorage.setItem("ikonka", icon);
            localStorage.setItem("popis", description);

            const {temp, humidity} = data.main;
            localStorage.setItem("teplota", temp);
            localStorage.setItem("vlhkost", humidity);

            const {speed} = data.wind;
            localStorage.setItem("vitr", speed);

            document.querySelector(".mesto").innerText =  name;
            document.querySelector(".teplo").innerText =  temp + " °C";
            document.querySelector(".ikonka").src = "https://openweathermap.org/img/wn/" + icon + ".png";
            document.querySelector(".podrobnosti").innerText =   description;
            document.querySelector(".vlhkost").innerText = "Vlhkost: " + humidity + " %";
            document.querySelector(".vetrno").innerText = "Rychlost větru: " + speed + " km/h";
            
    },
    vyhledávání: function () {
        this.nactenipocasi(document.querySelector(".vyhledej").value);
     
    
    },
 };

    let mestopocasi = localStorage.getItem("mesto");
    let ikonkaPocasi = localStorage.getItem("ikonka");
    let popisIkonky = localStorage.getItem("popis");
    let teplota = localStorage.getItem("teplota");
    let vlhkost = localStorage.getItem("vlhkost");
    let vitr = localStorage.getItem("vitr");

    document.querySelector(".mesto").innerText =  mestopocasi;
    document.querySelector(".teplo").innerText =  teplota + " °C";
    document.querySelector(".ikonka").src = "https://openweathermap.org/img/wn/" + ikonkaPocasi + ".png";
    document.querySelector(".podrobnosti").innerText =   popisIkonky;
    document.querySelector(".vlhkost").innerText = "Vlhkost: " + vlhkost + " %";
    document.querySelector(".vetrno").innerText = "Rychlost větru: " + vitr + " km/h";
