const express = require('express');
const axios = require('axios');

const app = express();
app.use(express.json());
app.use(express.urlencoded({extended: false}));

const socketUrl = 'http://localhost:4000/';
app.post('/', async (req, res) => {
    console.log(req.body);
    await new Promise((r) => setTimeout(r, 300));
    const t = req.body;
    let forSock = `${t.vehicle}\n`;
    for (let j = 0; j <= t.dates.length-1; j++) {
        forSock += `${t.dates[j]}\n`;
    }
    axios.post(socketUrl, forSock).
        then(r => {
            console.log(r.data);
            res.send(`${r.data}`);
        });
});

app.listen(5000, () => {console.log('Listening to app...')})