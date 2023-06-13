char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-9ndCyUaIbzAi2FUVXJi0CjmCapSmO7SnpJef0486qhLnuZ2cdeRhO02iuK6FUUVM" crossorigin="anonymous">
    <title>Document</title>
    <script>
        
        function fillDrink(event){
          const id = event.target.id
          console.log(`/drink${id}`)
          fetch(`/drink${id}`)
            .then(response=>{
              if (response.ok) {
                return response.text();
              } else {
                throw new Error(`Error en la solicitud para el ${id} Drink`);
              }
            })
            .then(data => {
              console.log(data);
            })
            .catch(error => {
              console.error(error);
            })
        } 

        

        function submitValues() {
          let drink1 = parseInt(document.getElementById('percentage-range1').value);
          let drink2 = parseInt(document.getElementById('percentage-range2').value);
          let drink3 = parseInt(document.getElementById('percentage-range3').value);
          let result = drink1 + drink2 + drink3  

          result==100 
            ? mixValues(drink1,drink2,drink3)
            : result > 100
              ? console.log("this is more than 100%")
              : console.log("must be 100%")
                  
        }

        function mixValues(drink1,drink2,drink3){
          fetch(`/drink1/${drink1}/drink2/${drink2}/drink3/${drink3}`)
          .then(response=>{
              if (response.ok) {
                return response.text();
              } else {
                throw new Error(`Error en la solicitud para el mix Drink`);
              }
            })
            .then(data => {
              console.log(data);
            })
            .catch(error => {
              console.error(error);
            })
        }

        function updateRangeValue() {
          let range = document.getElementById('percentage-range');
          let value = range.value;
          let rangeValue = document.getElementById('range-value');
          rangeValue.textContent = value + '%';
        }
        function updateRangeValue(drinkNumber) {
          let range = document.getElementById('percentage-range' + drinkNumber);
          let value = range.value;
          let rangeValue = document.getElementById('range-value' + drinkNumber);
          rangeValue.textContent = value + '%';
        }
      </script>
</head>
<body onload="javascript:init()" class="vh-100 bg-dark d-flex flex-column justify-content-center align-items-center gap-3">
    <div class="d-flex justify-content-center align-items-center gap-3">
        <div>
            <button class="btn btn-secondary" id="1" onclick="fillDrink(event)">1st Drink</button>
          </div>
          <div>
              <button class="btn btn-secondary" id="2" onclick="fillDrink(event)">2nd Drink</button>
          </div>
          <div>
              <button class="btn btn-secondary" id="3" onclick="fillDrink(event)">3rd Drink</button>
          </div>
    </div>
    <div class="d-flex flex-column align-items-center justify-content-center gap-3">
        <h3 class="text-light">For a mix:</h3>
        <div class="text-light">
            <div>1st Drink:</div>
            <div class="d-flex align-items-center justify-content-center gap-3">
                <input type="range" id="percentage-range1" min="0" max="100" step="10" onchange="updateRangeValue(1)" oninput="updateRangeValue(1)">
                <div id="range-value1" style="width: 30px;">0%</div>
            </div>
        
          </div>
        
          <div class="text-light">
            <div>2nd Drink:</div>
            <div class="d-flex align-items-center justify-content-center gap-3">
                <input type="range" id="percentage-range2" min="0" max="100" step="10" onchange="updateRangeValue(2)" oninput="updateRangeValue(2)">
                <div id="range-value2" style="width: 30px;">0%</div>
            </div>
        
          </div>
        
          <div class="text-light">
            <div>3rd Drink:</div>
            <div class="d-flex align-items-center justify-content-center gap-3">
                <input type="range" id="percentage-range3" min="0" max="100" step="10" onchange="updateRangeValue(3)" oninput="updateRangeValue(3)">
                <div id="range-value3" style="width: 30px;">0%</div>
            </div> 
          </div>
          <button class="btn btn-success" onclick="submitValues()">Enviar</button>
    </div>  
    
  </body>
</html>
)=====";

