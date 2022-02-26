#include <Arduino.h>

char _webpage[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html lang="en">

  <head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
      body{
        padding: 0;
        margin: 0;
        font-family: Arial, Helvetica, sans-serif;
        /* background: linear-gradient(120deg, #2b5876, #4e4376); */
        overflow: hidden;
        height: 100vh;
      }
      .center{
        position: absolute;
        top: 50%;
        left: 50%;
        transform: translate(-50%,-50%);
        width: 300px;
        background: white;
        border-radius: 10px;
        box-shadow: rgba(0, 0, 0, 0.35) 0px 5px 15px;
      }
      .center h1{
        text-align: center;
        padding: 0 0 20px 0;
        border-bottom: 1px solid silver;
        text-transform: uppercase;
        font-weight: 100;
      }
      .center form{
        padding: 0 40px;
        box-sizing: border-box;
      }
      form .text_field{
        position: relative;
        border-bottom: 2px solid #adadad;
        margin: 30px 0;
      }
      .text_field input{
        width: 100%;
        height: 40%;
        font-size: 16px;
        border: none;
        background: none;
        outline: none;
      }
      .text_field label{
        position: absolute;
        top: 50%;
        left: 5px;
        color: #adadad;
        transform: translateY(-80%);
        font-size: 16px;
        pointer-events: none;
        transition: .5s;
      }
      .text_field span::before{
        content: '';
        position: absolute;
        top: 20.5px;
        left: 0;
        width: 0%;
        height: 2px;
        background: #2691d9;
        transition: .5s;
      }
      .text_field input:focus ~ label,
      .text_field input:valid ~ label{
        top: -5px;
        color: #2691d9;
      }
      .text_field input:focus ~ span::before,
      .text_field input:valid ~ span::before{
        width: 100%;
      }
      input[type="submit"]{
        width: 100%;
        height: 50px;
        border-radius: 50px;
        font-size: 18px;
        background: #2691d9;
        border: none;
        outline: none;
        color: #e9f4fb;
        cursor: pointer;
        margin-bottom: 30px;
        box-shadow: rgba(0, 0, 0, 0.35) 0px 5px 15px;
      }
      input[type="submit"]:focus{
        box-shadow: rgba(0, 0, 0, 0.1) 0px 5px 15px;
      }
    </style>
    <title>SETTING</title>
  </head>

  <body>
    <div class="center">
      <h1>setup</h1>
      <form action="/data">
        <div class="text_field">
          <input type="text" name="auth" required/>
          <span></span>
          <label for="">AUTH</label>
        </div>
        <div class="text_field">
          <input type="text" name="ssid" required/>
          <span></span>
          <label for="">SSID</label>
        </div>
        <div class="text_field">
          <input type="text" name="pass" required/>
          <span></span>
          <label for="">PASSWORD</label>
        </div>
        <input type="submit" value="SEND"/>
      </form>
    </div>
  </body>

  </html>
)=====";


char success[] PROGMEM = R"=====(
  <!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    body {
      text-align: center;
      padding: 40px 0;
      background: #EBF0F5;
    }

    h1 {
      color: #88B04B;
      font-family: sans-serif;
      font-weight: 900;
      font-size: 40px;
      margin-bottom: 10px;
      font-weight: 100;
    }

    p {
      color: #404F5E;
      font-family: sans-serif;
      font-size: 20px;
      margin: 0;
    }

    i {
      color: #9ABC66;
      font-size: 100px;
      line-height: 200px;
      margin-left: -15px;
    }

    .card {
      background: white;
      padding: 60px;
      border-radius: 4px;
      box-shadow: 0 2px 3px #C8D0D8;
      display: inline-block;
      margin: 0 auto;
      border-radius: 20px;
      box-shadow: rgba(0, 0, 0, 0.35) 0px 5px 15px;
    }

    .check {
      border-radius: 200px;
      height: 200px;
      width: 200px;
      background: #f0fddc;
      margin: 0 auto;
    }
  </style>

  <title>SUCCSESS</title>
</head>

<body>

  <div class="card">
    <div class="check">
      <i class="checkmark">✓</i>
    </div>
    <h1>Success</h1>
    <p>Semua pengaturan telah di simpan<br /> ESP telah restart dengan sendirinya!</p>
  </div>
</body>

</html>
)=====";

