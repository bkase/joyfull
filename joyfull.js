var Joystick = function(file, pollFrequency, onEvent){
    if(!this.__proto__.addEvent){
        console.log("must be called with new");
        return;
    }


    var pluginObj = document.createElement('object');
    pluginObj.id = "joystickPlugin";
    pluginObj.type = "application/x-joyfull";
    pluginObj.width = "0";
    pluginObj.height = "0";
    document.body.appendChild(pluginObj);

    var joystickPlugin = this.getJoystickPlugin();
    this.addEvent(joystickPlugin, 'joystickData', function(joyButton){
        if (joyButton.button_type)
            onEvent(joyButton.button_type, joyButton.button_value);
    });

    joystickPlugin.init(file)
    setInterval(function() {
        joystickPlugin.poll();
    }, pollFrequency);
}

Joystick.prototype.getJoystickPlugin = function(){
    return document.getElementById('joystickPlugin');
}
Joystick.prototype.addEvent = function(obj, name, func){
    if (window.addEventListener) {
        obj.addEventListener(name, func, false); 
    } else {
        obj.attachEvent("on"+name, func);
    }
}
