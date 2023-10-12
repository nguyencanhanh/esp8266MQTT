const mqtt = require('mqtt');
const brokerUrl = 'mqtt://192.168.0.223';
const options = {
  port: 9001,
  clientId: 'canhanh',
};

const client = mqtt.connect(brokerUrl, options);

client.on('connect', () => {
  console.log('Connected to Mosquitto');
  const yourObject = {
    ssid: 'OPPO Reno4',
    pass: '11111111',
  };

  const jsonString = JSON.stringify(yourObject);
  const topic = 'data';
  client.publish(topic, jsonString, () => {
    console.log(`Message sent to topic ${topic}`);
    client.end();
  });
});

client.on('error', (error) => {
  console.error('Error:', error);
});
