


socket = new WebSocket("ws:/" + "/" + location.host + ":81");
socket.onopen = function (event) {};
socket.onerror = function (event) {};
socket.onmessage = function (event) {};

var currentPosition = 
{
   x: 0,
   y: 0 
};

const forwardButton = document.getElementById('forward') 
const reverseButton = document.getElementById('reverse')
const rightButton = document.getElementById('right')
const leftButton = document.getElementById('left')

forwardButton.addEventListener('touchstart', () => sendY(1));
forwardButton.addEventListener('touchend', () => sendY(0));

reverseButton.addEventListener('touchstart', () => sendY(-1));
reverseButton.addEventListener('touchend', () => sendY(0));

rightButton.addEventListener('touchstart', () => sendX(1));
rightButton.addEventListener('touchend', () => sendX(0));

leftButton.addEventListener('touchstart', () => sendX(-1));
leftButton.addEventListener('touchend', () => sendX(0));

function sendY(value) {
  console.log('Y:', value);
  currentPosition.y = value;
  socket.send(JSON.stringify(currentPosition));
}

function sendX(value) {
  console.log('X:', value);
  currentPosition.x = value;
  socket.send(JSON.stringify(currentPosition));
}
