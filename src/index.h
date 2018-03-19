const char INDEX_HTML[] = R"=====(
<!DOCTYPE HTML>
<html>
<head>
    <meta name="viewport" content="width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
    <title>Control LED light</title>
    <style>
        body {
            background-color: #ffffff;
            font-family: Arial, Helvetica, Sans-Serif;
            Color: #000000;
        }
        .content {
          width: 100%;
          display: flex;
          align-items: center;
          justify-content: center;
          flex-direction: column;
        }
        button {
          height: 35px;
          width: 220px;
          font-size: 14px;
        }
    </style>
</head>
<body>
<div class="content">
    <h1>Control LED light</h1>
    <button onclick="updateLed(4)">ON</button><br>
    <button onclick="updateLed(3)">OFF</button><br>
    <button onclick="updateLed(1)">Run BLINK program</button><br>
    <button onclick="updateLed(2)">Run SMOOTH program</button><br>
</div>

<script>
    function updateLed(mode) {
        var http = new XMLHttpRequest();
        var params = "LED=" + mode;
        http.open("POST", "/", true);
        http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        http.send(params);
    }
</script>
</body>
</html>
)=====";
