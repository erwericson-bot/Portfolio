// Chat Application - WebSocket Server
// Run with: node chat-server.js
// Requires the "ws" package: npm install ws

const WebSocket = require('ws');

const PORT = 8080;
const wss = new WebSocket.Server({ port: PORT });

// Track connected clients and their usernames
const clients = new Map();

function broadcast(data, exclude = null) {
  const message = JSON.stringify(data);
  for (const client of wss.clients) {
    if (client.readyState === WebSocket.OPEN && client !== exclude) {
      client.send(message);
    }
  }
}

wss.on('connection', (ws) => {
  console.log('New client connected.');

  ws.on('message', (raw) => {
    let data;
    try {
      data = JSON.parse(raw);
    } catch (e) {
      return;
    }

    if (data.type === 'join') {
      clients.set(ws, data.username);
      broadcast({ type: 'system', text: `${data.username} joined the chat.` });
    }

    if (data.type === 'message') {
      broadcast({ type: 'message', username: data.username, text: data.text });
    }
  });

  ws.on('close', () => {
    const username = clients.get(ws);
    if (username) {
      broadcast({ type: 'system', text: `${username} left the chat.` });
      clients.delete(ws);
    }
    console.log('Client disconnected.');
  });
});

console.log(`Chat server running on ws://localhost:${PORT}`);
