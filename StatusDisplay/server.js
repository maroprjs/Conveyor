/*******************
    server.js for CBD Status Display

    -bridges udp messages between controllino and remote server (demo-) laptop
    -exposes htpp server for administrative configuration
    -exposes socketIO for Status Display on Raspberry (as own socketIO client)
*/


//defines:
var THIS_SERVER_IP = '0.0.0.0';
var REMOTE_SERVER_IP = '127.0.0.1';
var THIS_SERVER_HTTP_PORT = 8080; //same used for IO and admin
//var HARI_POST_PORT = 8283; //this is for cam notifications
var THIS_SERVER_UDP_PORT_1 = 4555; //to receice controllino status
var THIS_SERVER_UDP_PORT_2 = 4556; //to receice XDK Measurements
var REMOTE_SERVER_UDP_PORT_1 = 5555; //to receice controllino status
var REMOTE_SERVER_UDP_PORT_2 = 5556; //to receice XDK Measurements

//var CONVEYOR_IP = '10.200.20.132';
//var CONVEYOR_UDP_PORT = 3333; //to send commands to

//dependencies and global variables:
var express = require('express');
var app = express();
//var hari = express(); //this is for cam notifications
var http = require('http').createServer(app);
//var hari_post = require('http').createServer(hari); //this is for cam notifications
var ioSocket = require('socket.io')(http);
var dgram = require('dgram');
//var bodyParser = require("body-parser"); //for POST requests from cam
var udpdserver1 = dgram.createSocket('udp4'); //to receice controllino status
var udpdserver2 = dgram.createSocket('udp4'); //to receice XDK Measurements

//------------------ app: -------------------------------------------
// Webserver
http.listen(THIS_SERVER_HTTP_PORT, () => {
 console.log("Http Get Server running on port " + THIS_SERVER_HTTP_PORT );
});

// use static data
app.use(express.static(__dirname + '/public'));
// call path 
app.get('/', function (req, res) {
    // open the file
    res.sendfile(__dirname + '/public/index.html');
});

app.get("/admin", (req, res, next) => {
        //TODO: minimum admin thisServerIP, thisServerPort, remoteServerIP, remoteServerPort
                //add on: control controllino from here?
	if (req.param('raspberry')){
		if (req.param('raspberry') == "reboot"){
			var result = runCmd("do something");
			console.log(result);
			res.status(200).send( '{"msg":"reboot requested"}' ); 
		};
		if (req.param('raspberry') == "shutdown"){
			var result = runCmd("do something");
			console.log(result);
			res.status(200).send( '{"msg":"shutdown requested"}' ); 
		};		
	}

});

//-------------- hari: -----------------------------------------------
// Webserver for camera notifications as POST
//hari_post.listen(HARI_POST_PORT, () => { //this is for cam notifications
// console.log("Hari Post Server running on port " + HARI_POST_PORT );
//});
 
//hari.use(bodyParser.urlencoded({ extended: false })); //Here we are configuring express to use body-parser as middle-ware to parse POST requests.
//hari.use(bodyParser.json());

//hari.post('/hari', (req, res) => {
//	var msg = (req.body)
//        console.log('Got body:', msg);
        //TODO: alarm-/notification specific actions here
//        if(ioSocket){
                //console.log("inside socket");
//                ioSocket.emit('hari_report',msg);
//        };
//        res.sendStatus(200);
//});

//hari.post('/test', (req, res) => {
//        var msg = (req.body)
//        console.log('Got body:', msg);
        //TODO: alarm-/notification specific actions here
//        if(ioSocket){
                //console.log("inside socket");
//                ioSocket.emit('hari_report',msg);
//        };
//        res.sendStatus(200);
//});

//----------------- IO Socket ----------------------------------------
ioSocket.sockets.on('connection', function (socket) {
    console.log("connectio");
    socket.on('adduser', function () {
        socket.room = 'user';
        socket.join('user');
        console.log('User ' + socket.id + ' connected.');
    });
    // when the user log out.. perform this
    socket.on('logout', function () {
        // echo globally that this client has left
        socket.leave(socket.room);
        console.log('User ' + socket.id + ' left.');
    });
    // when the user disconnects.. perform this
    socket.on('disconnect', function () {
        socket.leave(socket.room);
        console.log('User ' + socket.id + ' disconnected.');
    });
    socket.on('send-clients', function (data) {});
    //socket.on('command', function (data) {
    //    console.log(data.toString());
    //    var umsg = Buffer.from( data );
    //    var udp_client = dgram.createSocket('udp4');
    //    udp_client.send(umsg, 0, umsg.length, CONVEYOR_UDP_PORT, CONVEYOR_IP, function(error) {
    //      if(error){
    //        udp_client.close();
    //        //sendUdpMsg( );
    //      }else{
    //        udp_client.close();
    //        console.log('sent UDP: ' + umsg);
    //      }
    //    });

    //});
});

//------------------------ udp function ---------------------------------
// udp listener controllino:
udpdserver1.on('listening', function () {
    var address = udpdserver1.address();
    console.log('UDP Server for Controllino listening on ' + address.address + ":" + address.port);
});

udpdserver1.on('message', function (message, remote) {
    	console.log(remote.address + ':' + remote.port + ' - ' + message.toString());
	if(ioSocket){
                //console.log("inside socket");
		ioSocket.emit('controllino_status',message.toString());
	};
        var umsg = Buffer.from( data );
        var udp_client = dgram.createSocket('udp4');
        udp_client.send(umsg, 0, umsg.length, REMOTE_SERVER_UDP_PORT_1, REMOTE_SERVER_IP, function(error) {
          if(error){
            udp_client.close();
            //sendUdpMsg( );
          }else{
            udp_client.close();
            console.log('sent UDP: ' + umsg);
          }
        });
});

udpdserver1.bind(THIS_SERVER_UDP_PORT_1, THIS_SERVER_IP);

// udp listener XDK:
udpdserver2.on('listening', function () {
    var address = udpdserver2.address();
    console.log('UDP Server for XDK listening on ' + address.address + ":" + address.port);
});

udpdserver2.on('message', function (message, remote) {
        console.log(remote.address + ':' + remote.port + ' - ' + message.toString());
        if(ioSocket){
                //console.log("inside socket");
                ioSocket.emit('xdk_measurement',message.toString());
        };
        var umsg = Buffer.from( data );
        var udp_client = dgram.createSocket('udp4');
        udp_client.send(umsg, 0, umsg.length, REMOTE_SERVER_UDP_PORT_2, REMOTE_SERVER_IP, function(error) {
          if(error){
            udp_client.close();
            //sendUdpMsg( );
          }else{
            udp_client.close();
            console.log('sent UDP: ' + umsg);
          }
        });
});

udpdserver2.bind(THIS_SERVER_UDP_PORT_2, THIS_SERVER_IP);
