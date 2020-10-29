const /*PROGMEM*/ char _index_html[] = R"---(
<html>
<head>
<link rel="icon" type="image/png" href="/favicon.png"/>
<script>
"use strict";

class Comm {
  constructor()
  {
    var base = location.hash ? location.hash.substr(1) : window.location.hostname;
    if (base == "localhost" || base == "")
      base = "192.168.1.105";

    this.uri = "ws://" + base + ":88/";
    this.online = false;
  }

  init()
  {
    var websocket = new WebSocket(this.uri);
    this.websocket = websocket;

    websocket.onopen = (() => {
      this.online = true;
      this.handle("Connected");
    }).bind(this);

    websocket.onclose = (() => {
      this.online = false;
      this.handle("Disconnected");
    }).bind(this);

    websocket.onmessage = ((evt) => {
      var command = evt.data.toString();
      this.process(command);
    }).bind(this);

    websocket.onerror = ((evt) => {
      this.handle("Error: " + evt.data);
    }).bind(this);

  }

  process(line)
  {
    eval(line);
  }

  send(line)
  {
    if (this.online)
      this.websocket.send(line);
  }

  handle(message)
  {
    console.log(message);
  }
}

class Handler 
{
  log(msg)
  {
    document.querySelector('#info').innerHTML = msg;
  }
  status(json)
  {
    this.log(JSON.stringify(json));
  }
  append(line)
  {
    var textarea = document.querySelector('#textarea');
    textarea.value += line + "\n";
    textarea.scrollTop = textarea.scrollHeight;
  }
  error(msg)
  {
    this.log(msg);
  }
}

var _h = new Handler();
var comm = new Comm();
comm.handle = (msg) => _h.log(msg);
window.addEventListener("load", () => comm.init(), false); 

setInterval(() => {
  if (comm.online)
    comm.send("status();\n");
}, 5000);

</script>
</head>
<body>
  <h2>
      Uart logger
  </h2>
  <textarea id="textarea" cols=80 rows=20 readonly></textarea>
  <div id="info"></div>
  <br>
  <a href="/download">Download initial buffer (32kB max)</a>&nbsp;
  <a href="/log.txt">See initial buffer</a><br>
  <input type="button" value="Set 57600 bauds" onClick="comm.send('baudrate(57600);\n')">
  <input type="button" value="Set 9600 bauds" onClick="comm.send('baudrate(9600);\n')">
  <input type="text" id="cmd"><input value="send" type="button"
  onClick="comm.send(document.querySelector('#cmd').value)"><br>
</body>
</html>
)---";

const /*PROGMEM*/ char _index_html_redirect[] = R"---(
<html><script>document.location.href = "http://192.168.1.144/remote.html#" + window.location.hostname;</script></html>
)---";

const /*PROGMEM*/ char _favicon_png[] = {
0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x40,0x10,0x06,0x00,0x00,0x00,0xfa,0xf9,0xad,
0x9d,0x00,0x00,0x00,0x06,0x62,0x4b,0x47,0x44,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x58,0xf7,0xdc,0x00,0x00,0x00,0x09,0x70,0x48,0x59,0x73,0x00,0x00,0x00,0x48,0x00,
0x00,0x00,0x48,0x00,0x46,0xc9,0x6b,0x3e,0x00,0x00,0x0c,0x26,0x49,0x44,0x41,0x54,0x78,0xda,0xed,0xdd,0x6d,0x94,0x55,0xd5,0x7d,0xc7,0xf1,0xcf,0xb9,0xf7,0xce,0x03,
0x03,0xc3,0x0c,0xcf,0x6a,0x04,0x04,0x31,0x5a,0x45,0x51,0x5a,0x13,0x56,0x94,0xf8,0xc0,0xc4,0x56,0x6b,0x62,0xad,0x32,0x54,0xeb,0x73,0xd3,0xa6,0xf5,0xa1,0x26,0xc4,
0xae,0xd5,0x18,0xb5,0x8d,0x09,0x2b,0x31,0x76,0xa5,0x8d,0x31,0xda,0xa8,0x75,0x25,0xc6,0x36,0x32,0x36,0x5a,0x35,0x3e,0x33,0x60,0xac,0x56,0x03,0x88,0x88,0x28,0xa8,
0x80,0x08,0x0a,0x32,0x30,0x30,0x30,0xcc,0x9d,0xa7,0x7b,0xcf,0xe9,0x8b,0x73,0x2e,0x2a,0x4b,0x17,0x0a,0x63,0xce,0xc0,0xcc,0xf7,0xcd,0x5e,0xe7,0xee,0x73,0xf6,0xfe,
0x9f,0xbd,0x7f,0xfb,0x79,0x9f,0xbb,0x83,0xba,0x0b,0x1b,0x1a,0x58,0x16,0x59,0x05,0xd9,0x26,0xdd,0x90,0x0f,0xc5,0x14,0xf4,0xb3,0x2f,0x91,0x53,0x06,0x55,0x81,0xf1,
0x50,0x1c,0x95,0xdb,0x91,0xf1,0x2b,0xe1,0x47,0x23,0x34,0xc1,0xcb,0x97,0x0a,0xc0,0xb6,0xb4,0x2d,0xee,0xa7,0x87,0x88,0xc0,0x60,0x23,0xe1,0xc8,0x5b,0xe2,0x1f,0x67,
0x6e,0xc8,0xed,0x28,0xf1,0x49,0xc6,0x17,0x4e,0x80,0x67,0xe7,0x28,0x82,0xcd,0x69,0xdb,0xdd,0x4f,0x0f,0x91,0x05,0x43,0x73,0xbf,0x05,0x97,0x1a,0x03,0xf9,0x7f,0xca,
0x25,0xde,0x85,0x1d,0x25,0x3e,0xc9,0xf8,0xa7,0x9e,0xaa,0xaf,0xd7,0x2f,0x80,0x7d,0x86,0x13,0x4f,0x6c,0x68,0x80,0x9d,0x6a,0xf6,0x42,0x26,0x6d,0xc3,0xfa,0x49,0x97,
0x7e,0x01,0xf4,0x71,0xfa,0x05,0xd0,0xc7,0xc9,0xed,0x79,0x10,0xbf,0x1f,0xa6,0xe5,0x1b,0xe6,0xa1,0xc2,0xeb,0x36,0xe1,0x30,0x83,0xe4,0x51,0x1b,0xfc,0x83,0x31,0x98,
0x3f,0xe7,0xfe,0xfa,0x93,0xd0,0xfe,0x69,0xc5,0x5f,0xf7,0xc3,0x86,0x2b,0x91,0x0d,0xae,0xb6,0x1f,0xc6,0x99,0x61,0x11,0xc6,0x9a,0xe3,0x7c,0xbc,0x18,0xdd,0x60,0x01,
0xb6,0xcc,0xb9,0xa8,0xfe,0xbb,0x4a,0x7d,0xee,0xbd,0x80,0x5e,0x5f,0x03,0x9c,0x34,0xf1,0x81,0x53,0x91,0x0d,0x3e,0x27,0xcb,0x80,0x2b,0x82,0xf3,0x65,0x19,0x7f,0x72,
0x70,0xa1,0x32,0x0e,0xbf,0x46,0xb9,0x0e,0x06,0x2d,0xaa,0xfb,0xe7,0x86,0xdb,0x31,0xb7,0xa7,0xe3,0x9f,0xb6,0xbe,0xe1,0x65,0x4c,0xf6,0x6b,0x53,0x28,0x3b,0x20,0xaa,
0xf7,0x59,0x0e,0x9c,0x1c,0x0d,0x71,0x36,0x13,0x4f,0x8e,0xce,0x57,0x64,0xd8,0x02,0x77,0x68,0x25,0x93,0xab,0x9b,0xdc,0x70,0x01,0xf1,0x68,0x7b,0x6f,0xa0,0xd7,0x0b,
0x20,0x73,0x7f,0xf7,0xff,0xe0,0x46,0x23,0xe4,0x99,0x9a,0x33,0x54,0xc4,0x0d,0x2d,0x2a,0xe5,0xf8,0xd9,0x72,0xed,0x3a,0x38,0xf3,0x97,0x16,0x1b,0x41,0xd5,0xb4,0xa9,
0x8b,0x1e,0x1c,0xa1,0xd4,0xd7,0xed,0x09,0xca,0x74,0x91,0xb9,0x44,0x8b,0x41,0x1c,0xf2,0x8a,0x0d,0x22,0xbe,0x75,0xb6,0xd5,0x32,0xdc,0x36,0xc5,0x4a,0x6d,0x5c,0x7a,
0x3f,0x0e,0x64,0xd8,0x17,0x54,0xf9,0x2c,0xfe,0x22,0xed,0x74,0xfb,0xb8,0xf4,0xfa,0x26,0x20,0xb8,0x31,0x7c,0x9e,0x6c,0x9b,0x0a,0x5b,0xf9,0xe2,0x4f,0x14,0x05,0x4c,
0xdb,0x18,0x57,0xb2,0x83,0xaf,0xd4,0x2a,0xe4,0xed,0xeb,0xbd,0x64,0x3f,0xe6,0x4e,0xc9,0x1c,0xd4,0xb5,0x81,0xfc,0x79,0x62,0x71,0xef,0xf9,0x44,0xd6,0x16,0xeb,0x29,
0xdb,0x64,0x9b,0x02,0x47,0x96,0xeb,0x12,0x51,0x77,0x84,0x40,0xc4,0xc1,0x74,0xaa,0xa4,0x6c,0xa8,0x0a,0x47,0xf1,0xc8,0x22,0x0c,0x65,0xd3,0x36,0x5c,0xb3,0x37,0xb4,
0x04,0xbd,0x5e,0x00,0xda,0xa2,0x88,0xec,0x4a,0xc5,0xa0,0x95,0x9a,0xcb,0x45,0x06,0x51,0x79,0x0b,0x32,0x64,0xbb,0xe4,0x85,0x0c,0xf9,0xc7,0xe8,0x15,0xcd,0x54,0x3e,
0x19,0xfc,0x4b,0xd8,0x85,0x21,0xc9,0xd3,0x7b,0x2e,0x80,0xe7,0xe4,0xc9,0x7c,0x39,0x7a,0x0b,0x06,0x3f,0x1a,0x4c,0x85,0xaa,0xaf,0xa9,0x80,0xec,0x61,0xb1,0x3d,0x83,
0x3b,0x05,0x26,0x53,0xd5,0x44,0x30,0x09,0x77,0x25,0x4f,0x7f,0x2d,0xed,0xe4,0xdb,0x15,0xbd,0xbe,0x09,0xb0,0xc1,0x06,0x0c,0x14,0x89,0x50,0x9b,0xfc,0x5a,0x12,0x6e,
0x20,0x2e,0x66,0xd5,0x3a,0x75,0x60,0x88,0xff,0xf3,0xa0,0x9e,0x6c,0x02,0xb6,0x24,0xf1,0x75,0x80,0x61,0xe2,0x55,0x92,0xca,0xa4,0x70,0x07,0xe2,0x39,0xb6,0x6a,0xd4,
0x10,0x0c,0xc1,0xfe,0x69,0x27,0xd9,0x27,0xa1,0xf7,0x0b,0xa0,0x9f,0x4f,0x95,0x7e,0x01,0xf4,0x71,0xfa,0x05,0xd0,0xc7,0xe9,0x17,0x40,0x1f,0x27,0xb5,0x51,0xc0,0x97,
0x46,0xcd,0xde,0x82,0x20,0xba,0xd8,0x02,0x54,0x5a,0x68,0x8b,0x8f,0x9e,0x40,0x19,0x9c,0xb8,0xe5,0xbb,0x78,0x8f,0xea,0x60,0xaa,0x07,0x90,0xad,0xcb,0xcd,0x9e,0xfd,
0xbe,0xe7,0x76,0x9b,0x28,0x10,0x25,0xe1,0x04,0xe8,0x4a,0x7e,0xde,0xb9,0xe0,0x94,0xae,0x07,0xa2,0x15,0x35,0x75,0x75,0x3b,0xc5,0x5f,0xda,0x5a,0xb3,0x0e,0x74,0x47,
0x2f,0x83,0x8e,0xc6,0x8a,0x19,0x33,0xa4,0x38,0x5e,0x4c,0x4d,0x00,0xd1,0xa5,0xc1,0xfe,0xb8,0xc4,0x12,0x35,0xe4,0x86,0xa3,0x9c,0xec,0xf3,0x1f,0x72,0xe7,0x12,0xca,
0xb3,0x68,0x20,0x3b,0x28,0xf9,0xf1,0xb8,0xc4,0x5d,0x8a,0x88,0x4c,0xd6,0x50,0x5b,0x28,0xff,0xc3,0xec,0x23,0x9e,0xa5,0xa2,0xd5,0x90,0xe0,0x69,0xef,0x0d,0x07,0x77,
0x9f,0x2f,0x3b,0x8b,0x8a,0x26,0xe5,0x8e,0xa5,0x6c,0x86,0x58,0xa4,0x2f,0x26,0xbe,0xd3,0xe3,0xf9,0x80,0x60,0xa4,0x8c,0x66,0xca,0x66,0x0a,0xa3,0xc3,0xa8,0x38,0x44,
0x14,0x5c,0x45,0x74,0xcc,0x8e,0x70,0xe2,0x71,0xc9,0x33,0xb1,0x24,0x8a,0x3f,0x0f,0x0e,0x12,0x51,0x18,0x37,0xed,0x89,0x86,0x83,0x30,0xb5,0xf1,0x94,0xfa,0xd5,0x52,
0x10,0x42,0x7a,0xf3,0x00,0x6f,0x1b,0x41,0xae,0x42,0xa7,0x13,0x38,0xfa,0x34,0x0c,0x63,0xfc,0x87,0x0c,0xa1,0x82,0x6b,0xc9,0x9d,0x80,0x23,0x19,0xff,0x55,0x04,0x64,
0x0f,0x4d,0x3c,0x27,0x2b,0x53,0x60,0x64,0x65,0xf0,0x45,0x2d,0xd4,0x7d,0xde,0x30,0x7f,0xc6,0x86,0xc5,0xe2,0xc4,0xdc,0xb8,0xa7,0x66,0x06,0xe7,0x28,0xa7,0xe2,0x8f,
0x35,0xd9,0xc6,0xa4,0xe5,0xf6,0x37,0x84,0x01,0xdb,0x04,0x32,0x38,0x5e,0x46,0x07,0x83,0xde,0x50,0x66,0x1e,0xc7,0x8f,0xd2,0xe9,0x60,0x86,0xbf,0x8c,0x83,0x88,0xce,
0xdc,0x11,0x50,0x56,0x44,0xf1,0x62,0xb5,0xda,0x58,0x7b,0x9c,0x1a,0xcd,0x2c,0x19,0x1e,0xcc,0xf2,0x10,0x1d,0xa5,0x9a,0xaf,0x6b,0x37,0x4c,0xdc,0x23,0xd2,0x13,0xc0,
0x48,0xc3,0x28,0x9f,0x6b,0xa3,0x09,0x9c,0xde,0x8e,0x91,0xd4,0x7f,0x48,0x0d,0x20,0x20,0xf8,0x4f,0x54,0x31,0x6a,0x48,0x7c,0x5d,0xf6,0x9b,0xc4,0xef,0x1b,0x2a,0x64,
0x98,0xf0,0x37,0xca,0x0d,0xe7,0xef,0xff,0x44,0x60,0x30,0xdd,0x37,0x24,0xfe,0xdd,0x7b,0x6c,0xe7,0x40,0x01,0xc1,0x43,0xc6,0x18,0x40,0xcd,0x5b,0x32,0x02,0x6a,0xae,
0x4d,0x7c,0x7f,0x86,0x0e,0x86,0xcd,0x57,0xd0,0xc9,0xc5,0xbf,0x10,0x99,0x40,0x7e,0x7c,0xe2,0xdf,0xf8,0xbe,0xb7,0x08,0xe9,0xa8,0x57,0x66,0x3b,0x8f,0x9e,0x6c,0x80,
0x6a,0xde,0xfc,0x6b,0x47,0x44,0xdd,0x74,0x54,0xfa,0xad,0x8c,0x3e,0x25,0x80,0xbc,0xd3,0x50,0xa7,0x68,0x2c,0x43,0x6f,0xc2,0x00,0x0e,0x5d,0x95,0xa4,0xd6,0x37,0x76,
0xba,0x7b,0xa0,0x58,0x08,0x5b,0x92,0xeb,0x6f,0x27,0x6e,0x8d,0x40,0x96,0x81,0x5f,0x10,0xa8,0xe6,0xe0,0xbb,0xc4,0x25,0x7f,0x6c,0x8f,0xd9,0x19,0x57,0xdd,0xb7,0xcb,
0x09,0x70,0x7b,0x62,0xc7,0x0f,0x12,0xdf,0xb1,0xf1,0x0e,0xaa,0xf2,0x55,0xb1,0xfd,0x63,0x2e,0x47,0x25,0x6e,0x4b,0xfc,0x27,0xec,0x08,0x27,0x12,0x90,0xbf,0x47,0xa7,
0xfd,0x58,0xf8,0x63,0xed,0x8e,0x20,0x73,0x94,0x87,0x83,0xb5,0x24,0xfb,0xb0,0x52,0x20,0x3d,0x01,0xbc,0xeb,0x48,0xa2,0xb5,0x22,0x19,0xba,0xb7,0x0a,0x04,0x04,0x67,
0xc4,0xad,0x60,0xb0,0xf4,0x13,0x86,0x76,0xb5,0x38,0x63,0xe8,0xc9,0x59,0xc0,0x8f,0xe6,0x98,0x9d,0xae,0x4f,0xde,0x29,0xfe,0x53,0x3f,0xe2,0xb9,0x5b,0x85,0xb2,0x74,
0x37,0xeb,0x50,0x46,0xf8,0xfd,0xe8,0xce,0xe0,0x5c,0x74,0x9b,0xf4,0x7b,0xb0,0xfa,0x43,0x48,0x6f,0x18,0x38,0xd2,0x76,0xa2,0xfd,0x0d,0xd2,0x45,0xd7,0xb7,0xe3,0x36,
0x32,0x6c,0x4b,0xcd,0x9e,0x4f,0x9b,0x0c,0x44,0xb3,0xd4,0xe8,0xa2,0x6b,0x95,0x09,0x9a,0x29,0xce,0x6f,0x9c,0x34,0xfd,0x59,0x3d,0xd1,0x54,0xed,0x26,0xe9,0xd5,0x00,
0x9b,0x94,0x11,0x6d,0x97,0x97,0xa1,0xe3,0xf4,0x78,0x8e,0xbd,0x78,0x62,0xec,0x99,0x4d,0xcd,0xac,0x4f,0x8d,0x50,0x40,0xf1,0x25,0xad,0x72,0x74,0x2c,0xd0,0xaa,0x92,
0x30,0xf5,0xc5,0xb8,0xf4,0x0c,0x78,0x43,0x17,0x51,0x18,0xaf,0xeb,0x77,0xce,0x8a,0x67,0x00,0xc2,0xd1,0x49,0x05,0x3e,0x3d,0xed,0x84,0xe9,0x71,0x8a,0x02,0xc2,0xe7,
0xe3,0x7d,0x05,0x9d,0x33,0x35,0xab,0x25,0x5e,0x63,0x4c,0x93,0xf4,0x9a,0x80,0x32,0x93,0x08,0x6f,0x93,0x55,0x4b,0xdb,0x99,0xf1,0xb0,0xaa,0xf0,0xf5,0xc4,0x77,0x5f,
0xfb,0x22,0x29,0x8a,0xe7,0x0b,0x8a,0xf3,0x54,0xe8,0xa4,0x6d,0x92,0x2a,0x6d,0x14,0x2f,0x4f,0xdb,0xb0,0xf4,0x04,0x50,0xae,0x9a,0xe8,0xb6,0xb8,0x17,0xdf,0x7a,0x62,
0xdc,0x4b,0xee,0x7e,0x3c,0xf1,0x7d,0x27,0xed,0x84,0xe9,0x61,0xd6,0xc7,0xcb,0xd9,0xdd,0xdb,0x15,0x75,0xd3,0x3a,0x41,0x87,0x36,0x8a,0x9f,0x4f,0xdb,0xb0,0xf4,0x04,
0xf0,0xba,0x37,0x88,0xee,0xb3,0x5d,0x1b,0x5b,0x87,0x08,0x85,0x74,0xcc,0x4a,0x7c,0xff,0x37,0xed,0x84,0xe9,0x61,0xee,0x8b,0x6b,0x80,0xf6,0x1f,0xa9,0xd0,0xcd,0xb6,
0x45,0x86,0xc9,0x13,0xde,0x99,0xb6,0x61,0xa9,0x09,0x20,0x5a,0xe3,0x69,0xa2,0x85,0x06,0x6a,0xa7,0xe5,0x84,0x78,0x96,0xbf,0xed,0xd5,0xc4,0xfb,0x6f,0xd3,0x4e,0x98,
0x1e,0x7e,0xdb,0x0b,0x64,0x65,0xd9,0xfe,0xb8,0x81,0x06,0xd0,0x12,0x1a,0xa5,0x86,0x70,0x4d,0xda,0x96,0xa5,0x26,0x80,0xe0,0x48,0x43,0x88,0x2e,0x50,0xad,0x9a,0x2d,
0x73,0xe3,0xa6,0x60,0xf3,0x88,0xd8,0x37,0xfc,0x4e,0xda,0x09,0xd3,0xb3,0x44,0xbf,0x8b,0x7b,0x35,0x2d,0x37,0xc7,0xa3,0x9e,0xcd,0xa7,0xd8,0xa2,0x92,0xb0,0x39,0x6d,
0xcb,0xd2,0x6b,0x02,0x0e,0x31,0x1d,0xcf,0xa2,0x96,0x6d,0xa3,0x65,0x94,0xd3,0xf4,0x76,0x3c,0x21,0x54,0x1c,0x9a,0x76,0xc2,0xf4,0x18,0xa1,0x88,0xb0,0x49,0x93,0xed,
0x6c,0x1a,0xea,0x05,0x6b,0x68,0xb9,0x2e,0xfa,0xb9,0xf9,0x84,0xe7,0xa5,0x6d,0x5e,0x7a,0x35,0x40,0x3e,0x1a,0x83,0xd7,0x8c,0xb4,0x94,0x96,0x7b,0x95,0xdb,0xcc,0xf2,
0x67,0x10,0xd2,0xbe,0x3c,0xb9,0x2d,0xb5,0x09,0x92,0x1e,0xe2,0xdd,0x78,0x58,0xdb,0xf1,0x86,0xc1,0x22,0x5e,0x7b,0xda,0x01,0xda,0x68,0xfe,0x4b,0x23,0xbc,0x40,0x94,
0xfa,0xc7,0xb7,0xa9,0x09,0xe0,0xc9,0x27,0x67,0x0c,0x40,0x41,0x41,0x48,0xc7,0x43,0x08,0x59,0x79,0x6b,0xdc,0x59,0xda,0x56,0xea,0x0b,0xcc,0x4e,0x3b,0x81,0xf6,0x90,
0x99,0xca,0x85,0xb4,0xac,0x30,0x4a,0xc8,0x9b,0xd7,0x39,0x4a,0x44,0xfe,0x4f,0x83,0xc3,0xad,0xc7,0xa3,0x69,0x1b,0x98,0xfe,0x8e,0xa0,0x4e,0x59,0xba,0xc6,0xc6,0x33,
0x81,0xaf,0x3d,0x19,0xaf,0x9a,0xad,0xbd,0x22,0xf6,0x0c,0x3b,0x93,0xbb,0x7a,0xff,0x06,0xfb,0x0f,0xd2,0x1d,0x97,0xfc,0xe2,0x64,0x15,0x22,0xd6,0xbc,0xe5,0x40,0x21,
0x2b,0xa6,0xf8,0x73,0x79,0x3a,0xdf,0xc9,0x9c,0x55,0x5c,0x84,0x0d,0x69,0x1b,0x9a,0xbe,0x00,0x06,0xaa,0xa5,0xb8,0x49,0xb9,0x0c,0xab,0xc7,0xca,0x09,0x79,0xe5,0xbb,
0x32,0x22,0x3a,0x7f,0x95,0xdc,0xf5,0x6e,0xda,0x66,0x7e,0x42,0xe6,0xc7,0xc3,0xda,0xfc,0x4c,0x6d,0x8a,0x2c,0x2d,0xb3,0x56,0xc0,0x9a,0xdf,0x78,0xc1,0x58,0x8a,0xaf,
0x3e,0xf1,0xd3,0x73,0x5a,0xf5,0x02,0x61,0xa7,0x2f,0x80,0xa2,0x95,0x44,0xeb,0xd5,0x2a,0xb0,0xe9,0x0a,0x95,0xca,0x99,0x3f,0x58,0x20,0xc7,0xfa,0x1b,0xe3,0x9b,0xa2,
0x92,0x10,0x52,0x4f,0xb0,0x8f,0x47,0x98,0x13,0x09,0x59,0x7f,0x93,0xed,0xda,0x59,0x70,0xb3,0x25,0xd6,0xb1,0x71,0x56,0xf4,0x43,0xcb,0x88,0xd6,0xa5,0x6d,0x61,0x89,
0xd4,0x05,0x10,0x2c,0x35,0x0f,0x0b,0xe4,0x1c,0x44,0xbe,0xc6,0x26,0x23,0x79,0x61,0xa6,0xbc,0x4a,0x5e,0xbc,0x30,0x5e,0x44,0xe9,0x58,0x98,0xdc,0xbe,0x38,0x6d,0x7b,
0x77,0x41,0x18,0x57,0xfd,0xed,0x13,0xe2,0xfd,0x03,0x8b,0xef,0x56,0xa5,0x8c,0x45,0x97,0xc9,0xd8,0x4e,0x5b,0xc1,0x5a,0xff,0x81,0xc7,0xd2,0x36,0xb4,0x44,0xea,0x02,
0x78,0x72,0x41,0xfd,0x3c,0x14,0x34,0x38,0x92,0x62,0x95,0xad,0x6a,0x58,0xb9,0xc2,0x40,0x11,0x8f,0xbe,0x14,0x7f,0x82,0xf5,0xe6,0x5d,0x71,0xc2,0x86,0x67,0xa7,0x6d,
0xef,0x47,0x10,0x21,0x20,0xda,0x8a,0x0c,0x6b,0xde,0x8d,0x9b,0xb4,0x87,0xee,0x33,0x5c,0x27,0x2b,0x8e,0x53,0xed,0x34,0x8a,0xc7,0x35,0x8e,0xaf,0x6f,0x26,0xf9,0xce,
0xa8,0x17,0x90,0xba,0x00,0x4a,0x44,0x6f,0x05,0xc7,0x60,0x96,0xaf,0x68,0xa6,0xf5,0x7b,0x0e,0xb5,0x95,0xa7,0xff,0xc8,0x40,0x45,0x9e,0x58,0x18,0x0b,0x60,0x73,0x69,
0xad,0xe0,0x91,0xd2,0x63,0x69,0xdb,0x9d,0x70,0x6a,0x3c,0x7f,0xd1,0xf2,0x7c,0x3c,0x9f,0x31,0x67,0x8c,0x76,0xa3,0x68,0xbc,0xce,0x60,0xdb,0x68,0x3d,0x76,0xce,0xe2,
0xfa,0x13,0xf1,0x4c,0xda,0x86,0xee,0x4c,0xaf,0x11,0x40,0x63,0xf5,0xf4,0x77,0xd0,0x99,0x99,0x1a,0x5d,0x4b,0xb8,0xce,0x6a,0x63,0x59,0xf9,0x94,0xe5,0xaa,0xf8,0x69,
0xa5,0x48,0x37,0x0f,0x5d,0x24,0xab,0xc8,0xe6,0x96,0xf8,0xa9,0xa8,0xb4,0x8f,0xa6,0x73,0x37,0xa3,0xdd,0x5d,0x92,0x3f,0xa2,0x88,0x5e,0x8f,0x17,0xd4,0x9b,0x47,0xcb,
0x1a,0xc8,0xec,0x8b,0x6c,0x33,0x9a,0x5b,0x4e,0x8a,0xe6,0x38,0x81,0xf5,0xc7,0x18,0xeb,0xb2,0x0f,0x6c,0x0e,0xed,0x65,0xa4,0xbe,0x21,0x61,0x67,0x9e,0xf8,0xd2,0x8c,
0xe7,0x10,0x4e,0x3b,0xe0,0xde,0xeb,0x08,0xf7,0x37,0x37,0x1a,0xc3,0xaa,0x29,0xc1,0x9d,0xc6,0x70,0x73,0xb5,0xb5,0x3e,0x43,0xeb,0x48,0x1b,0x0d,0xe1,0x8c,0x79,0xf1,
0x2a,0xe2,0xe8,0x71,0xf1,0xfc,0x41,0x66,0x49,0x12,0xcc,0xf0,0x4f,0xc9,0xbc,0x65,0xb1,0x53,0xfc,0x7a,0xdc,0xcb,0xdf,0x70,0x96,0xa1,0xda,0x98,0x3d,0xca,0x68,0xb5,
0xdc,0x31,0xd1,0x73,0x86,0xf1,0xc6,0x7f,0x35,0x06,0xf5,0x01,0xf6,0x4b,0x3b,0x3d,0x77,0x45,0xaf,0xa9,0x01,0x76,0xa6,0x71,0xdd,0xf4,0xb9,0x68,0x73,0x59,0xe1,0x14,
0xc2,0xb9,0x4e,0xf3,0x14,0x4b,0xae,0x52,0xd0,0xcd,0x4d,0x5f,0xd4,0x65,0x00,0xff,0x76,0xbb,0x6e,0x59,0x9e,0x6e,0x88,0x1b,0x83,0xb7,0x8f,0x8f,0xdd,0xce,0x5b,0x93,
0x60,0x6e,0xd8,0xcd,0xe8,0x4b,0x4d,0xcb,0x55,0xf1,0x2e,0xe0,0x8e,0xeb,0xe3,0xa2,0xf2,0xf6,0xc4,0xd8,0x6f,0xde,0x03,0xf2,0x8a,0xdc,0x74,0xae,0x6a,0xab,0xf8,0xf1,
0xb1,0xce,0xb7,0x90,0xd7,0xf2,0xfe,0x3d,0x38,0x97,0xe2,0x11,0x69,0xa7,0xdf,0xc7,0xa5,0xd7,0xd5,0x00,0x3b,0xd3,0xd8,0x78,0xee,0xb9,0x88,0xe2,0x0d,0xd6,0x85,0xba,
0xba,0x71,0x0d,0xa7,0xb2,0xf2,0x33,0x86,0x1a,0xcb,0x2d,0xed,0xf2,0xd6,0xf2,0xcc,0xe3,0x86,0xca,0x33,0x6d,0x5e,0x3c,0xfc,0x3a,0xef,0x27,0xf1,0x70,0xf2,0x0f,0x2e,
0x90,0x91,0xd9,0x8d,0x2d,0x66,0xdd,0xc8,0x50,0xfc,0x95,0x72,0xe5,0xbc,0x3a,0x5a,0xb5,0x90,0x7b,0x1b,0xb4,0xc2,0x13,0x13,0x2c,0x31,0x80,0x65,0x4b,0xc2,0x99,0x26,
0xd1,0xfe,0x57,0x73,0x27,0xd6,0xd7,0x23,0xf5,0xc5,0x9d,0x4f,0x4a,0xaf,0xad,0x01,0x3e,0x8a,0x39,0x6f,0xd6,0x7f,0x0b,0xef,0x44,0x23,0x1c,0x46,0x57,0xc6,0x3a,0xab,
0x59,0xbc,0xc4,0xeb,0x56,0xf0,0xf0,0x4a,0x9b,0x6d,0x66,0xc5,0x86,0xb8,0x8a,0x2e,0xee,0xee,0x7f,0xf5,0x74,0x21,0xa0,0x30,0x46,0x41,0x35,0xcb,0x96,0x89,0x1c,0xca,
0xc3,0xaf,0x39,0xdc,0x78,0x96,0xfc,0xda,0xc9,0xc6,0xd2,0x3e,0x63,0x6e,0xfd,0xde,0x99,0xf1,0x25,0xf6,0x3a,0x01,0x94,0x68,0x7c,0xac,0xbe,0x1c,0x9b,0xa2,0x39,0xee,
0xa0,0xf0,0x94,0x4d,0xd6,0x93,0x3f,0x54,0xb7,0x4e,0x3a,0xff,0x2e,0xf9,0x43,0x89,0x8b,0x76,0x33,0xf8,0xa4,0x09,0x88,0x0e,0x51,0x90,0xa3,0xe3,0x12,0x9b,0x1c,0x40,
0xfe,0xbf,0x2d,0x0a,0xbe,0x49,0xf1,0xe1,0x39,0xf7,0xd4,0x4f,0xc2,0x9c,0xb4,0xd3,0x61,0x4f,0xd9,0x6b,0x05,0xd0,0x4f,0xcf,0xd0,0x2f,0x80,0x3e,0x4e,0xbf,0x00,0xfa,
0x38,0xbd,0x7e,0x14,0xb0,0x4b,0xb2,0xb2,0x28,0xc6,0xbd,0x7d,0xd7,0x20,0x20,0x4c,0x3a,0x7f,0xc5,0x64,0x0d,0xa1,0x98,0x7c,0x74,0x19,0x7c,0x2e,0x79,0xea,0xe8,0xc4,
0x2d,0x7d,0x8d,0x5c,0x93,0xb8,0xa5,0xce,0xdc,0xfd,0xc9,0x73,0x47,0xc7,0x7d,0x89,0xb0,0x23,0x76,0xa3,0xeb,0x84,0x0a,0xf8,0x5d,0xda,0xaf,0xdd,0x53,0xec,0xfd,0x02,
0xa8,0x55,0x8b,0x05,0x2a,0x0d,0xa0,0xfd,0x1c,0x59,0x65,0x2c,0x9b,0x19,0x7f,0x73,0x38,0x22,0xd9,0x8f,0x5f,0xb1,0x25,0xde,0x6f,0x90,0xbd,0x1e,0x11,0xd9,0xef,0x2b,
0x8a,0x08,0x8e,0x56,0xa6,0x9c,0xe0,0x05,0x19,0x21,0x51,0xa0,0x20,0xa2,0x70,0x77,0x1c,0x78,0xfe,0x9b,0x8a,0x8a,0xbc,0xfe,0x1d,0x9d,0xf2,0x74,0x9c,0x66,0x9b,0x8d,
0x18,0x96,0xf6,0x6b,0xf7,0x14,0x7b,0xbf,0x00,0xc6,0x19,0x87,0x7f,0x55,0x6b,0x24,0xcd,0x0f,0x0b,0xd4,0x70,0xf7,0x2f,0x74,0xc9,0xf1,0xe8,0xd5,0x06,0xe9,0xa6,0xec,
0x1e,0xdb,0x45,0xe4,0x8e,0x97,0xd5,0x45,0xee,0x4a,0x5b,0x85,0x64,0xaa,0xe2,0xdd,0xb9,0xc1,0x79,0xaa,0x74,0x10,0x5d,0xad,0x59,0x81,0xae,0x29,0xf1,0xb7,0x8a,0x9d,
0xdb,0x75,0xe9,0xa0,0xe9,0xab,0x5a,0x6c,0x64,0x53,0xde,0x72,0x4b,0x89,0xce,0x48,0x62,0x7f,0x64,0x4f,0x4c,0xef,0x0d,0xec,0xf5,0x02,0x08,0x86,0x19,0x86,0xe5,0xb2,
0x0e,0xa0,0xeb,0xf4,0xe8,0x45,0x63,0x78,0xb3,0x21,0x18,0xa5,0x9b,0xd5,0x47,0x39,0xc3,0x2a,0x82,0x6b,0xac,0x15,0xe1,0x97,0xaa,0xb5,0x10,0xdc,0x61,0x95,0x6e,0x7c,
0xc5,0x68,0x47,0xa1,0xc6,0x81,0x9a,0x30,0xce,0x5b,0x0a,0x44,0x8f,0xc5,0xab,0x91,0xd1,0x1d,0xf1,0x1a,0x44,0x34,0xc4,0x00,0x79,0x1c,0x1d,0x35,0x45,0x4d,0x58,0x66,
0x44,0x7c,0xf8,0xca,0xde,0xce,0x5e,0x2f,0x80,0x39,0x9b,0xeb,0x7f,0xe0,0xbd,0xa9,0xdb,0x57,0x55,0x81,0x89,0xf1,0x65,0xc4,0xdd,0xde,0xe7,0x6d,0xe7,0x45,0x99,0x46,
0x0f,0xba,0x76,0x57,0x71,0x7c,0x80,0x11,0x69,0xbf,0x71,0xcf,0xd2,0x3f,0x0a,0xe8,0xe3,0xf4,0x0b,0xa0,0x8f,0xd3,0x2f,0x80,0x3e,0x4e,0xbf,0x00,0xfa,0x38,0xfd,0x02,
0xe8,0xe3,0xf4,0x0b,0xa0,0x8f,0xd3,0x2f,0x80,0x3e,0x4e,0x6e,0x87,0x5b,0x3a,0x5b,0x36,0x39,0x62,0x74,0xc7,0x49,0x93,0xfd,0xec,0x1b,0x24,0xf9,0xba,0x23,0x9f,0x63,
0x72,0xef,0x9d,0x26,0x9d,0x1c,0x2a,0xbc,0xe3,0x6c,0xd9,0xfe,0xc3,0xa3,0xf7,0x2d,0x76,0x3e,0x3c,0x3a,0xce,0xf7,0xa6,0x5c,0xe9,0x18,0xf1,0xf8,0xae,0x99,0x1b,0x4a,
0x87,0x0a,0x27,0x8f,0xed,0x6b,0x7f,0xd6,0xd4,0xd7,0x29,0x15,0xf8,0xa6,0x52,0xbe,0xff,0x3f,0x95,0x7f,0xfe,0xf1,0x77,0x6e,0x65,0xbc,0x00,0x00,0x00,0x00,0x49,0x45,
0x4e,0x44,0xae,0x42,0x60,0x82,};