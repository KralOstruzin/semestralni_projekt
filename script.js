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
        const {icon, description} = data.weather[0];
        const {temp, humidity} = data.main;
        const {speed} = data.wind;
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

 document.querySelector(".tlacitko").addEventListener("click", function () {
    pocasi.vyhledávání();
  });



