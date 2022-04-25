
# C++/NodeJS solution for basic scenario of Congestion Tax Calculator 

To run the app on localhost 5000:

Folder **nodejs**:
- `cd nodejs`
- `npm i`
- `node server.js`

Folder **cpp**:
- `g++ --std=gnu++17 socket.cpp -o socket.exe`
- `./socket.exe`

NodeJS receives http request and sends data to a socket in C++ part. All calculations are performed in C++, then the socket delivers the results back to NodeJS server which sends them in response to the initial request. 

Request can be run via Postman. Below is an example of JSON with data for which the tax should be calculated. It has properties `vehicle` for vehicle type and `dates` for the array of dates in usual human-readable format. Note the difference from Python version where the request was an array of objects. Here is only one vehicle per request, therefore the request is an object, not an array of objects. 

```
{
    "vehicle": "A",
    "dates": [
        "2013-01-14 21:00:00",
        "2013-01-15 21:00:00",
        "2013-02-07 06:23:27",
        "2013-02-07 15:27:00",
        "2013-02-08 06:27:00"
    ]
}
```

Response will be the calculated tax fee. 
