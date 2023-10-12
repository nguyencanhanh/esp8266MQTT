var mqtt;
var reconnectTimeout = 2000;
var host = "192.168.0.223"; // Địa chỉ IP của Mosquitto server
var port = 9001;

function onConnect() {
    console.log("Connected to MQTT server");
    mqtt.subscribe("den");
}
function onFailure(message) {
    console.log("Connection to MQTT server failed: " + message.errorMessage + " Retrying...");
    setTimeout(MQTTconnect, reconnectTimeout);
}

function MQTTconnect() {
    mqtt = new Paho.MQTT.Client(host, port, "client_id");
    var options = {
        onSuccess: onConnect,
        onFailure: onFailure,
    };
    mqtt.onMessageArrived = onMessageArrived;
    mqtt.connect(options);
}
var button = document.getElementById('val');
function onMessageArrived(message) {
    if (message.destinationName == "den"){
        if(message.payloadString == "1"){
            button.innerHTML="Bật";
        }else{
            button.innerHTML="Tắt";
        }
    }
}
function send(message) {
    var topic = "dulieu";
    var messageObject = new Paho.MQTT.Message(message);
    messageObject.destinationName = topic;
    mqtt.send(messageObject);
}
button.addEventListener('click', function(){
if(button.innerHTML == "Bật"){
    button.innerHTML="Tắt";
    button.className = "btn btn-secondary";
    send("ON");
}
else{
    button.innerHTML="Bật";
    button.className = "btn btn-danger";
    send("OFF");
}
});

MQTTconnect();