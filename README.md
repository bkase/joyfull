joyfull
=======

Use a joystick in the browser

## How to run the proof of concept example:
```
Move npJoyfull.so to ~/.mozilla/plugins
Open FBControl.html in Chrome or Firefox
```

v0.1 API
=======

Warning: Subject to change!

```javascript
plugin().init(pathToDevice) //where pathToDevice is the path to 
                            //the Joystick file descriptor on your machine
setInterval(function() {
  plugin().poll();
}, rateInMillisToFlushJoyEventBuffer);

var joyEventHandler = function(joyButton) {
  if (joyButton.type == 'analog_x') {
    xPos += joyButton.value;
  }
}

plugin().addEventListener('joystickData', joyEventHandler, false);

```

_joyButton object_

* _joyButton.type_:
   A string denoting the button that was acted on, one of
 
```javascript 
 'analog_x', 'analog_y', 'analog_ball' //these are the analog types
 
 'trigger', 'down_top', 'up_top', 'left_top', 'right_top', 'leftup_bot', 
 'leftdown_bot', 'centerleft_bot', 'centerright_bot', 
 'rightdown_bot', 'rightup_bot'        //these are the digital types
```

* _joyButton.value_:
  The value of the button pressed or analog input.

  The value is between `-32,768` and `32,767` if `joyButton.type` is an analog type
  
  The value is `0` if the button is not pressed and `1` if it is pressed if `joyButton.type` is a digital type