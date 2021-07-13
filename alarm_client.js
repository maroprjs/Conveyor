//defines:
var IO_SOCKET_SERVER_URL = 'http://10.200.20.153:8282/';
var logfile = "log/events.log"

fs = require('fs');
var ios = require('socket.io-client');
var socket = ios.connect(IO_SOCKET_SERVER_URL, {
    reconnection: true
});

var gYellowLight = 'OFF'; //TODO: these are note really needed!?
var gGreenLight = 'OFF';
var gRedLight = 'OFF';
var gStatusReportCount = 0;

function isJson(item) {
    item = typeof item !== "string"
        ? JSON.stringify(item)
        : item;

    try {
        item = JSON.parse(item);
    } catch (e) {
        return false;
    }

    if (typeof item === "object" && item !== null) {
        return true;
    }

    return false;
};

socket.on('connect', function () {
    console.log("Connected to " + IO_SOCKET_SERVER_URL );
});

socket.on('disconnect', function () {
    console.log("Disconnected from " + IO_SOCKET_SERVER_URL );
});

socket.on('hari_report', function (data) {
    //console.log(data);
    if ( isJson(data) === true ){
       if(data.hasOwnProperty('reports')){
          fs.appendFile(logfile, JSON.stringify(data) + "\n", function (err) {
              if (err) return console.log(err);
              console.log('data > logfile');
          });
          //console.log(data);
          var valueObj = JSON.parse(data.reports[0].value);
          //console.log(valueObj);
          var classObj = valueObj.stats[0].class;
          //console.log(valueObj.stats[0].class);
          if (classObj == 'person') { //perimeter alarm
              socket.emit('command', 'p'); //red on //will be turned off again when wenn motor is manually turned on 
              gRedLight = 'ON';
              socket.emit('command', 'z'); //motor off
              gStatusReportCount = 0;
          };
       }else{
          console.log("incmming data no reports property");
       };
    }else{
       console.log("incmming data invalid JSON");
    };

});

socket.on('status_report', function (data) { //conveyor status; received once per sec
    //var obj = (data);
    //console.log(data);
    //--- extract conveyor belt status: ---
    var statusElementArray = data.split(',');
    var msgID = statusElementArray[0]; //if status providers grow, we need distinction (msg id for conveyor control = 1)
    var elecPwr = (statusElementArray[1] == '1') ? "ON" : "OFF";
    var motorPwr = (statusElementArray[2] == '1') ? "ON" : "OFF";
    var direction = (statusElementArray[3] == '1') ? "FORWARD" : "REVERSE";
    var speedRPM = statusElementArray[4];
    var setPWM = statusElementArray[5]; //setPWM may be unequal zero during direction change
    //--- handle green light: ---
    if (motorPwr == "ON"){
       socket.emit('command', 'v'); //green on
       socket.emit('command', 'q'); //red off
       gGreenLight = 'ON';
       gRedLight = 'OFF';
    };
    if (motorPwr == "OFF"){
       socket.emit('command', 'w'); //green off
       gGreenLight = 'OFF';
    };
    //--- handle yellow light: ---
    if (elecPwr == "ON"){ //steady yellow light when elec is on  and zero speed and blinkg at speed
       var cmd = 'k';
       if (setPWM > 15){
          cmd = (gYellowLight == 'OFF') ? 'k' : 'l';
          socket.emit('command', cmd); 
          gYellowLight = (gYellowLight == 'OFF') ? 'ON' : 'OFF';
       }else{
          socket.emit('command', 'k'); //yellow on
          gYellowLight = 'ON';;
       };
    };
    if (elecPwr == "OFF"){
       socket.emit('command', 'l'); //yellow off
       gYellowLight = 'OFF';
    };
    //--- turn off red light intrusion if no one manually disables it: ---
    if (gRedLight == 'ON'){ 
       gStatusReportCount++;
       if (gStatusReportCount > 300){ //= 5 min; status reports are comming once per sec
          socket.emit('command', 'q'); //red off
          gRedLight = 'OFF';
          gStatusReportCount = 0;
       };
    };
});
