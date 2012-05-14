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
var onJoystickEvent = function(type, value) {
    console.log(type + ", " + value);
};

window.onload = function(){
    var joystick = new Joystick('/dev/input/js0', 30, onJoystickEvent);
};
```

_Joystick_

    _constructor(pathToJoystickInput, millisToWait, handler)_:
        The constructor, `handler` is a `function(type, value)` which gets called every `millisToWait` milliseconds with new data from the joystick at `pathToJoystickInput`

    _type_: a string denoting the type of the button

    _value_: `0` or `1` if digital, `-32,768` to `32,768` otherwise
        
## If you want to hack `joyfull.js`

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
