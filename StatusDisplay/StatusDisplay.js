//defines:
var IO_SOCKET_SERVER_URL = 'http://localhost:8080/';
var logfile = "log/events.log"

fs = require('fs');
var ios = require('socket.io-client');
var socket = ios.connect(IO_SOCKET_SERVER_URL, {
    reconnection: true
});

//var gYellowLight = 'OFF'; //TODO: these are note really needed!?
//var gGreenLight = 'OFF';
//var gRedLight = 'OFF';
//var gStatusReportCount = 0;

//function isJson(item) {
//    item = typeof item !== "string"
//        ? JSON.stringify(item)
//        : item;

//    try {
//        item = JSON.parse(item);
//    } catch (e) {
//        return false;
//    }

//    if (typeof item === "object" && item !== null) {
//        return true;
//    }

//    return false;
//};

socket.on('connect', function () {
    console.log("Connected to " + IO_SOCKET_SERVER_URL );
});

socket.on('disconnect', function () {
    console.log("Disconnected from " + IO_SOCKET_SERVER_URL );
});

socket.on('controllino_status', function (data) {
    console.log(data);
    /*
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
    */
});
