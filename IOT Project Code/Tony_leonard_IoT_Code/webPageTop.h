void printWebPage(dht DHT, float SM, WiFiEspClient client)
{
  //Layout of webserver
  //uses different shades of green to make a fade like design
  //colours found on W3 schools
  client.print(F(R"=====(
<!DOCTYPE HTML>
<html>
  <head>
    <style>
      p, body, button {
      font-size: 20px;
      text-align: center;
      margin: 0;
      }
      .sensor-row {
        display: flex;
        flex-direction: row;
        border: 1px solid Black;
        padding: 5px;
      }
      .sensor-row-inner {
        padding: 5px;
        text-align: center;
        width: 50%;
        border: 5px solid GreenYellow;
      }
       .sensor-row-inner1 {
        padding: 5px;
        text-align: center;
        width: 50%;
        border: 5px solid LawnGreen;
       }
      .sensor-row-inner2 {
       padding: 5px;
       text-align: center;
       width: 50%;
       border: 5px solid Lime;
       }
    </style>
  </head>
  
  <h1 style="background-color:LawnGreen; text-align: center;">Independent Growth Greenhouse</h1>
  <div class="sensor-row">
    <div class="sensor-row-inner">
      //Displays temperature on webserver
      <p>Temperature: 
)====="));

  client.print(DHT.temperature);
  client.print(F(R"=====( 
  Degrees C</p>
    </div>
    <div class="sensor-row-inner">
    //Allows user to turn off and on fan
     <a href="/z1"><button type="button" >Turn Fan On!</button></a>
     <a href="/z0"><button type="button" >Turn Fan Off!</button></a>
    </div>
   </div>
 <div class="sensor-row">
   <div class="sensor-row-inner1">
          //Displays humidity on webserver
          <p>Humidity:  
          )====="));
  client.print(DHT.humidity);
  client.print(F(R"=====(
            %</p>
      </div>
    <div class="sensor-row-inner1">
    //Allows user to turn off and on fan
    <a href="/z1"><button type="button" >Turn Fan On!</button></a>
    <a href="/z0"><button type="button" >Turn Fan Off!</button></a>
    </div>
 </div>
 <div class="sensor-row">
   <div class="sensor-row-inner2">
          //Displays soil moisture on webserver
            <p>Soil Moisture: 
          )====="));
  client.print(SM);
  client.println(F(R"=====(
            %</p>
      </div>
    <div class="sensor-row-inner2">
     //Allows user to turn off and on pump
     <a href="/P1"><button type="button" >Turn Pump On!</button></a>
     <a href="/P0"><button type="button" >Turn Pump Off!</button></a>
    </div>
 </div>
            </html>
          )====="));
}
